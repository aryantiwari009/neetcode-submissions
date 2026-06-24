class Solution {
   public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;

        for (int i = 0; i < s.size(); i++) {
            bool found = false;

            for (int j = 0; j < t.size(); j++) {
                if (s[i] == t[j]) {
                    found = true;
                    t[j] = -1;
                    break;
                }
            }

            if (found == true)
                continue;
            else
                return false;
        }

        return true;
    }
};
