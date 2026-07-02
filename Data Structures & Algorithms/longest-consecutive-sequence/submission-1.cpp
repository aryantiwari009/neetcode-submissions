class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0; // Edge case: empty input

        sort(nums.begin(), nums.end());

        int max_streak = 1;
        int current_streak = 1;

        for (size_t i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[i - 1]) { // Skip duplicates
                if (nums[i] == nums[i - 1] + 1) {
                    current_streak++;
                } else {
                    max_streak = max(max_streak, current_streak);
                    current_streak = 1; // Reset streak
                }
            }
        }

        return max(max_streak, current_streak);
    }
};