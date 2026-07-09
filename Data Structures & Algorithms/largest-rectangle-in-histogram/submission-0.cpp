class Solution {
   public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> left;
        vector<int> right;

        vector<int> ans;
        vector<int> width;

        stack<pair<int, int>> s1;
        stack<pair<int, int>> s2;

        int maximum = 0;

        int tempLeft = -1;
        int tempRight = heights.size();

        for (int i = 0; i < heights.size(); i++) {
            if (s1.size() == 0)
                left.push_back(tempLeft);

            else if (s1.size() > 0 && s1.top().first < heights[i]) {
                left.push_back(s1.top().second);
            }

            else if (s1.size() > 0 && s1.top().first >= heights[i]) {
                while (s1.size() > 0 && s1.top().first >= heights[i]) s1.pop();

                if (s1.size() == 0)
                    left.push_back(tempLeft);
                else
                    left.push_back(s1.top().second);
            }

            s1.push({heights[i], i});
        }

        for(int i= 0; i < left.size(); i++){
            cout << left[i] << " ";
        }


        for (int i = heights.size()-1; i >= 0; i--) {
            if (s2.size() == 0)
                right.push_back(tempRight);

            else if (s2.size() > 0 && s2.top().first < heights[i]) {
                right.push_back(s2.top().second);
            }

            else if (s2.size() > 0 && s2.top().first >= heights[i]) {
                while (s2.size() > 0 && s2.top().first >= heights[i]) s2.pop();

                if (s2.size() == 0)
                    right.push_back(tempRight);
                else
                    right.push_back(s2.top().second);
            }

            s2.push({heights[i], i});
        }

        for(int i= 0; i < right.size(); i++){
            cout << right[i] << " ";
        }

        reverse(right.begin(), right.end());

        for(int i= 0; i < heights.size(); i++){
            maximum = max(((right[i] - left[i]) - 1) * heights[i], maximum);
        }

        return maximum;
    }
};
