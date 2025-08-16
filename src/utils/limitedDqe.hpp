#ifndef LIMITEDDEQUE_H
#define LIMITEDDEQUE_H
#include <deque>
#include <iostream>
#include <deque>
#include <stdexcept>
#include <QDebug>

template <typename T>
class LimitedDqe : public std::deque<T> {
public:
    explicit LimitedDqe(size_t &&limit) : limit(limit) {}

    void push(const T& value) {
        if (this->size() >= limit) {
            this->pop_front(); // 移除栈底元素
        }
        this->push_back(value); // 压入新元素
    }


    T peek() const {
        if (this->empty()) {
            qDebug()<<"Stack is empty.";
            throw std::out_of_range("Stack is empty.");
        }
        return this->back(); // 查看栈顶元素
    }

    bool isEmpty() const {
        return this->empty();
    }

    size_t size() const {
        return std::deque<T>::size();
    }

    void stdcout() const {
        std::cout << "Stack Contents: ";
        for (const auto& item : *this) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

private:
    size_t limit; // 栈的最大容量
};
#endif // LIMITEDDEQUE_H
