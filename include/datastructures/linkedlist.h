#ifndef LL_H
#define LL_H
#include <functional>

template <typename T> class ListNode {
public:
  ListNode() : data(T()), nextNode(nullptr){};

  ListNode(const T &value) : data(value), nextNode(nullptr){};

  ListNode(T &&value) : data(std::move(value)), nextNode(nullptr){};

  ListNode(ListNode *node, const T &value) noexcept
      : data(std::move(value)), nextNode(node){};

  ListNode(ListNode *node, T &&value) noexcept
      : data(std::move(value)), nextNode(node){};

  ListNode(const ListNode &other) : data(other.data), nextNode(nullptr) {
    if (other.nextNode) {
      nextNode = new ListNode(*other.nextNode);
    }
  }

  ~ListNode() { delete nextNode; }

  const ListNode *next() const { return nextNode; }

  const T &getData() const { return data; }

  void setData(const T &newData) { data = newData; }

  void setData(T &&newData) { data = std::move(newData); }

  void setNext(ListNode *next) { nextNode = next; }

  ListNode &operator=(const ListNode &other) {
    if (this != &other) {
      data = other.data;
      ListNode *newNextNode = nullptr;
      if (other.nextNode)
        newNextNode = new ListNode(*other.nextNode);
      delete nextNode;
      nextNode = newNextNode;
    }
    return *this;
  }

private:
  ListNode *nextNode;
  T data;
};

template <typename T> class LinkedList {
public:
  LinkedList() : head(nullptr), tail(head), size(0){};

  void push_front(ListNode<T> *node) {
    node->setNext(head);
    head = node;
    if (!tail)
      tail = head;
    size++;
  }

  void push_front(const T &data) {
    ListNode<T> *newNode = new ListNode<T>(data);
    newNode->setNext(head);
    head = newNode;
    if (!tail)
      tail = head;
    size++;
  }

  void push_front(T &&data) {
    ListNode<T> *newNode = new ListNode<T>(std::move(data));
    newNode->setNext(head);
    head = newNode;
    if (!tail)
      tail = head;
    size++;
  }

  void pop_front() {
    if (empty())
      return;
    ListNode<T> *oldHead = head;
    head = head->next();
    if (head == nullptr)
      tail = nullptr;
    delete oldHead;
    size--;
  }

  void push_back(ListNode<T> *node) {
    if (!head) {
      head = node;
      tail = head;
    } else {
      tail->setNext(node);
      tail = node;
    }
    size++;
  }

  void push_back(const T &data) {
    ListNode<T> *newNode = new ListNode<T>(data);
    if (!head) {
      head = newNode;
      tail = head;
    } else {
      tail->setNext(newNode);
      tail = newNode;
    }
    size++;
  }

  void push_back(T &&data) {
    ListNode<T> *newNode = new ListNode<T>(std::move(data));
    if (!head) {
      head = newNode;
      tail = head;
    } else {
      tail->setNext(newNode);
      tail = newNode;
    }
    size++;
  }

  void pop_back() {
    if (empty())
      return;
    if (size == 1) {
      delete head;
      head = tail = nullptr;
    } else {
      ListNode<T> *cur = head;
      while (cur->next() != tail) {
        cur = cur->next();
      }
      delete tail;
      tail = cur;
      tail->setNext(nullptr);
    }
    size--;
  }

  const size_t getSize() const { return size; }

  bool empty() const { return size == 0; }

  ListNode<T> *front() { return head; }

  ListNode<T> *back() { return tail; }

  ListNode<T> *search(const T &searchValue) {
    ListNode<T> *temp = head;
    while (temp != nullptr) {
      if (temp->getData() == searchValue)
        return temp;
      temp = temp->next();
    }
    return nullptr;
  }

  ListNode<T> *getAt(size_t idx) {
    if (idx >= size)
      return nullptr;
    ListNode<T> *temp = head;
    for (size_t i = 0; i < idx; ++i) {
      temp = temp->next();
    }
    return temp;
  }

  bool deleteAt(size_t idx) {
    if (idx >= size)
      return false;

    if (idx == 0) {
      pop_front();
    } else if (idx == size - 1) {
      pop_back();
    } else {
      ListNode<T> *temp = head;
      ListNode<T> *prev = nullptr;
      for (size_t i = 0; i < idx; ++i) {
        prev = temp;
        temp = temp->next();
      }
      prev->setNext(temp->next());
      delete temp;
      size--;
    }
    return true;
  }

private:
  ListNode<T> *head;
  ListNode<T> *tail;
  size_t size;
};

#endif // LL_H