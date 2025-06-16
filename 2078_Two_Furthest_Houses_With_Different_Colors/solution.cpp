class Solution {
public:
    int maxDistance(vector<int>& colors) {
        int n = colors.size();
        if ( n == 2 ) {
            return 1;
        }

        int first = colors[ 0 ];
        int second = -1;
        int pos = 1;
        int answer = 1;

        while ( pos < n ) {
            if ( colors[ pos ] != first ) {
                second = colors[ pos ];
                answer = max( answer, pos );
                break;
            }
            ++pos;
        }

        for ( int i = pos + 1; i < n; ++i ) {
            if ( colors[ i ] != first ) {
                answer = max( answer, i );
            }
            else {
                if ( colors[ i ] != second ) {
                    answer = max( answer, i - pos );
                }
            }
        }
        return answer;
    }
};