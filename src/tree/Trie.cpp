//
// Created by Lenovo on 2025/10/9.
//

#include "Trie.h"

Trie::Trie(bool startOfWord) :
        startOfWord(startOfWord), previos(new Trie *[26]{nullptr}) {}

void Trie::insert(const std::string &word) {
    Trie *cur = this;
    for (int i = (int) word.length() - 1; i >= 0; --i) {
        char t = word[i] - 'a';
        if (cur->previos[t] == nullptr)
            cur->previos[t] = new Trie();
        cur = cur->previos[t];
    }
    cur->startOfWord = true;
}

std::vector<int> Trie::possibleWordLength(const std::string &sentence, int wordEnd) const {
    if (wordEnd <= 0 || sentence.length() < wordEnd) {
        return {};// out of range;
    }
    const Trie *cur = this;
    std::vector<int> res;
    for (int i = wordEnd - 1; i >= 0; --i) {
        cur = cur->previos[sentence[i] - 'a'];
        if (cur == nullptr) {
            // 没有了
            return res;
        } else if (cur->startOfWord) {
            res.push_back(wordEnd - i);
        }
    }
    return res;
}


void Trie::clear() {
    // 清空子节点, 但不清空子节点数组和root节点本身
    for (int i = 0; i < 26; ++i) {
        Trie *child = this->previos[i];
        if (child) {
            delete child;
            this->previos[i] = nullptr;
        }
    }
}

Trie::~Trie() {
    // cleanup: no recursion
    std::vector<Trie *> st;
    auto node = this;
    if (!node->previos) return;
    for (int i = 0; i < 26; ++i)
        if (node->previos[i]) st.push_back(node->previos[i]);
    while (!st.empty()) {
        node = st.back();
        st.pop_back();
        for (int i = 0; i < 26; ++i)
            if (node->previos[i]) st.push_back(node->previos[i]);
        delete[] node->previos;  // 删除节点内的数组
        node->previos = nullptr; // 防止递归
        delete node;             // 删除节点自身
    }
    delete[] previos;
}