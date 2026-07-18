//MT APPROACH - BRUTE FORCE
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

        vector<int> arr;

        int i1 = 0;
        int i2 = 0;

        // Merge both sorted arrays
        while (i1 < nums1.size() && i2 < nums2.size()) {

            if (nums1[i1] <= nums2[i2]) {
                arr.push_back(nums1[i1]);
                i1++;
            } else {
                arr.push_back(nums2[i2]);
                i2++;
            }
        }

        // Add remaining elements of nums1
        while (i1 < nums1.size()) {
            arr.push_back(nums1[i1]);
            i1++;
        }

        // Add remaining elements of nums2
        while (i2 < nums2.size()) {
            arr.push_back(nums2[i2]);
            i2++;
        }

        int n = arr.size();

        if (n % 2 == 0) {
            return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
        }

        return arr[n / 2];
    }
};