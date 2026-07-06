#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        // We track seen numbers for rows, columns, and 3x3 squares
        unordered_set<string> seen;

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char number = board[i][j];
                
                if (number != '.') {
                    // Create unique strings for row, col, and block
                    string rowKey = to_string(number) + " in row " + to_string(i);
                    string colKey = to_string(number) + " in col " + to_string(j);
                    string boxKey = to_string(number) + " in box " + to_string(i / 3) + "-" + to_string(j / 3);

                    // If any of these are already in the set, the board is invalid
                    if (seen.count(rowKey) || seen.count(colKey) || seen.count(boxKey)) {
                        return false;
                    }

                    // Mark as seen
                    seen.insert(rowKey);
                    seen.insert(colKey);
                    seen.insert(boxKey);
                }
            }
        }
        return true;
    }
};