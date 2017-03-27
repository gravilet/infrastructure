#ifndef INCLUDE_HASH_H_
#define INCLUDE_HASH_H_

#include <string>
#include <vector>
#include <tuple>

namespace gravilet {


class BaseHash {
 protected:
    size_t static const default_hash_size = 100;
    // for 'string-key' implementation of hash-function based on division on 26
    size_t static const hash_function_divisor = 26;
    size_t collection_size;     // size of hash, not a number of elements
    static size_t calculate_hash_function(std::string key,
                                          size_t collection_size);
    explicit BaseHash(size_t size = default_hash_size) : collection_size(size) {}

 public:
    virtual void insert(std::string key, std::string value) = 0;
    virtual void erase(std::string key) = 0;
    virtual std::string* find(std::string key)  = 0;
};

class OpenAddressingHash : BaseHash {
 private:
    std::vector<std::tuple<bool, std::string, std::string>> collection;
    size_t step;                           // step of Linear Probing
    size_t current_size;
    size_t expand_step = collection_size;
    void expand_collection(size_t new_size);
    size_t find_hash(std::string key) const;
    std::string default_value_for_not_found = "";

 public:
    explicit OpenAddressingHash(size_t size = default_hash_size, size_t step = 1) :
                                                               BaseHash(size),
                                                               collection(size),
                                                               step(step),
                                                               current_size(0) {}
    void insert(std::string key, std::string value) override;
    void erase(std::string key) override;
    std::string* find(std::string key)  override;
    size_t size();
    int count(std::string key) const;
    // operators
    // [key] - create new if key not found (value is "")
    std::string& operator[](std::string key);
};

}  // namespace gravilet

#endif  // INCLUDE_HASH_H_
