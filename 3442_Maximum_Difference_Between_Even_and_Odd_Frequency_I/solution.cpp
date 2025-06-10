#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int maxDifference(string s) {
        vector<int> buffer( 26, 0 );

        for ( const char c : s ) {
            ++buffer[ c - 'a' ];
        }

        int maxima = 0;
        int minima = s.length();
        for ( const int i : buffer ) {
            if ( i % 2 == 1 && i > maxima ) {
                maxima = i;
            }
            else if ( i % 2 == 0 && i < minima && i > 0 ) {
                minima = i;
            }
        }

        return maxima - minima;
    }
};