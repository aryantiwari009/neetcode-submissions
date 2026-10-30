class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mpp;

        for (int i = 0; i < nums.size(); i++) {

            int num = nums[i];
            int needed = target - nums[i];

            if (mpp.contains(needed)){
                return { mpp[needed], i };
            }
            mpp[num] = i; // element:index--> 2:1 , 7:2    
        }
        return {-1,-1};
    }
};