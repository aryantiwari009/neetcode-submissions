class Solution {
   public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());

        int n = nums.size();

        for (int left = 0; left <= n - 2; left++) {
            if (left > 0 && nums[left] == nums[left - 1]) continue;

            int mid = left + 1;
            int right = n - 1;

            while (mid < right) {
                if (nums[left] + nums[mid] + nums[right] == 0) {
                    result.push_back({nums[left], nums[right], nums[mid]});

                    while (mid < right && nums[mid] == nums[mid + 1]) mid++;
                    // Skip duplicate values for the third element
                    while (mid < right && nums[right] == nums[right - 1]) right--;

                    mid++;
                    right--;
                }

                else if (nums[mid] + nums[right] + nums[left] > 0)
                    right--;

                else
                    mid++;
            }
        }
        return result;
    }
};
