#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stack>

template <typename T>
struct Tree {
    T data;
    explicit Tree(T);

    Tree<T> *right;
    Tree<T> *left;
};

template <class T>
Tree<T>::Tree(T inData)
 :  data(inData),
    right(nullptr),
    left(nullptr) {}

using CallFn = void(Tree<int> *tree);

template <class T>
void traverseTreePreOrderRecursive(Tree<T> *tree, CallFn fn) {
    if (!tree) return;
    fn(tree);
    
    traverseTreePreOrderRecursive(tree->left, fn);
    traverseTreePreOrderRecursive(tree->right, fn);
}

template <class T>
void traverseTreePreOrderIterative(Tree<T> *tree, CallFn fn) {
    std::stack<Tree<T>*> tStack;
    bool leftDone(false);

    if (!tree) { return; }
    auto t = tree;

    while (true) {
        fn(t);

        if (!leftDone && t->left) {
            tStack.push(t);
            t = t->left;
        } else if (t->right) {
            tStack.push(t);
            t = t->right;
            leftDone = false;
        } else {
            leftDone = true;
            if (tStack.empty()) {
                break;
            } else {
                auto prev = t;
                t = tStack.top();
                tStack.pop();
                if (prev == t->right) {
                    while (!tStack.empty() && prev == t->right) {
                        prev = t;
                        t = tStack.top();
                        tStack.pop();
                    }
                    if (t == tree) {
                        break;
                    }
                } else if (t->right) {
                    t = t->right;
                }
            }
        }
    }
}

int main () {
    /**
     *
     *      1
     *     / \
     *    2   5
     *   / \
     *  3   4
     */
    std::vector<Tree<int>> treeList;
    for (int i=1; i <= 5; ++i) {
        treeList.emplace_back(i);
    }

    treeList[0].right = &(treeList[4]);
    treeList[0].left  = &(treeList[1]);
    treeList[1].right = &(treeList[3]);
    treeList[1].left  = &(treeList[2]);

    auto lambda = [](Tree<int> *node) {
        std::cout << node->data << " ";
    };

    std::cout << "Recursively: " << std::endl;
    traverseTreePreOrderRecursive(&(treeList[0]), lambda);
    std::cout << std::endl;

    std::cout << "Iteratively: " << std::endl;
    traverseTreePreOrderIterative(&(treeList[0]), lambda);
    std::cout << std::endl;
    return 0;
}
