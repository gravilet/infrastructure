#ifndef INCLUDE_SORT_MERGE_H_
#define INCLUDE_SORT_MERGE_H_

namespace cormen {

    void merge(std::vector<int>* p_nums, int64_t l, int64_t m, int64_t r);
    void sort_merge_subtask(std::vector<int>* p_nums, int64_t l, int64_t r);
    void sort_merge(std::vector<int>* nums);

}

#endif  // INCLUDE_SORT_MERGE_H_
