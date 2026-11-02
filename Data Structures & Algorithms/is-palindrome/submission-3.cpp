class Solution {
   public:
    bool isPalindrome(string s) {

        string result = "";

        for (char c : s) {
            if (isalnum(c)) {
                result += tolower(c);  // Saves only lowercase letters
            }
        }

        s = result;  
        int low = 0;
        int high = s.size() - 1;

        while (low <= high) {
            if (s[low] != s[high]) return false;
            low++;
            high--;
            
        }

        return true;
    }
};
