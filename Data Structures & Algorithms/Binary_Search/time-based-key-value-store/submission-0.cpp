class TimeMap {
   public:
    unordered_map<string, vector<pair<int, string>>> mp;

    TimeMap() {}

    void set(string key, string value, int timestamp) { mp[key].push_back({timestamp, value}); }

    string get(string key, int timestamp) {
        // If the key doesn't exist, return empty string
        if (mp.find(key) == mp.end()) {
            return "";
        }

        const auto& values = mp[key];

        // Binary search to find the first element with a timestamp > target
        // We use a dummy pair with our target timestamp to compare against
        auto it = upper_bound(values.begin(), values.end(), make_pair(timestamp, string("")),
                              [](const pair<int, string>& a, const pair<int, string>& b) {
                                  return a.first < b.first;
                              });

        // If upper_bound points to the beginning, all timestamps are strictly greater than target
        if (it == values.begin()) {
            return "";
        }

        // Step back one element to get the largest timestamp <= target
        return prev(it)->second;
    }
};
