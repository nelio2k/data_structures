#include <stdlib.h>
#include <mutex>
#include <iostream>

template <typename T>
class DataNode {
public:
    explicit DataNode(T inData)
        : data(inData),
          prev(nullptr),
          next(nullptr)
    {}

    ~DataNode() {}

    T data;
    DataNode *prev;
    DataNode *next;
};

template <typename T>
class CQueue {
public:
    CQueue()
      : first(nullptr),
        last(nullptr)
    {}
    ~CQueue();
    void push(T data);
    T pop();

private:
    // Queue access mutex
    std::mutex mutex;

    // pointers to the first and last of the queue
    DataNode<T> *first;
    DataNode<T> *last;
};

// Have to delete elements
template <class T>
CQueue<T>::~CQueue<T>() {
    DataNode<T> *curr, *next;
    curr = first;
    while (curr) {
        next = curr->next;
        delete curr;
        curr = next;
    }
}

template <class T>
void CQueue<T>::push(T data) {
    std::lock_guard<std::mutex> lk(mutex);
    DataNode<T> *nodePtr = new DataNode<T>(data);

    if (!first) {
        // assert not last
        first = nodePtr;
        last = nodePtr;
    } else {
        last->next = nodePtr;
        nodePtr->prev = last;
        last = nodePtr;
    }
}

template <class T>
T CQueue<T>::pop() {
    std::lock_guard<std::mutex> lk(mutex);
    T retVal = std::move(first->data);

    DataNode<T> *temp = first;
    first = first->next;
    if (first)
        first->prev = nullptr;
    
    delete temp;
    return retVal;
}

int main() {
    CQueue<int> intQueue;
    std::cout << "Pushing 1" << std::endl;;
    intQueue.push(1);
    std::cout << "Pushing 2" << std::endl;;
    intQueue.push(2);

    auto ret = intQueue.pop();
    std::cout << "Popping 1: " << ret << std::endl;;
    ret = intQueue.pop();
    std::cout << "Popping 2: " << ret << std::endl;;

    return 0;
}
