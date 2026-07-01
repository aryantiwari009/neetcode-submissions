class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int k = n, i = 0, j = n - 1;

        while(i < j){
            if(nums[i] != nums[j] && nums[i] == val){
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
                i++;
                j--;
                k--;
            }
            else if(nums[j] != val && nums[i] != val) i++;
            else if (i == j) j--;
            else {
                k--;
                j--;
            }

        }

        return k;
    }
};