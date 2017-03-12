#ifndef INCLUDE_HASH_H_
#define INCLUDE_HASH_H_

#include <string>
#include <vector>
#include <tuple>

namespace gravilet {

class BaseHash {
 protected:
    int64_t collection_size;
    static int64_t calculate_hash_function(std::string key,
                                            int64_t collection_size);
    explicit BaseHash(int64_t size = 100) : collection_size(size) {}
 public:
    virtual void insert(std::string key, std::string value) = 0;
    virtual void erase(std::string key) = 0;
    virtual std::string find(std::string key) const = 0;
};

class OpenAddressingHash : BaseHash {
 private:
    // bool=true => not empty, not deleted
    std::vector<std::tuple<bool, std::string, std::string>> collection;
    int64_t step;                           // step of Linear Probing
    // log26(collection_size) - number of significant letters in key
    // int64_t hash_support;
    int64_t current_size;
    int64_t expand_step = collection_size;  // ha-ha-ha!!!
 public:
    OpenAddressingHash() : BaseHash(100), collection(100), step(1), current_size(0) {}
    OpenAddressingHash(int64_t size, int64_t step) : BaseHash(100), collection(100),
                                                     step(step), current_size(0) {}
    void expand_collection(int64_t new_size);
    // int64_t static calculate_hash_function(std::string key);
    void insert(std::string key, std::string value);
    void erase(std::string key);
    std::string find(std::string key) const;
    int64_t find_hash(std::string key) const;
    int64_t size();
};
//
//    struct ListNode {
//        std::string key;
//        std::string value;
//        ListNode *next;
//        ListNode(std::string k, std::string v) : key(k), value(v), next(NULL) {}
//    };
//
//    class ChainingHash : BaseHash {
//     private:
//        std::vector<int64_t, ListNode*> collection;
//     public:
//        ChainingHash() : collection_size(100) {}
//        void expand_collection(int64_t new_size);
//
//        // int64_t calculate_hash_function(std::string key);
//        void insert(std::string key, std::string value);
//        void erase(std::string key);
//        std::string find(std::string key) const;
//        int64_t size();
//    };

}  // namespace gravilet

#endif  // INCLUDE_HASH_H_
