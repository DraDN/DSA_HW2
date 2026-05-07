#include "Queue.hpp"

template <typename T>
tools::Queue_t::ResultType tools::Queue<T>::enqueue(T element) {
    if (size == QUEUE_MAX_SIZE) {
        return ResultType::FAILURE;
    }

    element_array[tail] = element;
    tail = (tail + 1) % QUEUE_MAX_SIZE;
    size++;
    
    return ResultType::SUCCESS;
}

template <typename T>
tools::Optional<T> tools::Queue<T>::dequeue() {
    if (isEmpty()) return tools::nullopt;

    T element = element_array[head];
    head = (head + 1) % QUEUE_MAX_SIZE;
    size--;

    return element;
}

template <typename T>
tools::Optional<T> tools::Queue<T>::peek() {
    if (isEmpty()) return tools::nullopt;
    return element_array[head];
}
