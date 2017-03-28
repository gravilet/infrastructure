#ifndef INCLUDE_HASH_H_
#define INCLUDE_HASH_H_

#include <string>
#include <vector>
#include <tuple>
#include <functional>

namespace gravilet {

template<class Key>
int hash_func(Key& x, int size) {
    return x % size;
}

template<>
int hash_func<std::string>(std::string& x, int size) {
    return x.size() % size;
}

template <class Key, class Value>
class BaseHash {
 protected:
    size_t static const default_hash_size = 100;
    // for 'string-key' implementation of hash-function based on division on 26
    size_t collection_size;     // size of hash, not a number of elements

    /**
     * int size - число значений, которое принимает эта хэш-функция => [0, size)
     */
//    using hash_function = int (*)(Key, int);
    std::function<int(Key&, int)> hash;
//    hash_function hash;
    explicit BaseHash(size_t size = default_hash_size,
                      std::function<int(Key&, int)> func = hash_func) :
            collection_size(size),
            hash(func) {}

 public:
    virtual void insert(Key key, Value value) = 0;
    virtual void erase(Key key) = 0;
    virtual Value* find(Key key)  = 0;
};


/*
template <class Key, class Value>
size_t BaseHash<Key, Value>::calculate_hash_function(Key key, size_t collection_size) {
    size_t result;
    result = (key[0] % hash_function_divisor) * collection_size / hash_function_divisor;
    return result;
}
*/
template <class Key, class Value>
class OpenAddressingHash : BaseHash<Key, Value> {
 private:
    std::vector<std::tuple<bool, Key, Value>> collection;
    size_t step;                           // step of Linear Probing
    size_t current_size;
    size_t expand_step;
    void expand_collection(size_t new_size);
    // find hash - position in the collection for the 'key'
    size_t find_hash(Key key) const;

 public:
    explicit OpenAddressingHash(size_t size = BaseHash<Key, Value>::default_hash_size,
                                size_t step = 1,
                                std::function<int(Key&, int)> func = hash_func) :
                                                    BaseHash<Key, Value>(size, func),
                                                    collection(size),
                                                    step(step),
                                                    current_size(0),
                                                    expand_step(size) {}
    void insert(Key key, Value value) override;
    void erase(Key key) override;
    Value* find(Key key) override;
    size_t size() {
        return current_size;
    }
    // number of used elemets
    int isPresent(Key key) const;
    // operators
    Value& operator[](Key key);
};

template <class Key, class Value>
void OpenAddressingHash<Key, Value>::expand_collection(size_t new_size) {
    if (new_size <= BaseHash<Key, Value>::collection_size)
        return;
    std::vector<std::tuple<bool, Key, Value>> collection_tmp;
    BaseHash<Key, Value>::collection_size = new_size;
    for (auto elem : collection) {
        size_t hash = BaseHash<Key, Value>::hash(std::get<1>(elem),
                                                 BaseHash<Key, Value>::collection_size);
        std::get<0>(collection_tmp[hash]) = true;
        std::get<1>(collection_tmp[hash]) = std::get<1>(elem);
        std::get<2>(collection_tmp[hash]) = std::get<2>(elem);
    }
    collection = move(collection_tmp);
}

// find hash - position in the collection for the 'key'
template <class Key, class Value>
size_t OpenAddressingHash<Key, Value>::find_hash(Key key) const {
    size_t hash = BaseHash<Key, Value>::hash(key, BaseHash<Key, Value>::collection_size);
    int checked_count = 0;  // how many elements have been checked
    while (std::get<0>(collection[hash])
           && std::get<1>(collection[hash]) != key
           && checked_count < BaseHash<Key, Value>::collection_size) {
        hash = (hash + step) % BaseHash<Key, Value>::collection_size;
        checked_count++;
    }
    if (checked_count == BaseHash<Key, Value>::collection_size)     // key (hash) not found
        hash = -1;
    return hash;
}

template <class Key, class Value>
void OpenAddressingHash<Key, Value>::insert(Key key, Value value) {
    if (current_size == BaseHash<Key, Value>::collection_size)
        expand_collection(BaseHash<Key, Value>::collection_size + expand_step);
    size_t hash = find_hash(key);
    if (hash != -1) {
        if (!std::get<0>(collection[hash]))
            current_size++;
        std::get<0>(collection[hash]) = true;
        std::get<1>(collection[hash]) = key;
        std::get<2>(collection[hash]) = value;
    }
}

template <class Key, class Value>
void OpenAddressingHash<Key, Value>::erase(Key key) {
    size_t hash = find_hash(key);
    if (hash != -1 && std::get<0>(collection[hash])) {
        std::get<0>(collection[hash]) = false;
        current_size--;
    }
}

template <class Key, class Value>
Value* OpenAddressingHash<Key, Value>::find(Key key) {
    size_t hash = find_hash(key);
    return (hash != -1 && std::get<0>(collection[hash])) ?
           &std::get<2>(collection[hash]) : nullptr;
}

// number of used elemets
template <class Key, class Value>
int OpenAddressingHash<Key, Value>::isPresent(Key key) const {
    size_t hash = find_hash(key);
    if (std::get<0>(collection[hash]))
        return 1;
    else
        return 0;
}

/**
 *
 * @param key - create new if key not found
 * @return
 */
template <class Key, class Value>
Value& OpenAddressingHash<Key, Value>::operator[](Key key) {
    int cnt = isPresent(key);
    if (cnt == 0) {
        insert(key, Value());
    }
    Value* p = find(key);
    return *p;
}

}  // namespace gravilet

#endif  // INCLUDE_HASH_H_
