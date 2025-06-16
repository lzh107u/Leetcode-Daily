class Solution {
public:
    int minMaxDifference(int num) {
        
        vector<int> digits;
        int running = num;

        while ( running > 0 ) {
            digits.push_back( running % 10 );
            running /= 10;
        }

        int n = digits.size();
        int pos_max = n - 1;
        int pos_min = n - 1;
        bool flag_x = true;
        bool flag_n = true;

        for ( int i = n - 1; i >= 0 && ( flag_x || flag_n ); --i ) {
            if ( digits[ i ] < 9 && flag_x ) {
                pos_max = i;
                flag_x = false;
                //cout << "set max to pos " << pos_max << endl;
            }
            if ( digits[ i ] > 0 && flag_n ) {
                pos_min = i;
                flag_n = false;
                //cout << "set min to pos " << pos_min << endl;
            }
        }

        int maxima = 0;
        int minima = 0;
        int base = 1;

        for ( int i = 0; i < n; ++i ) {
            if ( digits[ i ] == digits[ pos_max ] ) {
                maxima += 9 * base;
            }
            else {
                maxima += digits[ i ] * base;
            }

            if ( digits[ i ] != digits[ pos_min ] ) {
                minima += digits[ i ] * base;
            }
            base *= 10;
        }
        //cout << "maxima: " << maxima << endl;
        //cout << "minima: " << minima << endl;

        return maxima - minima;
    }
};