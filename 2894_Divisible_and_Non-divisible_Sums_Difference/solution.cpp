class Solution {
public:
    int differenceOfSums(int n, int m) {
        
        int cnt = 1;
        int num1 = 0;
        int num2 = 0;

        for ( int i = 1; i <= n; ++i ) {
            if ( cnt == m ) {
                num2 += i;
                cnt = 0;
            }
            else {
                num1 += i;
            }
            ++cnt;
        }
        return num1 - num2;
    }
};