#include <stdlib.h>
#include <iostream>

template <typename T>
struct Tree {
    T data;

    Tree<T> *right;
    Tree<T> *left;
    Tree<T> *parent;
};

using CallFn = void(Tree<int> *tree);

void printIntTree(Tree<int> *tree) {
    std::cout << tree->data << " ";
}

template <class T>
void traverseInOrderTree(Tree<T> *head, CallFn func) {
    Tree<T> *curr = head;
    bool leftDone(false);
    bool done(false);

    if (!curr) return;

    while (!done) {
        while ((curr->left) && !leftDone) {
            curr = curr->left;
        }
        func(curr);
        leftDone = true;
        if (curr->right) {
            leftDone = false;
            curr = curr->right;
        } else if (curr->parent) {
            while ((curr->parent && (curr->parent->right == curr))) {
                curr = curr->parent;
            }
            // This is in the case where we're done with the right side and as we're done traversing back up
            if (!curr->parent) break;

            // This is the case where we're just coming back up from the left, one level only.
            if (curr->parent && (curr->parent->left == curr)) {
                curr = curr->parent;
            }
        } else {
            done = true;
        }
    }
}

int main () {
    /**
     * Create a tree with diff leaf nodes that print them in order of
     */
    Tree<int> tree1;
    tree1.data = 1;

    Tree<int> tree2;
    tree2.data = 2;

    Tree<int> tree3;
    tree3.data = 3;

    Tree<int> tree4;
    tree4.data = 4;

    Tree<int> tree5;
    tree5.data = 5;

    Tree<int> tree6;
    tree6.data = 6;

    Tree<int> tree7;
    tree7.data = 7;

    Tree<int> tree8;
    tree8.data = 8;

    // top
    tree6.parent = nullptr;
    tree6.right = &tree7;
    tree6.left = &tree4;

    // left from top
    tree4.right = &tree5;
    tree4.left = &tree2;
    tree4.parent = &tree6;

    tree5.right = nullptr;
    tree5.left = nullptr;
    tree5.parent = &tree4;

    tree2.right = &tree3;
    tree2.left = &tree1;
    tree2.parent = &tree4;

    tree3.right = nullptr;
    tree3.left = nullptr;
    tree3.parent = &tree2;

    tree1.right = nullptr;
    tree1.left = nullptr;
    tree1.parent = &tree2;

    // right from top
    tree7.parent = &tree6;
    tree7.left = nullptr;
    tree7.right = &tree8;

    tree8.parent = &tree7;
    tree8.left = nullptr;
    tree8.right = nullptr;

    auto lambda = [](Tree<int> *node) {
        std::cout << node->data << " ";
    };
    // traverseInOrderTree<int>(&tree6, printIntTree);
    traverseInOrderTree<int>(&tree6, lambda);
    return 0;
}
