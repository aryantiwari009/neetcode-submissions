class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int>mp;
        vector<int> output;

        for(int num : nums){
            mp[num]++;
        }

        for(auto it : mp){
            int large = 0;

            if(it.first > large){
                output.insert(output.begin(), it.first);
            } 
        }

        if(k == 1) return output;

        else{

        for(int i = 0;  i <= output.size() - k; i++){
            erase(output, output[i]);
        }

        return output;

        }

        
    }
};
