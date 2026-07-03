class Solution {
public:
    int trap(vector<int>& h) {
        if (h.empty()) return 0;
        
        int left = 0;
        int right = h.size() - 1;
        
        int leftMax = h[left];
        int rightMax = h[right];
        int res = 0;
        
        while (left < right) {
            if (leftMax < rightMax) {
                left++;
                leftMax = max(leftMax, h[left]);
                res += leftMax - h[left];
            } else {
                right--;
                rightMax = max(rightMax, h[right]);
                res += rightMax - h[right];
            }
        }
        
        return res;
    }
};