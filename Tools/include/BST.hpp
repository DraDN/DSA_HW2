#pragma once

#include "Optional.hpp"
#include "Queue.hpp"
#include <memory>

namespace tools {

    template <typename T>
    class BST {
        private: 
            struct BSTNode {
                BSTNode* left = nullptr;
                BSTNode* right = nullptr;
                T* data;

                BSTNode(T data) : data(new T(data)) {};
                ~BSTNode() { delete data; }
            };

        public:
            BST() {};
            ~BST() { destroy(root); }
            BST(const BST&) = delete; // disable copy constructor
            BST& operator=(const BST&) = delete;

            void insert(T value) { insert(value, root); }
            void remove(T value) { remove(value, root); }

            tools::Optional<T> find(T value) const { return find(value, root); }
            void findInRange(T min, T max, tools::Queue<T>& result) const;

            template <typename Func>
            tools::Optional<T> findLinear(Func criterion) const { return findLinear(criterion, root); } // returns the first node that makes the criterion return true

            template <typename Func>
            void traverseInOrder(Func function) const { traverseInOrder(function, root); }
            template <typename Func>
            void traversePreOrder(Func function) const { traversePreOrder(function, root); }
            template <typename Func>
            void traversePostOrder(Func function) const { traversePostOrder(function, root); }

            tools::Optional<T> getMin() const;
            tools::Optional<T> getMax() const;
            tools::Optional<T> getKthLargest(unsigned int k) const;

            unsigned int getHeight() const { return getHeight(root); }
            unsigned int getNumberOfLeafs() const { return getNumberOfLeafs(root); }
            bool isBalanced() const { return isBalanced(root); }
        
        private:
            BSTNode* root = nullptr;
        
        private:
            void destroy(BSTNode* node);

            BSTNode* in_order_successor(BSTNode* node);

            // private functions to help recursion
            void insert(T value, BSTNode*& node);
            void remove(T value, BSTNode*& node);

            tools::Optional<T> find(T value, const BSTNode* node) const;

            template <typename Func>
            tools::Optional<T> findLinear(Func criterion, const BSTNode* node) const;

            template <typename Func>
            void traverseInOrder(Func function, const BSTNode* node) const;
            template <typename Func>
            void traversePreOrder(Func function, const BSTNode* node) const;
            template <typename Func>
            void traversePostOrder(Func function, const BSTNode* node) const;

            unsigned int getHeight(const BSTNode* node) const;
            unsigned int getNumberOfLeafs(const BSTNode* node) const;
            bool isBalanced(const BSTNode* node) const;
    };

}

#include "BST.tpp"
