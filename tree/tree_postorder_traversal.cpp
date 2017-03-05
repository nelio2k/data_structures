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
void traverseTreePostOrderIterative(Tree<T> *tree, CallFn fn) {
    /**
     * Postorder traversal goes like this:
     * 3 4 2 6 5 1
     */
    Tree<T> *t = tree;
    Tree<T> *prev(nullptr);
    std::stack<Tree<T>*> tStack;
    bool leftDone(false);
    bool rightDone(false);

    if (!t) return;

    char dummy;
    while (true) {
        while (!rightDone && !leftDone && (t->left)) {
            tStack.push(t);
            t = t->left;
        }

        if (!t->left) {
            leftDone = true;
        }

        if (!rightDone && t->right) {
            tStack.push(t);
            t = t->right;
            leftDone = false;
        } else {
            rightDone = true;
            fn(t);

            if (tStack.empty()) break;

            // Go back up one
            prev = t;
            t = tStack.top();
            tStack.pop();
            if (prev == t->left) {
                if (t->right) {
                    leftDone = false;
                    rightDone = false;
                    tStack.push(t);
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
     *   / \   \
     *  3   4   6
     */
    std::vector<Tree<int>> treeList;
    for (int i=1; i <= 6; ++i) {
        treeList.emplace_back(i);
    }

    treeList[0].right = &(treeList[4]);
    treeList[0].left  = &(treeList[1]);
    treeList[1].right = &(treeList[3]);
    treeList[1].left  = &(treeList[2]);
    treeList[4].right = &(treeList[5]);

    auto lambda = [](Tree<int> *node) {
        std::cout << node->data << " ";
    };

    std::cout << "Iteratively: " << std::endl;
    traverseTreePostOrderIterative(&(treeList[0]), lambda);
    std::cout << std::endl;
    return 0;
}
