class Solution {
public:
    int maxDiff(int num) {
        int running = num;
        vector<int> digits;

        while ( running > 0 ) {
            digits.push_back( running % 10 );
            running /= 10;
        }

        bool flag_max = true;
        bool flag_min = true;
        int n = digits.size();
        int pos_max = n - 1;
        int pos_min = n - 1;

        for ( int i = n - 1; i >= 0 && ( flag_max || flag_min ); --i ) {
            if ( digits[ i ] < 9 && flag_max ) {
                pos_max = i;
                flag_max = false;
            }
            if ( digits[ i ] > 1 && flag_min ) {
                pos_min = i;
                flag_min = false;
            }
        }

        int maxima = 0;
        int minima = 0;
        int base = 1;

        int minima_y;

        if ( pos_min == n - 1 ) {
            minima_y = 1;
        }
        else {
            minima_y = 0;
        }

        for ( int i = 0; i < n; ++i ) {
            if ( digits[ i ] == digits[ pos_max ] ) {
                maxima += base * 9;
            }
            else {
                maxima += base * digits[ i ];
            }
            if ( digits[ i ] == digits[ pos_min ] ) {
                minima += base * minima_y;
            }
            else {
                minima += base * digits[ i ];
            }

            base *= 10;
        }
        return maxima - minima;
    }
};