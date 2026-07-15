class Solution {
public:

    int searchTarget(vector<int>& nums,int start,int end, int target){
        int low = start;
        int high = end;

        while(low < high){
            int mid = low + (high - low)/2;

            if(nums[mid] == target) return mid;
            else if(nums[mid] > target) high = mid-1;
            else low = mid + 1;
        }

        if(nums[low] != target) return -1;
        else return low;
    }

    int search(vector<int>& nums, int target) {
        int low = 0,high = nums.size() - 1;
        
        while(low < high){
            int mid = low + (high - low)/2;

            if(nums[high] < nums[mid]) low = mid + 1;
            else high = mid;
        }

       int result1 =  searchTarget(nums, 0, low - 1, target);
       int result2 = searchTarget(nums, low, nums.size() - 1, target);

       return max(result1, result2);
    }
};
