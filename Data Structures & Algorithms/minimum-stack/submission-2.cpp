class MinStack {
public:
    stack<int>s;
    stack<int>minS;

    MinStack() {}
    
    void push(int val) {
        s.push(val);
        if(minS.size() == 0) minS.push(val);
        else if(val <= minS.top()) minS.push(val);
    }
    
    void pop() {
        if(minS.top() == s.top()) minS.pop();
        s.pop();
    }
    
    int top() {
        int top = s.top();
        return top;
    }
    
    int getMin() {
        return minS.top(); 
    }
};
