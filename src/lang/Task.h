#ifndef ALGORITHM_TASK_H
#define ALGORITHM_TASK_H

#include <ostream>
#include "Runnable.h"

template<class T>
class Task {
private:
    T *task;
    int priority;
public:
    Task(T *task, int priority) : task(task), priority(priority) {
    }

    Task() : Task(nullptr, 0) {};

    [[nodiscard]] const T &getTaskMsg() const {
        return task;
    }

    void setTaskMsg(const T &task_) {
        Task::task = task_;
    }

    [[nodiscard]] int getPriority() const {
        return priority;
    }

    void setPriority(int priority_) {
        Task::priority = priority_;
    }

    int operator-(const Task &t) const {
        return this->priority - t.priority;
    }

    friend std::ostream &operator<<(std::ostream &os, const Task &obj) {
        obj.execute();
        return os << ": " << obj.priority;
    }

    void execute() const {
        this->task->run();
    }
};


#endif //ALGORITHM_TASK_H
