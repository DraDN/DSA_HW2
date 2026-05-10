#pragma once

#include "Optional.hpp"
#include "Queue.hpp"
#include <memory>

namespace tools {

    /// @brief Binary search tree
    /// @tparam T The data type to store
    template <typename T>
    class BST {
        private: 
            /// @brief Node of the binary search tree
            /// @tparam T The data type it stores
            /// @note Creates a copy of the data
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
            BST(const BST&) = delete; // disable copy constructors
            BST& operator=(const BST&) = delete;

            /// @brief Inserts an element into the tree
            /// @param value The data/value to insert
            void insert(T value) { insert(value, root); }

            /// @brief Removes an element from the tree
            /// @param value The data/value to remove
            void remove(T value) { remove(value, root); }


            /// @brief Finds an element
            /// @param value The data/value to search for
            /// @return `tools::Optional<T>` containing the value if found
            ///
            /// `tools::nullopt` otherwise
            tools::Optional<T> find(T value) const { return find(value, root); }

            /// @brief Finds all elements within a range
            /// @param min The lower bound of the search
            /// @param max The upper bound of the search
            /// @param result A queue to store the found elements
            void findInRange(T min, T max, tools::Queue<T>& result) const { findInRange(min, max, result, root); }

            /// @brief Finds the first element that makes the criterion return true
            /// @note This is a linear search and doesn't make use of the tree stucture for efficiency
            /// @tparam Func A function that returns a boolean
            /// @param criterion The criterion function to consider the element as found
            /// @return `tools::Optional<T>` containing the value if found
            ///
            /// `tools::nullopt` otherwise
            template <typename Func>
            tools::Optional<T> findLinear(Func criterion) const { return findLinear(criterion, root); }

            /// @brief Traverses the tree in order
            /// @tparam Func The function to apply to each element when visiting
            template <typename Func>
            void traverseInOrder(Func function) const { traverseInOrder(function, root); }

            /// @brief Traverses the tree pre order
            /// @tparam Func The function to apply to each element when visiting
            template <typename Func>
            void traversePreOrder(Func function) const { traversePreOrder(function, root); }

            /// @brief Traverses the tree post order
            /// @tparam Func The function to apply to each element when visiting
            template <typename Func>
            void traversePostOrder(Func function) const { traversePostOrder(function, root); }

            /// @brief Returns the minimum element in the tree
            /// @return `tools::Optional<T>` containing the value if found
            ///
            /// `tools::nullopt` if the tree is empty
            tools::Optional<T> getMin() const;

            /// @brief Returns the maximum element in the tree
            /// @return `tools::Optional<T>` containing the value if found
            ///
            /// `tools::nullopt` if the tree is empty
            tools::Optional<T> getMax() const;

            /// @brief Returns the k-th largest element in the tree
            /// @return `tools::Optional<T>` containing the value if found
            ///
            /// `tools::nullopt` if the tree doesn't contain at least k elements
            tools::Optional<T> getKthLargest(unsigned int k) const { return getKthLargest(k, root); }

            /// @brief Returns the lowest common ancestor of two elements
            /// @param value1 The first element
            /// @param value2 The second element
            /// @return `tools::Optional<T>` containing the value if found
            ///
            /// `tools::nullopt` if (1) one or both of the values are not in the tree or (2) the tree is empty / not enough elements or (3) the elements don't share a common ancestor
            tools::Optional<T> getLowestCommonAncestor(T value1, T value2) const { return getLowestCommonAncestor(value1, value2, root); }

            /// @brief Gives the height of the tree
            /// @return The height
            unsigned int getHeight() const { return getHeight(root); }

            /// @brief Gives the leafs of the tree via the `tools::Queue<T> result` queue 
            void getLeafs(tools::Queue<T>& result) const { return getLeafs(result, root); }

            /// @brief Checks if the tree is balanced
            /// @return `true` if the tree is balanced, `false` otherwise
            bool isBalanced() const { return isBalanced(root); }
        
        private:
            BSTNode* root = nullptr;
        
        private:
            /// helps deleting the tree by deleting each node recursively
            void destroy(BSTNode* node);

            /// gives the successor of a node in an in-order traversal - helper for removing a node
            BSTNode* in_order_successor(BSTNode* node);

            // private functions to help recursion
            void insert(T value, BSTNode*& node);
            void remove(T value, BSTNode*& node);

            tools::Optional<T> find(T value, const BSTNode* node) const;
            void findInRange(T min, T max, tools::Queue<T>& result, const BSTNode* node) const;

            template <typename Func>
            tools::Optional<T> findLinear(Func criterion, const BSTNode* node) const;

            template <typename Func>
            void traverseInOrder(Func function, const BSTNode* node) const;
            template <typename Func>
            void traversePreOrder(Func function, const BSTNode* node) const;
            template <typename Func>
            void traversePostOrder(Func function, const BSTNode* node) const;

            tools::Optional<T> getKthLargest(unsigned int& k, const BSTNode* node) const;
            tools::Optional<T> getLowestCommonAncestor(T value1, T value2, const BSTNode* node) const;

            unsigned int getHeight(const BSTNode* node) const;
            void getLeafs(tools::Queue<T>& result, const BSTNode* node) const;
            // unsigned int getNumberOfLeafs(const BSTNode* node) const;
            bool isBalanced(const BSTNode* node) const;
    };

}

#include "BST.tpp"
