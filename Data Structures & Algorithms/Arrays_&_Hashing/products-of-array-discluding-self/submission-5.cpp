class Solution {
public:
    vector<int> productExceptSelf(std::vector<int>& nums) {
        int length = nums.size();
        std::vector<int> output(length, 1);
        
        // Pass 1: Calculate prefix products
        int prefix = 1;
        for (int i = 0; i < length; ++i) {
            output[i] = prefix;
            prefix *= nums[i];
        }
        
        // Pass 2: Calculate postfix products and update output
        int postfix = 1;
        for (int i = length - 1; i >= 0; --i) {
            output[i] *= postfix;
            postfix *= nums[i];
        }
        
        return output;
    }
};
