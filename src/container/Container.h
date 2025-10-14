/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/22
 *
 */
#ifndef ALGORITHM_CONTAINER_H
#define ALGORITHM_CONTAINER_H

template<class T>
class Container {
public:
    [[nodiscard]] virtual int getSize() const = 0;

    [[nodiscard]] virtual bool empty() const = 0;
};


#endif //ALGORITHM_CONTAINER_H
