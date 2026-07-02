class Solution {
public:
    int maxArea(vector<int>& h) {
        int maxArea = 0;
        int currentMaxArea = 0;

        int left = 0;
        int right = h.size() - 1;

        while(left < right){
            currentMaxArea = min(h[left], h[right]) * (right - left);

            if(h[left] <= h[right]) left++;
            else right--;

            maxArea = max(maxArea, currentMaxArea);
        }

        return maxArea;
    }
};
