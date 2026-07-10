class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        
        for(int i = 0; i < s.size(); i++){
            st.push(s[i]);

            if(i == s.size() - 1) {
                if(st.size() > 2) return false;
            }

            if(s[i] == ']'){
                while(st.size() > 0 && st.top() != '[') st.pop();

                if(st.size() == 0) return false;
                else st.pop();
            }

            else if(s[i] == '}'){
                while(st.size() > 0 && st.top() != '{') st.pop();

                if(st.size() == 0) return false;
                else st.pop();
            }

            else if(s[i] == ')'){
                while(st.size() > 0 && st.top() != '(') st.pop();

                if(st.size() == 0) return false;
                else st.pop();
            }

        }

        if(st.size() != 0) return false; 

        else return true;
    }
};
