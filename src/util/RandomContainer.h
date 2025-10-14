/**
 *
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/22
 *
 */
#ifndef ALGORITHM_RANDOM_CONTAINER_H
#define ALGORITHM_RANDOM_CONTAINER_H

#include "../lang/Array.h"
#include "Random.h"

template<class T>
class RandomContainer {
private:
    SequentialAccessibleContainer<T> &container;
    bool sequenceContainer;
public:

    static Array<T> shuffle(const Array<T> &array, Array<T> &target);

    // 给一个的数组 , 每次都能从这个数组中随机选一个值
    //      随机一个下标,然后返回下标即可
    explicit RandomContainer(const Array<T> &container) : container(container), sequenceContainer(true) {}

    // 给出一个集合(map), key: count; 能依据count的概率加权选出key的值
    //      Map底层依然有序, 依据此次序, count累加: map[index].count += map[index-1].count
    //      然后随机一个值(最后的总和count), 按次序遍历map, 每经过一个元素减去count: randomNum -= map[index].count
    //      当randomNum终于等于0时, 那个让它为0的数作为返回值
    T randomCatch();

};

template<class T>
T RandomContainer<T>::randomCatch() {
    return sequenceContainer ? T() : T();
}

/**
 * 给一个数组, 抽乱它(洗牌)<p>
 * 随机一个值, 作为索引, 如果本索引有值, 就往后放, 直到找到第一个没有值的<p>
 * @return target
 */
template<class T>
Array<T> RandomContainer<T>::shuffle(const Array<T> &array, Array<T> &target) {
    if (array.getSize() != target.getSize()) {
        throw IllegalArgumentException();
    }
    int length = array.getSize();
    bool mark[length];
    for (int i = 0; i < length; ++i) {
        mark[i] = false;
    }
    for (int i = 0; i < length; ++i) {
        unsigned int randomIndex = Random::unsignedInt() % length;
        for (; mark[randomIndex]; (++randomIndex) %= length);
        mark[randomIndex] = true;
        target[randomIndex] = array[i];
    }
    return target;
}


#endif //ALGORITHM_RANDOM_CONTAINER_H
