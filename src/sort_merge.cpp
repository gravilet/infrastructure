#include <vector>

namespace cormen {

    void merge(std::vector<int>* nums, int x, int y, int z) {
        std::vector<int>& ref_nums = *nums;
        ref_nums[0] = 1;
    }

}
