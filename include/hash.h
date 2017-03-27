#ifndef INCLUDE_HASH_H_
#define INCLUDE_HASH_H_

#include <string>
#include <vector>
#include <tuple>

namespace gravilet {


template <class K, class V> class BaseHash {
 protected:
    size_t static const default_hash_size = 100;
    // for 'string-key' implementation of hash-function based on division on 26
    size_t static const hash_function_divisor = 26;
    size_t collection_size;     // size of hash, not a number of elements
    static size_t calculate_hash_function(K key,
                                          size_t collection_size) {
        size_t result;
        result = (key[0] % hash_function_divisor) * collection_size / hash_function_divisor;
        return result;
    }
    explicit BaseHash(size_t size = default_hash_size) : collection_size(size) {}

 public:
    virtual void insert(K key, V value) = 0;
    virtual void erase(K key) = 0;
    virtual V* find(K key)  = 0;
};

template <class K, class V> class OpenAddressingHash : BaseHash<K, V> {
 private:
    std::vector<std::tuple<bool, K, V>> collection;
    size_t step;                           // step of Linear Probing
    size_t current_size;
    size_t expand_step;
    void expand_collection(size_t new_size) {
        if (new_size <= BaseHash<K, V>::collection_size)
            return;
        std::vector<std::tuple<bool, K, V>> collection_tmp;
        BaseHash<K, V>::collection_size = new_size;
        for (auto elem : collection) {
            size_t hash = BaseHash<K, V>::calculate_hash_function(std::get<1>(elem),
                                                                  BaseHash<K, V>::collection_size);
            std::get<0>(collection_tmp[hash]) = true;
            std::get<1>(collection_tmp[hash]) = std::get<1>(elem);
            std::get<2>(collection_tmp[hash]) = std::get<2>(elem);
        }
        collection = collection_tmp;
    }
    // find hash - position in collection for the 'key'
    size_t find_hash(K key) const {
        size_t hash = BaseHash<K, V>::calculate_hash_function(key, BaseHash<K, V>::collection_size);
        int tmp = 0;
        while (std::get<0>(collection[hash])
               && std::get<1>(collection[hash]) != key
               && tmp < BaseHash<K, V>::collection_size) {
            hash += step;
            if (hash > BaseHash<K, V>::collection_size - 1)
                hash %= BaseHash<K, V>::collection_size;
            tmp++;
        }
        if (tmp == BaseHash<K, V>::collection_size)     // key (hash) not found
            hash = -1;
        return hash;
    }
    V default_value_for_not_found = "";

 public:
    explicit OpenAddressingHash(size_t size = BaseHash<K, V>::default_hash_size, size_t step = 1) :
                                                    BaseHash<K, V>(size),
                                                    collection(size),
                                                    step(step),
                                                    current_size(0),
                                                    expand_step(size) {}
    void insert(K key, V value) override {
        if (current_size == BaseHash<K, V>::collection_size)
            expand_collection(BaseHash<K, V>::collection_size + expand_step);
        size_t hash = find_hash(key);
        if (hash != -1) {
            if (!std::get<0>(collection[hash]))
                current_size++;
            std::get<0>(collection[hash]) = true;
            std::get<1>(collection[hash]) = key;
            std::get<2>(collection[hash]) = value;
        }
    }
    void erase(K key) override {
        size_t hash = find_hash(key);
        if (hash != -1 && std::get<0>(collection[hash])) {
            std::get<0>(collection[hash]) = false;
            current_size--;
        }
    }
    V* find(K key)  override {
        size_t hash = find_hash(key);
        return (hash != -1 && std::get<0>(collection[hash])) ?
               &std::get<2>(collection[hash]) : nullptr;
    }
    size_t size() {
        return current_size;
    }
    int count(K key) const {
        size_t hash = find_hash(key);
        if (std::get<0>(collection[hash]))
            return 1;
        else
            return 0;
    }
    // operators
    // [key] - create new if key not found (value is "")
    V& operator[](K key) {
        int cnt = count(key);
        if (cnt == 0) {
            insert(key, default_value_for_not_found);
        }
        V* p = find(key);
        return *p;
    }
};


}  // namespace gravilet

#endif  // INCLUDE_HASH_H_
