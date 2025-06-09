#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findKthNumber(int n, int k) {

        // curr: the current number
        // everything starts from 1
        int curr = 1;

        // k: counter
        // already started from `curr = 1`, counter substract this one
        k--; 

        while (k > 0) {
            // counter(k) becomes less when every curr being processed

            // steps: the number of valid integers starting with integer `curr`(prefix)
            // no need to visit all of them, saving our execution time
            long steps = getSteps(curr, n);
            
            if (steps <= k) {
                curr++;       // next number
                k -= steps;   // bypass all valid numbers starting with prefix `curr`
            } else {
                curr *= 10;   // the answer (k-th) smallest is in the numbers starting with prefix `curr`
                k--;          // but not this one, counter has to substract another round
            }
        }
        return curr;
    }

    long getSteps(long curr, int n) {
        // the calculation of `the number of valid integers with prefix curr`

        long steps = 0; // counting starts from 0
        long first = curr; // element starts from `curr`
        long last = curr + 1; // Lexicographically, the largest integer is to directly add 1 to the `curr`

        // Why it happens?
        // Take an easy example:
        // -----------------------------
        // 123
        // 1230
        // 12300
        // 123001457
        // 123000457
        // 124 -> largest
        // -----------------------------
        // The prefix is more important than the actual value of an integer
        // The `124` is lexicographically larger than all of the integers start with `123`,
        // and that's why I use `curr++` as `bypassing entire curr section` in line 26

        while (first <= n) {
            // always make sure the range is valid ( <= n )
            
            // count the number of integers in current range [ first, min( ( long )n + 1, last ) ]
            // again, always make sure the ending of range doesn't exceed the boundary `n`
            steps += min((long)n + 1, last) - first;

            // moving to a new range,
            // simply add a zero at the tail, 
            // making the prefix longer while keeping lexicographically smallest principle
            first *= 10;
            last *= 10;
        }
        return steps;
    }
};