#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxAdjacentDistance(vector<int>& nums) {
        int n = nums.size();

        int answer = INT_MIN;

        for ( int i = 0; i < n; ++i ) {
            answer = max( answer, abs( nums[ i ] - nums[ ( i + 1 )%n ] ) );
        }
        return answer;
    }
};