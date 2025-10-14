//
// Created by Lenovo on 2025/10/9.
//

#ifndef ALGORITHM_TRIE_H
#define ALGORITHM_TRIE_H

#include <string>
#include <vector>

/**
 * 字典树Trie
 * root是所有的word的结尾
 * 所有叶子是word的开头
 * 有些word, 例如male和female, male的开头在female的字母m上, 在m上做一个特殊标记
 */
class Trie {
private:
    Trie **previos;
    bool startOfWord;/*是端点*/
public:
    explicit Trie(bool startOfWord = false);

    void insert(const std::string &word);

    /**
     * 从wordEnd(不包括)往前倒, 匹配的单词有几个
     * @return 匹配的单词的长度, 升序排列
     */
    [[nodiscard]] std::vector<int> possibleWordLength(const std::string &sentence, int wordEnd) const;

    void clear();

    virtual ~Trie();
};


#endif //ALGORITHM_TRIE_H
