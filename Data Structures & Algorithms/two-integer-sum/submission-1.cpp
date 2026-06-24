class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector <int> output(2);

        for(int i = 0; i < nums.size(); i++){
            int found = 0;
            for(int j = 0; j < nums.size(); j++){
                if((nums[i] + nums[j] == target) && i != j){
                    output[0] = i;
                    output[1] = j;
                    found = 1;
                    break;
                }else continue;
            }

            if(found == 1) break;
        }

        return output;
    }
};
