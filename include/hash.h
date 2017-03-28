#ifndef INCLUDE_HASH_H_
#define INCLUDE_HASH_H_

#include <string>
#include <vector>
#include <tuple>

namespace gravilet {


template <class KEY, class VALUE> class BaseHash {
 protected:
    size_t static const default_hash_size = 100;
    // for 'string-key' implementation of hash-function based on division on 26
    size_t static const hash_function_divisor = 26;
    size_t collection_size;     // size of hash, not a number of elements
    static size_t calculate_hash_function(KEY key, size_t collection_size);
    explicit BaseHash(size_t size = default_hash_size) : collection_size(size) {}

 public:
    virtual void insert(KEY key, VALUE value) = 0;
    virtual void erase(KEY key) = 0;
    virtual VALUE* find(KEY key)  = 0;
};

template <class KEY, class VALUE>
size_t BaseHash<KEY, VALUE>::calculate_hash_function(KEY key, size_t collection_size) {
    size_t result;
    result = (key[0] % hash_function_divisor) * collection_size / hash_function_divisor;
    return result;
}

template <class KEY, class VALUE> class OpenAddressingHash : BaseHash<KEY, VALUE> {
 private:
    std::vector<std::tuple<bool, KEY, VALUE>> collection;
    size_t step;                           // step of Linear Probing
    size_t current_size;
    size_t expand_step;
    void expand_collection(size_t new_size);
    // find hash - position in the collection for the 'key'
    size_t find_hash(KEY key) const;

 public:
    explicit OpenAddressingHash(size_t size = BaseHash<KEY, VALUE>::default_hash_size, size_t step = 1) :
                                                    BaseHash<KEY, VALUE>(size),
                                                    collection(size),
                                                    step(step),
                                                    current_size(0),
                                                    expand_step(size) {}
    void insert(KEY key, VALUE value) override;
    void erase(KEY key) override;
    VALUE* find(KEY key) override;
    size_t size() {
        return current_size;
    }
    // number of used elemets
    int isPresent(KEY key) const;
    // operators
    VALUE& operator[](KEY key);
};

template <class KEY, class VALUE>
void OpenAddressingHash<KEY, VALUE>::expand_collection(size_t new_size) {
    if (new_size <= BaseHash<KEY, VALUE>::collection_size)
        return;
    std::vector<std::tuple<bool, KEY, VALUE>> collection_tmp;
    BaseHash<KEY, VALUE>::collection_size = new_size;
    for (auto elem : collection) {
        size_t hash = BaseHash<KEY, VALUE>::calculate_hash_function(std::get<1>(elem),
                                                                    BaseHash<KEY, VALUE>::collection_size);
        std::get<0>(collection_tmp[hash]) = true;
        std::get<1>(collection_tmp[hash]) = std::get<1>(elem);
        std::get<2>(collection_tmp[hash]) = std::get<2>(elem);
    }
    collection = move(collection_tmp);
}

// find hash - position in the collection for the 'key'
template <class KEY, class VALUE>
size_t OpenAddressingHash<KEY, VALUE>::find_hash(KEY key) const {
    size_t hash = BaseHash<KEY, VALUE>::calculate_hash_function(key, BaseHash<KEY, VALUE>::collection_size);
    int checked_count = 0;  // how many elements have been checked
    while (std::get<0>(collection[hash])
           && std::get<1>(collection[hash]) != key
           && checked_count < BaseHash<KEY, VALUE>::collection_size) {
        hash = (hash + step) % BaseHash<KEY, VALUE>::collection_size;
        checked_count++;
    }
    if (checked_count == BaseHash<KEY, VALUE>::collection_size)     // key (hash) not found
        hash = -1;
    return hash;
}

template <class KEY, class VALUE>
void OpenAddressingHash<KEY, VALUE>::insert(KEY key, VALUE value) {
    if (current_size == BaseHash<KEY, VALUE>::collection_size)
        expand_collection(BaseHash<KEY, VALUE>::collection_size + expand_step);
    size_t hash = find_hash(key);
    if (hash != -1) {
        if (!std::get<0>(collection[hash]))
            current_size++;
        std::get<0>(collection[hash]) = true;
        std::get<1>(collection[hash]) = key;
        std::get<2>(collection[hash]) = value;
    }
}

template <class KEY, class VALUE>
void OpenAddressingHash<KEY, VALUE>::erase(KEY key) {
    size_t hash = find_hash(key);
    if (hash != -1 && std::get<0>(collection[hash])) {
        std::get<0>(collection[hash]) = false;
        current_size--;
    }
}

template <class KEY, class VALUE>
VALUE* OpenAddressingHash<KEY, VALUE>::find(KEY key) {
    size_t hash = find_hash(key);
    return (hash != -1 && std::get<0>(collection[hash])) ?
           &std::get<2>(collection[hash]) : nullptr;
}

// number of used elemets
template <class KEY, class VALUE>
int OpenAddressingHash<KEY, VALUE>::isPresent(KEY key) const {
    size_t hash = find_hash(key);
    if (std::get<0>(collection[hash]))
        return 1;
    else
        return 0;
}

template <class KEY, class VALUE>
VALUE& OpenAddressingHash<KEY, VALUE>::operator[](KEY key) {        // [key] - create new if key not found
    int cnt = isPresent(key);
    if (cnt == 0) {
        insert(key, VALUE());
    }
    VALUE* p = find(key);
    return *p;
}

}  // namespace gravilet

#endif  // INCLUDE_HASH_H_
