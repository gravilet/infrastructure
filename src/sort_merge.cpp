#include <vector>
#include <queue>

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

    void merge(std::vector<int>* nums, unsigned long long l, unsigned long long m, unsigned long long r) {
        // merge two parts - indexed by [l ... m] and [m+1 ... r]
        std::vector<int>& ref_nums = *nums;
        unsigned long long ptr_1 = l;
        unsigned long long ptr_2 = m + 1;
        std::queue<int> kicked_left;    // don't hard copy both subarrays - just keep kicked elements of left subarray
                                        // (!) in the assumption that (r - m) <= (m - l)
        while (nums[ptr_1] < nums[ptr_2])   // skip firts small elements of left subarray
            ptr_1++;
        while (ptr_1 <= m) {
            kicked_left.push(ref_nums[ptr_1]);
            int tmp = kicked_left.front();
            if (kicked_left.front() < ref_nums[ptr_2]) {
                ref_nums[ptr_1] = tmp;
                kicked_left.pop();
            }
            else {
                ref_nums[ptr_1] = ref_nums[ptr_2];
                ptr_2++;
            }
            ptr_1++;
        }
        while (ptr_1 <= r && !kicked_left.empty()) {
            int tmp = kicked_left.front();
            if (kicked_left.front() < ref_nums[ptr_2]) {
                ref_nums[ptr_1] = tmp;
                kicked_left.pop();
            }
            else {
                ref_nums[ptr_1] = ref_nums[ptr_2];
                ptr_2++;
            }
            ptr_1++;
        }
        // if we finish previous "while" by empty 'kicked_left' => last big elements already in right positions
    }

    void sort_merge_subtask(std::vector<int>* nums, unsigned long long l, unsigned long long r) {
        if (l == r)
            return;
        std::vector<int> & ref_nums = *nums;
        unsigned long long m = l + (r - l) / 2;
        sort_merge_subtask(&ref_nums, l, m);
        sort_merge_subtask(&ref_nums, m + 1, r);
        merge(&ref_nums, l, m, r);
    }

    void sort_merge(std::vector<int>* nums) {
        if (nums == nullptr)
            return;
        std::vector<int>& ref_nums = *nums;
        sort_merge_subtask(&ref_nums, 0, ref_nums.size() - 1);
    }

}
