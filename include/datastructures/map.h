#ifndef MAP_H
#define MAP_H

#include <memory>
#include <stdexcept>
#include <utility>

template <typename K, typename V> class Map {
public:
  Map()
      : values(new V[2]()), keys(new K[2]()), filled(new bool[2]()),
        capacity(2), size(1){};

  ~Map() {
    delete[] values;
    delete[] keys;
    delete[] filled;
  }

  bool find(const K &key) const {
    size_t index = std::hash<K>(key) % capacity;
    size_t i = 1;
    size_t original = index;
    while (filled[index] && keys[index] != key) {
      index += i * i % capacity;
      ++i;
      if (index == original)
        return false;
    }
    return filled[index];
  }

  bool find(K &&key) const {
    size_t index = std::hash<K>(key) % capacity;
    size_t i = 1;
    size_t original = index;
    while (filled[index] && keys[index] != key) {
      index += i * i % capacity;
      ++i;
      if (index == original)
        return false;
    }
    return filled[index];
  }

  const K *getKeys() const { return keys; }

  const V *getValues() const { return values; }

  void add(const K &key, const V &value) {
    if (find(key)) {
      throw std::runtime_error("Key already added");
    }
    if (size > capacity / 2) {
      expandMap();
    }
    size_t ind = getFreeIndex(key);
    keys[ind] = key;
    values[ind] = value;
    filled[ind] = true;
    ++size;
  }

  void add(K &&key, V &&value) {
    if (find(std::move(key))) {
      throw std::runtime_error("Key already added");
    }
    if (size > capacity / 2) {
      expandMap();
    }
    size_t ind = getFreeIndex(std::move(key));
    keys[ind] = std::move(key);
    values[ind] = std::move(value);
    filled[ind] = true;
    ++size;
  }

  void set(const K &key, const V &value) {
    size_t ind = findIndex(key);
    if (ind == -1) {
      add(key, value);
      return;
    }
    if (keys[ind] != key || !filled[ind]) {
      throw std::runtime_error("Wrong key");
    }
    values[ind] = value;
  }

  void set(K &&key, V &&value) {
    size_t ind = findIndex(std::move(key));
    if (ind == -1) {
      add(std::move(key), std::move(value));
      return;
    }
    if (keys[ind] != key || !filled[ind]) {
      throw std::runtime_error("Wrong key");
    }
    values[ind] = std::move(value);
  }

  void remove(const K &key) {
    size_t ind = findIndex(key);
    if (ind == -1)
      return;
    delete keys[ind];
    delete values[ind];
    filled[ind] = false;
    --size;
  }

  V *get(const K &key) const {
    size_t ind = findIndex(key);
    if (ind == -1)
      return nullptr;
    return values[ind];
  }

private:
  V *values;
  K *keys;
  bool *filled;
  size_t capacity = 2;
  size_t size = 0;

  size_t getFreeIndex(const K &key) const {
    size_t index = std::hash<K>(key) % capacity;
    size_t i = 1;
    size_t original = index;
    while (filled[index]) {
      index += i * i % capacity;
      ++i;
      if (index == original)
        throw std::runtime_error("Table is full");
    }
    return index;
  }
  size_t getFreeIndex(K &&key) const {
    size_t index = std::hash<K>(std::move(key)) % capacity;
    size_t i = 1;
    size_t original = index;
    while (filled[index]) {
      index += i * i % capacity;
      ++i;
      if (index == original)
        throw std::runtime_error("Table is full");
    }
    return index;
  }

  size_t findIndex(const K &key) const {
    size_t index = std::hash<K>(key) % capacity;
    size_t i = 1;
    size_t original = index;
    while (filled[index] && keys[index] != key) {
      index += i * i % capacity;
      ++i;
      if (index == original)
        return -1;
    }
    return filled[index] ? index : -1;
  }

  size_t findIndex(K &&key) const {
    size_t index = std::hash<K>(std::move(key)) % capacity;
    size_t i = 1;
    size_t original = index;
    while (filled[index] && keys[index] != key) {
      index += i * i % capacity;
      ++i;
      if (index == original)
        return -1;
    }
    return filled[index] ? index : -1;
  }

  void expandMap() {
    V *newValues = new V[capacity * 2];
    K *newKeys = new K[capacity * 2];
    bool *newFilled = new bool[capacity * 2];
    for (int i = 0; i < capacity; ++i) {
      if (filled[i]) {
        size_t newIndex = std::hash<K>(keys[i]) % (capacity * 2);
        size_t i = 1;
        while (newFilled[newIndex]) {
          newIndex += i * i % (capacity * 2);
          ++i;
        }
        newFilled[newIndex] = true;
        newValues[newIndex] = std::move(values[i]);
        newKeys[newIndex] = std::move(keys[i]);
      }
    }
    delete[] filled;
    delete[] values;
    delete[] keys;
    keys = newKeys;
    filled = newFilled;
    values = newValues;
    capacity *= 2;
  }
};

#endif // MAP_H