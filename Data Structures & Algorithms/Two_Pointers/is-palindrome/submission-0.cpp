class Solution {
public:
    bool isPalindrome(string s) {
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        int isPalindrone = false;

        int i = 0, j = s.size()-1;
        while(i <= j){
            if(s[i] == s[j]){
                isPalindrone = true;
                continue;
                j--;
                i++;
            }
            else{
                isPalindrone = false;
                break;
            }
        }

        return isPalindrone;
    }
};
