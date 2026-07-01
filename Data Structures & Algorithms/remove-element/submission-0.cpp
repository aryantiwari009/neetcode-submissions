class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int k = n - 1, i = 0, j = n - 1;

        while(i < j){
            if(nums[i] != nums[j] && nums[i] == val){
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
                i++;
                k--;
            }
            else if(nums[j] != val && nums[i] != val) i++;
            else j--;

        }

        return k;
    }
};