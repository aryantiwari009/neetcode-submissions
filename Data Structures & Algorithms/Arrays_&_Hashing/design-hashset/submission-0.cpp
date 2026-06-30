class MyHashSet {
private:
    // A member variable that persists across all function calls
    vector<bool> arr;

public:
    MyHashSet() {
        // Resize the vector to handle keys up to 1,000,000, initialized to false
        arr.resize(1000001, false);
    }
    
    void add(int key) {
        arr[key] = true;
    }
    
    void remove(int key) {
        arr[key] = false;
    }
    
    bool contains(int key) {
        return arr[key];
    }
};