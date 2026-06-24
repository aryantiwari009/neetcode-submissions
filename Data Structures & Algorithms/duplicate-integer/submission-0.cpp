class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        int n = nums.size();
        int duplicate = -1;

        for(int i = 0; i < n; i++){
            int num = i;
            duplicate = nums[i];
            for(int j = (num + 1) ; j < n; j++){
                if(duplicate == nums[j]) return true;
                else continue;
            }
        } 
        return false;
    }
};