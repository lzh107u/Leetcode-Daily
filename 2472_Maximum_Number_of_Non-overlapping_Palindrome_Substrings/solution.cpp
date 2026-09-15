class Solution {
public:
    int maxPalindromes(string s, int k) {
        int answer = 0;
        
        vector<int> record(s.length(), -1);

        for (int i = 0; i < s.length() - 1; ++i) {
            nPalindromes(s, i, i, k, record);
            
            // Edge case: 
            // Don't call nPalindromes with 2 starting points if the k is `1`.
            if (k > 1) nPalindromes(s, i, i + 1, k, record);
        }
        // Check the last letter.
        nPalindromes(s, s.length() - 1, s.length() - 1, k, record);

        // Count the number of valid palidrome sub-strings.
        int pos = 0;
        while (pos < record.size()) {
            if (record[pos] > -1) {
                answer++;
                pos = record[pos] + 1;
            }
            else {
                pos++;
            }
        }
        return answer;
    }

    void nPalindromes(const string& s, int left, int right, int k, vector<int>& record) {
        /* Check the length of the palindrome sub-string. */
        
        int len = 0;

        // The starting point had been occupied.
        if (record[left] != -1) {
            return ;
        }

        // Check the length.
        while (left >= 0 && right < s.length()) {
            if (s[left] == s[right] && record[left] == -1) {
                len = right - left + 1;
                if (len >= k) {
                    break;
                }
                if (left == 0 || right == s.length() - 1) break;
                left--;
                right++;
            }
            else {
                left++;
                right--;
                break;
            }
        }
        
        // Not enough length.
        if (len < k) {
            return ;
        }

        // Marked as occupied.
        for (int i = left; i <= right; ++i) {
            record[i] = right;
        }
        return ;
    }
};