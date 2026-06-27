class Solution {
   public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        vector<vector<int>> buckets(nums.size() + 1);
        vector<int> output;

        for (int num : nums) {
            mp[num]++;
        }

        for (auto it : mp) {
            int element = it.first;
            int frequency = it.second;

            // Put the element into the bucket corresponding to its frequency
            buckets[frequency].push_back(element);
        }

        for (int i = buckets.size() - 1; i >= 0; i--) {
            for (int num : buckets[i]) {
                output.push_back(num);

                // Once we have collected 'k' elements, we are done!
                if (output.size() == k) {
                    return output;
                }
            }
        }

    }
};
