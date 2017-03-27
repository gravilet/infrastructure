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
                                          size_t collection_size);
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
    void expand_collection(size_t new_size);
    size_t find_hash(K key) const;
    V default_value_for_not_found = nullptr;

 public:
    explicit OpenAddressingHash(size_t size = BaseHash<K, V>::default_hash_size, size_t step = 1) :
                                                    BaseHash<K, V>(size),
                                                    collection(size),
                                                    step(step),
                                                    current_size(0),
                                                    expand_step(size){}
    void insert(K key, V value) override;
    void erase(K key) override;
    V* find(K key)  override;
    size_t size();
    int count(K key) const;
    // operators
    // [key] - create new if key not found (value is "")
    V& operator[](K key);
};

}  // namespace gravilet

#endif  // INCLUDE_HASH_H_
