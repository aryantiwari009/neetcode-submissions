// Time Complexity == O(N²) , Space Complexity = O(N)
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> output;
        
        for(int i = 0; i < nums.size(); i++){
            int mult = 1;
            for(int j = 0; j < nums.size(); j++){
                if(i != j){
                    mult *= nums[j];
                }
            }
            output.push_back(mult);
        }

        return output;
    }
};
