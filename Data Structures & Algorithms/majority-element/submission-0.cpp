class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> freq;
        int count = 0;
        int num = 0;
        for(int num : nums){
            freq[num]++;
        }

        for(auto it : freq){
            if(it.second > count){
                num = it.first;
                count = it.second;
            } 
        }

        return num;
    }
};