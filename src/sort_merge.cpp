#include <vector>
#include <queue>
#include <stdint-gcc.h>

namespace cormen {

//      MERGE SORT
//
//    xxxxxx|yyyyyy
//    /       \
//  xxx|xxx    yyy|yyy
//    /   \     /  \  / \
//  xx|x xx|x  yy|y  yy|y
//
// x|x  x  x|x  x  y|y  y  y|y  y

//    void merge(std::vector<int>* p_nums, int l, int m, int r) {
//        // merge two parts - indexed by [l ... m] and [m+1 ... r]
//
//        std::vector<int>& nums = *p_nums;
//        int ptr_1 = l;
//        int ptr_2 = m + 1;
//
//        std::queue<int> kicked_left;    // don't hard copy both subarrays - just keep kicked
//                                        // elements of left subarray
//                                        // (!) in the assumption that (r - m) <= (m - l)
//        while (nums[ptr_1] < nums[ptr_2])   // skip firts small elements of left subarray
//            ptr_1++;
//        while (ptr_1 <= m) {
//            kicked_left.push(nums[ptr_1]);
//            int tmp = kicked_left.front();
//            if (kicked_left.front() < nums[ptr_2]) {
//                nums[ptr_1] = tmp;
//                kicked_left.pop();
//            } else {
//                nums[ptr_1] = nums[ptr_2];
//                ptr_2++;
//            }
//            ptr_1++;
//        }
//        while (ptr_1 <= r && !kicked_left.empty()) {
//            int tmp = kicked_left.front();
//            if (kicked_left.front() < nums[ptr_2]) {
//                nums[ptr_1] = tmp;
//                kicked_left.pop();
//            } else {
//                nums[ptr_1] = nums[ptr_2];
//                ptr_2++;
//            }
//            ptr_1++;
//        }
//        // if we finish previous "while" by empty 'kicked_left'
//        // => last big elements already in right positions
//    }
    void merge(std::vector<int>* p_nums, int64_t l, int64_t m, int64_t r) {
        // merge two parts - indexed by [l ... m] and [m+1 ... r]

        // std::vector<int>& nums = *p_nums;
        int64_t ptr_1 = l;
        int64_t ptr_2 = m + 1;

        std::queue<int> kicked_left;    // don't hard copy both subarrays - just keep kicked
        // elements of left subarray
        // (!) in the assumption that (r - m) <= (m - l)
        while ((*p_nums)[ptr_1] < (*p_nums)[ptr_2])   // skip firts small elements of left subarray
            ptr_1++;
        while (ptr_1 <= m) {
            kicked_left.push((*p_nums)[ptr_1]);
            int tmp = kicked_left.front();
            // "ptr_2 > r" - because right sybarray can be empty already
            if (ptr_2 > r || kicked_left.front() < (*p_nums)[ptr_2]) {
                (*p_nums)[ptr_1] = tmp;
                kicked_left.pop();
            } else {
                (*p_nums)[ptr_1] = (*p_nums)[ptr_2];
                ptr_2++;
            }
            ptr_1++;
        }
        while (ptr_1 <= r && !kicked_left.empty()) {
            int tmp = kicked_left.front();
            // "ptr_2 > r" - because right sybarray can be empty already
            if (ptr_2 > r || kicked_left.front() < (*p_nums)[ptr_2]) {
                (*p_nums)[ptr_1] = tmp;
                kicked_left.pop();
            } else {
                (*p_nums)[ptr_1] = (*p_nums)[ptr_2];
                ptr_2++;
            }
            ptr_1++;
        }
        // if we finish previous "while" by empty 'kicked_left'
        // => last big elements already in right positions
    }
    void sort_merge_subtask(std::vector<int>* p_nums, int64_t l, int64_t r) {
        if (l == r)
            return;
        int64_t m = l + (r - l) / 2;
        sort_merge_subtask(p_nums, l, m);
        sort_merge_subtask(p_nums, m + 1, r);
        merge(p_nums, l, m, r);
    }

    void sort_merge(std::vector<int>* nums) {
        if (nums == nullptr)
            return;
        sort_merge_subtask(nums, 0, (*nums).size() - 1);
    }

}   // namespace cormen
