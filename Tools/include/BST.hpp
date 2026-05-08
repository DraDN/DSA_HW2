#pragma once

#include "Optional.hpp"

namespace tools {

    template <typename T>
    class BST {
        public: 
            struct BSTNode {
                BSTNode* left = nullptr;
                BSTNode* right = nullptr;
                T* value;

                BSTNode(T value) : value(new T(value)) {};
                ~BSTNode() { delete value; }
            };

            typedef tools::Optional<BSTNode*> OptionalNode;

        public:
            BST() {};

            void insert(T value);
            void remove(T value);
            // OptionalNode find(T value);
            // OptionalNode findInRange(T min, T max);

            template <typename Func>
            void traverseInOrder(Func function, BSTNode* root = nullptr);
            template <typename Func>
            void traversePreOrder(Func function, BSTNode* root = nullptr);
            template <typename Func>
            void traversePostOrder(Func function, BSTNode* root = nullptr);

            T* getMin();
            T* getMax();
            T* getKthLargest(unsigned int k);

            unsigned int getHeight();
            unsigned int getNumberOfLeafs();
            bool isBalanced();
        
        public:
            BSTNode* root = nullptr;
    };

}