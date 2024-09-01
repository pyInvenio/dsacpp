#include "../include/datastructures/heap.h"
#include <vector>

int main() {
  std::vector<int> test{1, 2, 3, 4, 5, 6};
  Heap<int>::make_heap(test.begin(), test.end());
  for (const auto &i : test)
    printf("%d\n", i);

    Heap<std::pair<std::string, int>> heap;
    heap.push({"A", 1});
    heap.push({"A", 2});
    heap.push({"B", 3});
    heap.push({"B", 1});
    heap.push({"C", 2});
    heap.push({"C", 3});
    printf("%s, %d\n", heap.top().first.c_str(), heap.top().second);
    heap.pop();
    printf("%s, %d\n", heap.top().first.c_str(), heap.top().second);
  return 0;
}