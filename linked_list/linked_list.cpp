#include <stdlib.h>
#include <iostream>

template <typename T>
struct Node {
    explicit Node(T &data);
    T data;

    Node *next;
};

template <class T>
Node<T>::Node(T &data)
    :   next(nullptr),
        data(std::move(data))
{}

/**
 * Custom implementation of linked list
 */
template <typename T>
class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    // Operators on this linked ist
    void push_back(T &data);
    void push_back(T data);
    void print();
    void reverse();
private:
    Node<T> *head;
};

template <class T>
LinkedList<T>::LinkedList()
    :   head(nullptr)
{}

template <class T>
LinkedList<T>::~LinkedList() {
    Node<T> *curr(head);
    Node<T> *temp(nullptr);

    while (curr) {
        temp = curr ? curr->next : nullptr;
        delete curr;
        curr = temp;
    }
}

template <class T>
void LinkedList<T>::push_back(T data) {
    T dataCopy = data;
    Node<T> *newPtr = new Node<T>(dataCopy);
    if (!head) {
        head = newPtr;
    } else {
        auto curr = head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = newPtr;
    }
}

template <class T>
void LinkedList<T>::push_back(T &data) {
    Node<T> *newPtr = new Node<T>(data);
    if (!head) {
        head = newPtr;
    } else {
        auto curr = head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = newPtr;
    }
}

template <class T>
void LinkedList<T>::print() {
    for (auto curr = head; curr != nullptr; curr = curr->next) {
        std::cout << curr->data << " ";
    }
    std::cout << std::endl;
}

template <class T>
void LinkedList<T>::reverse() {
    Node<T> *curr, *prev, *next;
    curr = head;
    prev = nullptr;
    next = curr ? curr->next : nullptr;
    if (!curr) return;
    while (curr) {
        curr->next = prev;
        prev = curr;
        curr = next;
        if (next)
            next = next->next;
    }
    head = prev;
}

int main() {

    LinkedList<int> ll;
    ll.push_back(1);
    ll.push_back(2);
    ll.push_back(3);
    ll.print();
    ll.reverse();
    ll.print();

    return 0;
}
