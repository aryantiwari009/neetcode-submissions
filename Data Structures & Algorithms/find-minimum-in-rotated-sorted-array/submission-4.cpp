class Solution {
   public:
    int findMin(vector<int>& nums) {
        int start = 0, end = nums.size() - 1, n = nums.size(), mid = 0;

        while (start <= end) {
            mid = start + (end - start) / 2;
            int next = (mid + 1) % n;
            int previous = (mid + n - 1) % n;

            if (nums[start] < nums[end] && nums[start] < nums[mid] && nums[start] < nums[next]) {
                return nums[start];
                break;
            }
            
            if (nums[mid] <= nums[next] && nums[mid] <= nums[previous]) break;
            else if (nums[mid] >= nums[start]) start = mid + 1; 
            else if (nums[mid] <= nums[end]) end = mid - 1;
        }

        return nums[mid];
    }
};
