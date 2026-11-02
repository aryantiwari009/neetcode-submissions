class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        sort(numbers.begin(), numbers.end());
        int low = 0;
        int high = numbers.size()-1;

        for(int i = 0; i < numbers.size(); i++){
            int sum = numbers[low] + numbers[high];

            if(sum > target) high--;
            else if(sum < target) low++;
            else return {low + 1, high + 1};
        }

        return {};
    }
};
