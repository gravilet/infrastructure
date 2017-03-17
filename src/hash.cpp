#include <hash.h>


namespace gravilet {

    size_t BaseHash::calculate_hash_function(std::string key, size_t collection_size) {
        size_t result;
        result = (key[0] % hash_function_divisor) * collection_size / hash_function_divisor;
        return result;
    }

    void OpenAddressingHash::insert(std::string key, std::string value) {
        if (current_size == collection_size)
            expand_collection(collection_size + expand_step);
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
    size_t OpenAddressingHash::find_hash(std::string key) const {
        size_t hash = calculate_hash_function(key, collection_size);
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

    const std::string* OpenAddressingHash::find(std::string key) const {
        size_t hash = find_hash(key);
        return (hash != -1 && std::get<0>(collection[hash])) ?
               &std::get<2>(collection[hash]) : nullptr;
    }

    void OpenAddressingHash::erase(std::string key) {
        size_t hash = find_hash(key);
        if (hash != -1 && std::get<0>(collection[hash])) {
            std::get<0>(collection[hash]) = false;
            current_size--;
        }
    }

    void OpenAddressingHash::expand_collection(size_t new_size) {
        if (new_size <= collection_size)
            return;
        std::vector<std::tuple<bool, std::string, std::string>> collection_tmp;
        collection_size = new_size;
        for (auto elem : collection) {
            size_t  hash = calculate_hash_function(std::get<1>(elem), collection_size);
            std::get<0>(collection_tmp[hash]) = true;
            std::get<1>(collection_tmp[hash]) = std::get<1>(elem);
            std::get<2>(collection_tmp[hash]) = std::get<2>(elem);
        }
        collection = collection_tmp;
    }

    size_t OpenAddressingHash::size() {
        return current_size;
    }

    int OpenAddressingHash::count(std::string key) const {
        size_t hash = find_hash(key);
        if (std::get<0>(collection[hash]))
            return 1;
        else
            return 0;
    }

    std::string OpenAddressingHash::operator[](std::string key) {
        int cnt = count(key);
        if (cnt == 0) {
            insert(key, "");    // let "" be default value
            return "";
        } else {
            return *find(key);
        }
    }
}   // namespace gravilet
