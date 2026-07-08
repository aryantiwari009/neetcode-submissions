class Solution {
   public:
    int characterReplacement(string s, int k) {
        unordered_map<char, int> mp;
        int max_len = 0;
        int i = 0;
        int j = 0;

        // Use a single while loop to manage the window
        while (j < s.length()) {
            mp[s[j]]++;

            // Find the frequency of the most frequent character in the current window
            int max_freq = 0;
            for (auto const& [key, val] : mp) {
                max_freq = max(max_freq, val);
            }

            // Logic: (window size) - (max frequency) gives the number of replacements needed.
            // If this exceeds k, we must shrink the window from the left.
            while ((j - i + 1) - max_freq > k) {
                mp[s[i]]--;
                if (mp[s[i]] == 0) {
                    mp.erase(s[i]);
                }
                i++;
                // Re-calculate max_freq after shrinking
                max_freq = 0;
                for (auto const& [key, val] : mp) {
                    max_freq = max(max_freq, val);
                }
            }

            max_len = max(max_len, j - i + 1);
            j++;
        }
        return max_len;
    }
};
