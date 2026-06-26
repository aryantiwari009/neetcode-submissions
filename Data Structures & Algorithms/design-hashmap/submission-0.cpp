class MyHashMap {
   private:
    vector<int> map;

   public:
    MyHashMap() { map.resize(1000001, -1); }

    void put(int key, int value) {
        for (int i = 0; i < map.size(); i++) {
            if (key == i) {
                map[i] = value;
                break;
            }
        }
    }

    int get(int key) {
        for (int i = 0; i < map.size(); i++) {
            if (key == i) {
                return map[i];
            } else continue;
        }
    }

    void remove(int key) {
        for(int i = 0; i < map.size(); i++){
            if(key == i){
                map[i] = -1;
            }
        }
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */