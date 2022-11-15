#include "ThreadSafeQueue.h"

template <typename T>
auto ThreadSafeQueue<T>::clear() noexcept -> void {
    std::lock_guard<std::mutex> lock(mutex);
    queue.clear();
}

template <typename T>
auto ThreadSafeQueue<T>::empty() noexcept -> bool {
    std::lock_guard<std::mutex> lock(mutex);
    return queue.empty();
}

template <typename T>
auto ThreadSafeQueue<T>::size() noexcept -> size_t {
    std::lock_guard<std::mutex> lock(mutex);
    return queue.size();
}

template <typename T>
auto ThreadSafeQueue<T>::pop() -> void {
    std::lock_guard<std::mutex> lock(mutex);
    queue.pop_front();
}

template <typename T>
auto ThreadSafeQueue<T>::front() -> T& {
    std::lock_guard<std::mutex> lock(mutex);
    return queue.front();
}

template <typename T>
auto ThreadSafeQueue<T>::back_or_nullptr() -> T* {
    std::lock_guard<std::mutex> lock(mutex);
    if(queue.empty()) {
        return nullptr;
    } else {
        return &queue.back();
    }
}

template <typename T>
auto ThreadSafeQueue<T>::push(const T& item) -> void {
    std::lock_guard<std::mutex> lock(mutex);
    queue.push_back(item);
}

template <typename T>
auto ThreadSafeQueue<T>::push(const T&& item) -> void {
    std::lock_guard<std::mutex> lock(mutex);
    queue.push_back(item);
}

template <typename T>
auto ThreadSafeQueue<T>::lock() -> void {
    mutex.lock();
}

template <typename T>
auto ThreadSafeQueue<T>::unlock() -> void {
    mutex.unlock();
}
