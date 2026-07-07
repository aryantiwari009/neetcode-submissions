class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int k = s1.length();
        int n = s2.length();
        if (k > n) return false;

        unordered_map<char, int> m;
        for (char c : s1) m[c]++;

        int count = m.size();
        int i = 0, j = 0;

        while (j < n) {
            // Add s2[j] to the window
            if (m.find(s2[j]) != m.end()) {
                m[s2[j]]--;
                if (m[s2[j]] == 0) count--;
            }

            // Once window reaches size k
            if (j - i + 1 == k) {
                if (count == 0) return true;

                // Remove s2[i] from the window (slide)
                if (m.find(s2[i]) != m.end()) {
                    if (m[s2[i]] == 0) count++;
                    m[s2[i]]++;
                }
                i++;
            }
            j++;
        }
        return false;
    }
};