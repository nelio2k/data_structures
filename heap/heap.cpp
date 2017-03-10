#include <iostream>
#include <queue>
#include <vector>

template <typename T>
void printQueue(T &q) {
    while (!q.empty()) {
        std::cout << "Queue top: " << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

int main() {

    // By default, max heap
    std::priority_queue<int> q;

    std::vector<int> testVec;
    for (int i = 0; i < 10; ++i) {
        testVec.emplace_back(i);
    }
    for (auto const &number : testVec) {
        q.push(number);
    }

    std::cout << "Max queue/heap: " << std::endl;
    printQueue(q);

    // Make a min heap
    std::priority_queue<int, std::vector<int>, std::greater<int>> q2;
    for (auto const &number : testVec) {
        q2.push(number);
    }

    std::cout << "Min queue/heap: " << std::endl;
    printQueue(q2);

    return 0;
}
