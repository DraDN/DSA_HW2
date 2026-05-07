#pragma once

#include "Optional.hpp"

namespace tools {

    #define QUEUE_MAX_SIZE 100

    class Queue_t {
        public:
            enum class ResultType {
                SUCCESS,
                FAILURE
            };

            bool isEmpty() const { return size == 0; }
            unsigned int getSize() const { return size; }
        
        protected:
            unsigned int head = 0, tail = 0;
            unsigned int size = 0;
    };

    template<typename T>
    class Queue : public Queue_t {
        public:
            Queue() {};

            /// @brief Enqueues an element
            /// @param element `T` value to queue
            /// @return `tools::Queue_t::ResultType::FAILURE` - if the queue is full
            ///
            /// `tools::Queue_t::ResultType::SUCCESS` - if enqueue was successful
            ResultType enqueue(T element);

            /// @brief Dequeues an element
            /// @return `tools::Optional<T>` - containing the dequeued element
            /// 
            /// `tools::nullopt` - if the queue is empty
            Optional<T> dequeue();

            /// @brief Peeks at the first element
            /// @return `tools::Optional<T>` - containing the first element
            /// 
            /// `tools::nullopt` - if the queue is empty
            Optional<T> peek();

        private:
            T element_array[QUEUE_MAX_SIZE];
    };
}

#include "Queue.tpp"
