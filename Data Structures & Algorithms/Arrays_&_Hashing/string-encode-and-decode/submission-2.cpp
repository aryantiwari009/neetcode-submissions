class Solution {
   public:
    string encode(vector<string>& strs) {
        string encoded_string = "";

        for (int i = 0; i < strs.size(); i++) {
            int size = strs[i].size();
            encoded_string += to_string(size) + "#" + strs[i];
        }

        return encoded_string;
    }

    vector<string> decode(string s) {
        vector<string> decoded_string;
        int i = 0;

        while (i < s.size()) {
            int j = i;
            // Move j forward until it finds the '#' character
            while (s[j] != '#') {
                j++;
            }

            // Extract the length string (between i and j) and convert it to an integer
            int length = stoi(s.substr(i, j - i));

            // Move our main pointer i right past the '#' character
            i = j + 1;

            // Grab the actual string of that length and add it to our list
            decoded_string.push_back(s.substr(i, length));

            // Move pointer i past the string we just extracted to start the next loop
            i += length;
        }

        return decoded_string;
    }
};
