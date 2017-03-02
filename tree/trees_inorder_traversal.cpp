#include <stdlib.h>
#include <iostream>
#include <stack>

template <typename T>
struct Tree {
    T data;
    Tree<T>();
    explicit Tree<T>(T inData);

    Tree<T> *right;
    Tree<T> *left;
};

template <class T>
Tree<T>::Tree()
    :   right(nullptr),
        left(nullptr) {}

template <class T>
Tree<T>::Tree(T inData)
    :   data(inData),
        right(nullptr),
        left(nullptr) {}

using CallFn = void(Tree<int> *tree);

void printIntTree(Tree<int> *tree) {
    std::cout << tree->data << " ";
}

template <class T>
void traverseTwoTreesInOrder(Tree<T> *tree1, Tree<T> *tree2, CallFn fn) {
    std::stack<Tree<T>*> t1Stack;
    std::stack<Tree<T>*> t2Stack;
    Tree<T> *t1 = tree1;
    Tree<T> *t2 = tree2;
    bool t1LeftDone(false);
    bool t2LeftDone(false);
    bool t1GoUp(false);
    bool t2GoUp(false);
    bool t1TreeDone(false);
    bool t2TreeDone(false);

    while (true) {

        t1GoUp = false;
        t2GoUp = false;

        while (t1->left && !t1LeftDone) {
            t1Stack.push(t1);
            t1 = t1->left;
        }
        while (t2->left && !t2LeftDone) {
            t2Stack.push(t2);
            t2 = t2->left;
        }
        
        if (!t1TreeDone && !t2TreeDone) {
            if (t1->data <= t2->data) {
                fn(t1);
                t1LeftDone = true;
                t1GoUp = true;
            } else {
                fn(t2);
                t2LeftDone = true;
                t2GoUp = true;
            }
        } else if (t1TreeDone && !t2TreeDone) {
            fn(t2);
            t2LeftDone = true;
            t2GoUp = true;
        } else if (!t1TreeDone && t2TreeDone) {
            fn(t1);
            t1LeftDone = true;
            t1GoUp = true;
        } else {
            break;
        }

        if (t1GoUp) {
            if (t1->right) {
                t1LeftDone = false;
                t1Stack.push(t1);
                t1 = t1->right;
            } else {
                if (!t1Stack.empty()) {
                    // We go either up one level if we're coming from the left
                    // or if we're coming back up from the right, keep going
                    auto t1Prev = t1;
                    t1 = t1Stack.top();
                    t1Stack.pop();
                    if (t1Prev == t1->right) {
                        t1TreeDone = true;
                        while (!t1Stack.empty() && (t1Prev == t1->right)) {
                            t1Prev = t1;
                            t1 = t1Stack.top();
                            t1Stack.pop();
                        }
                    } else {
                        // one level only
                    }
                }
            }
        } else if (t2GoUp) {
            if (t2->right) {
                t2LeftDone = false;
                t2Stack.push(t2);
                t2 = t2->right;
            } else {
                if (!t2Stack.empty()) {
                    // We go either up one level if we're coming from the left
                    // or if we're coming back up from the right, keep going
                    auto t2Prev = t2;
                    t2 = t2Stack.top();
                    t2Stack.pop();
                    if (t2Prev == t2->right) {
                        t2TreeDone = true;
                        while (!t2Stack.empty() && (t2Prev == t2->right)) {
                            t2Prev = t2;
                            t2 = t2Stack.top();
                            t2Stack.pop();
                        }
                    } else {
                        // We only go up one
                    }
                }
            }
        } else {
            break;
        }
    }

}

int main() {
    /**
     * We're going to make two different trees
     * 
     *      3
     *     / \
     *    1   5
     *
     *      4
     *     / \
     *    2   6
     *
     * And should print out 1 2 3 4 5 6
     */

    Tree<int> tree1(1);
    Tree<int> tree2(2);
    Tree<int> tree3(3);
    Tree<int> tree4(4);
    Tree<int> tree5(5);
    Tree<int> tree6(6);

    // tree1
    tree3.right = &tree5;
    tree3.left = &tree1;
 
    // tree2
    tree4.right = &tree6;
    tree4.left = &tree2;

    auto printLambda = [](Tree<int> *tree) {
        std::cout << tree->data << " ";
        getchar();
    };
    traverseTwoTreesInOrder(&tree3, &tree4, printLambda);

    std::cout << std::endl;

    return 0;
}
