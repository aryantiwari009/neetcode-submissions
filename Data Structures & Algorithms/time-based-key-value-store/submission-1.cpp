class TimeMap {
   public:
    unordered_map<string, vector<pair<string, int>>> time_map;

    TimeMap() {}

    void set(string key, string value, int timestamp) {
        time_map[key].push_back({value, timestamp});
    }

    string get(string key, int timestamp) {
        string result = "";
        auto values = time_map[key];

        int left = 0;
        int right = values.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;

            if (values[mid].second > timestamp) {
                right = mid - 1;
            } else if (values[mid].second < timestamp) {
                result = values[mid].first;
                left = mid + 1;
            } else {
                result = values[mid].first;
                break;
            }
        }

        return result;
    }
};