#pragma once

#include <vector>
using namespace std;

template<typename K, typename V>
class OpenHashMap{
private:
    struct MapNode{
        K key_;
        V value_;
        bool is_occupied_;
        MapNode():is_occupied_(false){}
        MapNode(const K& k, const V& v):key_(k), value_(v), is_occupied_(true) {}
        MapNode(K&& k, V&& v) : key_(std::move(k)), valu_(std::move(v)), is_occupied_(true) {}
    };

    vector<MapNode> map;
    size_t size_;
    size_t capacity_;

    size_t hash(const K& key) const {
        size_t ind = std::hash<K>{}(key)%capacity_;
        while (map[ind]) {
            ind = (ind+1) % capacity_;
        }
        return ind;
    }

    void expand() {
        capacity_*=2;
        vector<MapNode> tempMap(capacity_);
        for (const MapNode & m : map) {
            if (m.is_occupied_) {
                tempMap[hash(m.key_)] = m;
            }
        }
        map = move(tempMap);
    }

public:
    OpenHashMap():size_(0),capacity_(16){}

    void insert(const K& key, const V& value) {
        if (size_ == capacity_) {
            expand();
        }
        map[hash(key)] = move(MapNode(key, value));
    }

    bool find(const K& key) const {}

    V& get(const K & key) {}

    bool remove(K key) {}

    size_t size() const {}

    V& operator[](const K& key) const {}

    V& operator[](K&& key) const {}

    void operator[](V&& value) {}
    void operator[](const V & value) {}

};