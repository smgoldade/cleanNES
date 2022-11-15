#ifndef _THREADSAFEQUEUE_H_
#define _THREADSAFEQUEUE_H_
#include <mutex>
#include <queue>

template <typename T>
class ThreadSafeQueue {
public:
    auto clear() noexcept -> void;
    auto empty() noexcept -> bool;
    auto size() noexcept -> size_t;
    auto pop() -> void;
    auto front() -> T&;
    auto back_or_nullptr() -> T*;
    auto push(const T& item) -> void;
    auto push(const T&& item) -> void;
    auto lock() -> void;
    auto unlock() -> void;
private:
    std::mutex mutex;
    std::deque<T> queue;
};

#include "ThreadSafeQueue.tpp"
#endif //_THREADSAFEQUEUE_H_