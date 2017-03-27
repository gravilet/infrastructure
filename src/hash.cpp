#include <hash.h>


namespace gravilet {

    template <class K, class V>
    size_t BaseHash<K, V>::calculate_hash_function(K key, size_t collection_size) {
        size_t result;
        result = (key[0] % hash_function_divisor) * collection_size / hash_function_divisor;
        return result;
    }

    template <class K, class V>
    void OpenAddressingHash<K, V>::insert(K key, V value) {
        if (current_size == BaseHash<K, V>::collection_size)
            expand_collection(OpenAddressingHash<K, V>::collection_size + expand_step);
        size_t hash = find_hash(key);
        if (hash != -1) {
            if (!std::get<0>(collection[hash]))
                current_size++;
            std::get<0>(collection[hash]) = true;
            std::get<1>(collection[hash]) = key;
            std::get<2>(collection[hash]) = value;
        }
    }

    // find hash - position in collection for the 'key'
    template <class K, class V>
    size_t OpenAddressingHash<K, V>::find_hash(K key) const {
        size_t hash = calculate_hash_function(key, BaseHash<K, V>::collection_size);
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

    template <class K, class V>
    V* OpenAddressingHash<K, V>::find(K key)  {
        size_t hash = find_hash(key);
        return (hash != -1 && std::get<0>(collection[hash])) ?
               &std::get<2>(collection[hash]) : nullptr;
    }

    template <class K, class V>
    void OpenAddressingHash<K, V>::erase(K key) {
        size_t hash = find_hash(key);
        if (hash != -1 && std::get<0>(collection[hash])) {
            std::get<0>(collection[hash]) = false;
            current_size--;
        }
    }

    template <class K, class V>
    void OpenAddressingHash<K, V>::expand_collection(size_t new_size) {
        if (new_size <= BaseHash<K, V>::collection_size)
            return;
        std::vector<std::tuple<bool, K, V>> collection_tmp;
        BaseHash<K, V>::collection_size = new_size;
        for (auto elem : collection) {
            size_t  hash = calculate_hash_function(std::get<1>(elem), BaseHash<K, V>::collection_size);
            std::get<0>(collection_tmp[hash]) = true;
            std::get<1>(collection_tmp[hash]) = std::get<1>(elem);
            std::get<2>(collection_tmp[hash]) = std::get<2>(elem);
        }
        collection = collection_tmp;
    }

    template <class K, class V>
    size_t OpenAddressingHash<K, V>::size() {
        return current_size;
    }

    template <class K, class V>
    int OpenAddressingHash<K, V>::count(K key) const {
        size_t hash = find_hash(key);
        if (std::get<0>(collection[hash]))
            return 1;
        else
            return 0;
    }

    template <class K, class V>
    V& OpenAddressingHash<K, V>::operator[](K key) {
        int cnt = count(key);
        if (cnt == 0) {
            insert(key, default_value_for_not_found);
        }
        V* p = find(key);
        return *p;
    }
}   // namespace gravilet
