class Solution {
public:
    int maximumDifference(vector<int>& nums) {
        int minima = nums[ 0 ];
        int answer = -1;

        for ( int i = 1; i < nums.size(); ++i ) {
            if ( nums[ i ] == minima ) {
                continue;
            }
            answer = max( answer, nums[ i ] - minima );
            minima = min( minima, nums[ i ] );
        }
        return answer;
    }
};