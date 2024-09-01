#ifndef HEAP_H
#define HEAP_H

#include <functional>
#include <iterator>
#include <vector>

template <typename T, typename Compare = std::less<T>> class Heap {
public:
  Heap(Compare compare = Compare()) : compare(compare) {}

  void push(const T &value) {
    heap.push_back(std::move(value));
    siftUp(heap.size() - 1);
  }

  const T &top() const { return heap.front(); }

  void pop() {
    if (!heap.empty()) {
      std::swap(heap.front(), heap.back());
      heap.pop_back();
      siftDown(0);
    }
  }

  bool empty() const { return heap.size() == 0; }

  size_t size() const { return heap.size(); }

  template<typename I>
  static void make_heap(I begin, I end) {
    make_heap(begin, end, std::less<typename std::iterator_traits<I>::value_type>());
  }

  template< typename I, typename Comp = std::less<I>>
  static void make_heap(I begin, I end, Comp comp) {
    auto n = std::distance(begin, end);
    for (auto i = n/2 - 1; i >= 0; --i) {
        heapify(begin, end, begin+i, comp);
    }
  }

private:
  Compare compare;
  std::vector<T> heap;

  void siftUp(size_t idx) {
    size_t parent;
    while (idx > 0) {
      parent = (idx - 1) / 2;
      if (compare(heap[idx], heap[parent])) {
        std::swap(heap[idx], heap[parent]);
        idx = parent;
      } else
        break;
    }
  }

  void siftDown(size_t idx) {
    size_t left, right, smallest;
    while ((left = idx * 2 + 1) < heap.size()) {
      right = left + 1;
      if (right < heap.size() && compare(heap[right], heap[left])) {
        smallest = right;
      } else {
        smallest = left;
      }
      if (compare(heap[smallest], heap[idx])) {
        std::swap(heap[smallest], heap[idx]);
        idx = smallest;
      } else
        break;
    }
  }

 template<typename I, typename Comp>
 static void heapify(I begin, I end, I root, Comp comp) {
    I rootTemp = root;
    I left = begin + std::distance(begin, root)*2+1;
    I right = begin + std::distance(begin, root)*2+2;
    if (left < end && comp(*rootTemp, *left)) {
        rootTemp = left;
    }
    if (right < end && comp(*rootTemp, *right)) {
        rootTemp = right;
    }
    if (rootTemp != root) {
        std::swap(*rootTemp, *root);
        heapify(begin, end, rootTemp, comp);
    }
 }
};

#endif // HEAP_H