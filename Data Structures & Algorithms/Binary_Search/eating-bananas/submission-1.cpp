class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1;
        int right = *max_element(piles.begin(), piles.end());

        while(left < right){
            int mid = left + (right - left) / 2;

            int canEat = 0;

            for(int i = 0; i < piles.size(); i++){
                canEat += piles[i]/mid;

                if(piles[i]%mid != 0) canEat++;
            }

            if(canEat <= h) right = mid;
            else left = mid + 1;
        }

        return left;
    }
};
