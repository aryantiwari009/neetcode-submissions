class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string output = strs[0];

        for(int i = 0; i < strs.size(); i++){
            string word = strs[i];
            for(int j = 0; j < output.size(); j++){
                if(output[j] != word[j]){
                    output.erase(j);
                    cout << output;
                }else continue;
            }
        }
        return output;
    }
};