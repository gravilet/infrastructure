#ifndef INCLUDE_SORT_MERGE_H_
#define INCLUDE_SORT_MERGE_H_

namespace cormen {

    void merge(std::vector<int>* nums, unsigned long long l, unsigned long long m, unsigned long long r);
    void sort_merge_subtask(std::vector<int>* nums, unsigned long long l, unsigned long long r);
    void sort_merge(std::vector<int>* nums);

}

#endif  // INCLUDE_SORT_MERGE_H_
