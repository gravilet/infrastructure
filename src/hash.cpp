#include <hash.h>


namespace gravilet {

    int64_t BaseHash::calculate_hash_function(std::string key, int64_t collection_size) {
        int64_t result;
        // for (char elem : key) {        }
        result = (key[0] % 26) * collection_size / 26;
        return result;
    }

    void OpenAddressingHash::insert(std::string key, std::string value) {
        if (current_size == collection_size)
            expand_collection(collection_size + expand_step);
        int64_t hash = find_hash(key);
        if (hash != -1) {
            if (!std::get<0>(collection[hash]))
                current_size++;
            std::get<0>(collection[hash]) = true;
            std::get<1>(collection[hash]) = key;
            std::get<2>(collection[hash]) = value;
        }
    }

    /**
     * // 20 -> 'a', 36 -> 'b' -> h1
     * // 20 -> 'a', 20 -> 'a' -> h1
     * @param key
     * @return
     */
    int64_t OpenAddressingHash::find_hash(std::string key) const {
        int64_t hash = calculate_hash_function(key, collection_size);
        int tmp = 0;
        while (std::get<0>(collection[hash])
               && std::get<1>(collection[hash]) != key
               && tmp < collection_size) {
            hash += step;
            if (hash > collection_size - 1)
                hash %= collection_size;
            tmp++;
        }
        if (tmp == collection_size)     // key (hash) not found
            hash = -1;
        return hash;
    }

    std::string OpenAddressingHash::find(std::string key) const {
        int64_t hash = find_hash(key);
        return (hash != -1) ? std::get<2>(collection[hash]) : nullptr;
    }

    void OpenAddressingHash::erase(std::string key) {
        int64_t hash = find_hash(key);
        if (hash != -1 && std::get<0>(collection[hash])) {
            std::get<0>(collection[hash]) = false;
            current_size--;
        }
    }

    void OpenAddressingHash::expand_collection(int64_t new_size) {
        if (new_size <= this->collection_size)
            return;
        std::vector<std::tuple<bool, std::string, std::string>> collection_tmp;
        collection_size = new_size;
        for (auto elem : collection) {
            int64_t  hash = calculate_hash_function(std::get<1>(elem), collection_size);
            std::get<0>(collection_tmp[hash]) = true;
            std::get<1>(collection_tmp[hash]) = std::get<1>(elem);
            std::get<2>(collection_tmp[hash]) = std::get<2>(elem);
        }
        collection = collection_tmp;
    }

    int64_t OpenAddressingHash::size() {
        return current_size;
    }
}   // namespace gravilet
