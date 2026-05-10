#include "BST.hpp"

#include <cmath>

template <typename T>
void tools::BST<T>::destroy(BSTNode* node) {
    if (!node) return;

    destroy(node->left);
    destroy(node->right);

    delete node;
}

/// ==== I/O ====

template <typename T>
void tools::BST<T>::insert(T value, BSTNode*& node) {
    if (!node) node = new BSTNode(value);
    else if (value < *node->data) insert(value, node->left);
    else if (value > *node->data) insert(value, node->right);
}

template <typename T>
auto tools::BST<T>::in_order_successor(BSTNode* node) -> BSTNode* {
    tools::BST<T>::BSTNode* current = node->right;
    while (current && current->left) current = current->left;
    return current;
}

template <typename T>
void tools::BST<T>::remove(T value, BSTNode*& node) {
    if (!node) return;

    if (value < *node->data) remove(value, node->left);
    else if (value > *node->data) remove(value, node->right);

    else if (node->left && node->right) { // if it has two children
        tools::BST<T>::BSTNode* successor = in_order_successor(node);
        *node->data = *successor->data;
        remove(*successor->data, node->right); // will remove the original successor - rududent since we've copied into the deleted spot

    } else { // has only 1 child
        tools::BST<T>::BSTNode* child = node->left ? node->left : node->right;
        delete node;
        node = child;
    }
}

/// ==== FINDS ====

template <typename T>
tools::Optional<T> tools::BST<T>::find(T value, const BSTNode* node) const {
    if (!node) return tools::nullopt;

    if (value < *node->data) return find(value, node->left);
    else if (value > *node->data) return find(value, node->right);
    else return tools::Optional<T>(*node->data);
}

// template <typename T>
// tools::Optional<T> tools::BST<T>::findInRange(T min, T max, const BSTNode* node) const {
//     if (!node) return tools::nullopt;

//     if (*node->data < min) return findInRange(min, max, node->right);
//     else if (*node->data > max) return findInRange(min, max, node->left);
//     else return tools::Optional<T>(*node->data);
// }

template <typename T>
void tools::BST<T>::findInRange(T min, T max, tools::Queue<T>& result, const BSTNode* node) const {
    if (!node) return;

    if (*node->data < min) findInRange(min, max, result, node->right);
    else if (*node->data > max) findInRange(min, max, result, node->left);
    else {
        findInRange(min, max, result, node->left);
        result.enqueue(*node->data);
        findInRange(min, max, result, node->right);
    }
}

template <typename T>
template <typename Func>
tools::Optional<T> tools::BST<T>::findLinear(Func criterion, const BSTNode* node) const {
    if (!node) return tools::nullopt;

    if (criterion(*node->data)) return tools::Optional<T>(*node->data); 

    tools::Optional<T> left_result = findLinear(criterion, node->left);
    if (left_result) return left_result;

    return findLinear(criterion, node->right);
}

/// ==== TRAVERSALS ====

template <typename T>
template <typename Func>
void tools::BST<T>::traverseInOrder(Func function, const BSTNode* node) const {
    if (!node) return;
    traverseInOrder(function, node->left);
    function(*node->data);
    traverseInOrder(function, node->right);
}

template <typename T>
template <typename Func>
void tools::BST<T>::traversePreOrder(Func function, const BSTNode* node) const {
    if (!node) return;
    function(*node->data);
    traversePreOrder(function, node->left);
    traversePreOrder(function, node->right);
}

template <typename T>
template <typename Func>
void tools::BST<T>::traversePostOrder(Func function, const BSTNode* node) const {
    if (!node) return;
    traversePostOrder(function, node->left);
    traversePostOrder(function, node->right);
    function(*node->data);
}

/// ==== TREE INFO ====

template <typename T>
unsigned int tools::BST<T>::getHeight(const BSTNode* node) const {
    if (!node) return 0;
    
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

template <typename T>
// unsigned int tools::BST<T>::getNumberOfLeafs(const BSTNode* node) const {
void tools::BST<T>::getLeafs(tools::Queue<T>& result, const BSTNode* node) const {
    if (!node) return;

    if (!node->left && !node->right) {
        result.enqueue(*node->data); // if it's a leaf
        return;
    }

    getLeafs(result, node->left);
    getLeafs(result, node->right);
}

template <typename T>
bool tools::BST<T>::isBalanced(const BSTNode* node) const {
    if (!node) return true;

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return std::abs(leftHeight - rightHeight) <= 1 && isBalanced(node->left) && isBalanced(node->right);
}

/// ==== MIN / MAX ====

template <typename T>
tools::Optional<T> tools::BST<T>::getMin() const {
    if (!root) return tools::nullopt;

    tools::BST<T>::BSTNode* current = root;
    while (current->left) current = current->left;

    return tools::Optional<T>(*current->data);
}

template <typename T>
tools::Optional<T> tools::BST<T>::getMax() const {
    if (!root) return tools::nullopt;

    tools::BST<T>::BSTNode* current = root;
    while (current->right) current = current->right;

    return tools::Optional<T>(*current->data);
}

template <typename T>
tools::Optional<T> tools::BST<T>::getKthLargest(unsigned int& k, const BSTNode* node) const {
    if (!node) return tools::nullopt;

    tools::Optional<T> right_result = getKthLargest(k, node->right);
    if (right_result) return right_result;
    else if (k-- == 1) return tools::Optional<T>(*node->data); // here, you visit the node - decrement one from k
    else return getKthLargest(k, node->left);
}

template <typename T>
tools::Optional<T> tools::BST<T>::getLowestCommonAncestor(T value1, T value2, const BSTNode* node) const {
    if (!node) return tools::nullopt;

    if (!node->left && !node->right) return tools::nullopt;

    if (value1 < *node->data && value2 < *node->data) return getLowestCommonAncestor(value1, value2, node->left);
    else if (value1 > *node->data && value2 > *node->data) return getLowestCommonAncestor(value1, value2, node->right);
    else return tools::Optional<T>(*node->data);
}

