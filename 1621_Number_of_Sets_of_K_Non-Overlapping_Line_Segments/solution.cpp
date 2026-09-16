class Solution {
public:
    const static long long MOD = 1e9 + 7;

    int numberOfSets(int n, int k) {
        int n_bucket = k + (k + 1);
        int n_ball = n - k - 1;
        return combinationMod(n_bucket + n_ball - 1, n_ball);
    }

    int getFactorialMod(int n) {
        long long result = 1;

        for (int i = 0; i <= n; ++i) {
            result = (result * i) % MOD;
        }
        return (int)result;
    }

    long long fastPower(long long base, long long exp) {
        long long result = 1;

        base %= MOD;

        while (exp > 0) {
            if (exp % 2 == 1) result = (result * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }

        return result;
    }

    long long modInverse(long long n) {
        return fastPower(n, MOD - 2);
    }


    int combinationMod(int n, int k) {
        if (k < 0 || k > n) return 0;
        if (k == 0 || k == n) return 1;

        vector<long long> fact(n + 1, 1);
        for (int i = 2; i <=n; ++i) {
            fact[i] = (fact[i - 1] * i) % MOD;
            // fact[i] = (fact[i - 1] * i);
        }

        long long numerator = fact[n];
        long long denominator = (fact[k] * fact[n - k]) % MOD;
        // cout << "num: " << numerator << ", dem: " << denominator << endl; 
        long long ans = (numerator * modInverse(denominator)) % MOD;
        // long long ans = (numerator / denominator) % MOD;

        return (int)ans; 
    }
};