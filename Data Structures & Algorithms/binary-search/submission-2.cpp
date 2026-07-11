class Solution {
public:
    int search(vector<int>& nums, int target) {
        int start = 0;
        int end = nums.size() - 1;
        int mid = -1;

        if(nums.size() == 0 && nums[0] == target) return 0;
        
        while(start <= end){
            mid = start + (end - start)/2;

            if(nums[mid] == target) return mid;

            if(nums[mid] > target) end = mid - 1;

            else start = mid + 1;
        }

        if(nums[mid] == target) return mid;
        else return -1;
    }
};
