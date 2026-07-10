class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temp) {
        stack<pair<int , int>> s;
        vector<int> result;

        for(int i = temp.size() - 1; i >= 0; i--){

            if(s.size() == 0) result.push_back(0);

            else if(s.size() > 0 && s.top().first > temp[i]){
                result.push_back((s.top().second) - i);
            }

            else if(s.size() > 0 && s.top().first <= temp[i]){
                while(s.size() > 0 && s.top().first <= temp[i]) s.pop();

                if(s.size() == 0) result.push_back(0);
                else result.push_back((s.top().second) - i);
            }

            s.push({temp[i], i});
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
