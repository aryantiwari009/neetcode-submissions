class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> charSet;
        int l = 0;
        int maxLength = 0;

        for (int r = 0; r < s.length(); r++) {
            // If we find a duplicate, shrink the window from the left
            while (charSet.find(s[r]) != charSet.end()) {
                charSet.erase(s[l]);
                l++;
            }
            // Add the current character to the set
            charSet.insert(s[r]);
            // Update the maximum length of the valid substring
            maxLength = max(maxLength, r - l + 1);
        }

        return maxLength;
    }
};