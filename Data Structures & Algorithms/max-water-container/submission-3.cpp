class Solution {
public:
    int maxArea(vector<int>& heights) {
        int low = 0;
        int high = heights.size()-1;
        int result = 0;
        while(low <= high){
            int length = high - low;
            int breadth = min(heights[low], heights[high]);

            result = max(result, (breadth * length));

            if(heights[low] < heights[high]) low++;
            else high--;
        }

        return result;
    }
};
