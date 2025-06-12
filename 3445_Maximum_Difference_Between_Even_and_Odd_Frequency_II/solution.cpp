#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Solution 
{
public:
    int maxDifference(string s, int k) 
    {
        int n = s.size();
        int ans = INT_MIN;

        // Step 1: Try all (a, b) pairs
        for (int a = 0; a <= 4; ++a) 
        {
            for (int b = 0; b <= 4; ++b) 
            {
                if (a == b)
                {
                    continue;
                } 

                vector<int> s1(n + 1);
                vector<int> s2(n + 1);
                
                // Step 2: Prefix counts
                for (int i = 1; i <= n; ++i) 
                {
                    s1[i] = s1[i - 1] + (s[i - 1] - '0' == a);
                    s2[i] = s2[i - 1] + (s[i - 1] - '0' == b);
                }

                /*
                這個解法將問題描述為：

                        ( s1[i] - s2[i] ) + ( s2[j] - s1[j] )
                    =>  s1[i] - s[j] - s2[i] + s2[j]
                    =>  ( s1[i] - s1[j] ) - ( s2[i] - s2[j] )

                也就是字元 a 與字元 b 在區間 [ j, i ] 之間的出現次數差值。
                注意 s1 與 s2 分別代表了字元 a 與 b 在該位置之前累計出現的次數。
                */

                /*
                g 扮演的角色：搞定 s1[j] 與 s2[j]

                無論作為右側邊界的 i 推進到哪裡，左邊已經看好的部分理應不必再檢查，
                反正內容跟結果都不可能會變。
                */

                /*
                在 Step 4 中，右側邊界 i 與左側邊界 j 的行動是分開看的

                大方向來說，for 迴圈在做的就是不斷將右側邊界 i 繼續往右邊推，一路推到底(就是 n)，
                每推進一次，就檢查目前的累積量，但由於左側邊界 j 的位置會讓部分字元的次數減少，
                因為 s1, s2 是從頭開始計，但左側邊界 j 已經不在開頭了，很有可能部分字元已經被排除了幾個。

                這個顧慮在問題描述：

                    ( s1[i] - s1[j] ) - ( s2[i] - s2[j] )

                中，就是兩個括號中被減掉的部分。只是在經過推導後，這個算式被改寫為：

                    ( s1[i] - s2[i] ) + ( s2[j] - s1[j] )

                其中第二項就是 g 在儲存的資料。
                總結來說，每推進一次 i ，就根據目前 a, b 累計數量的奇偶性質，從 need 中找看看左側最大的紀錄。

                
                至於左側邊界在幹嘛？

                左側這裡的重點在維護 g ，也就是推導後第二項，與其硬塞一個意義給它，單純理解為讓第二項最大化就能答案最大化就好。
                因此，g 的目的是存最大值。

                while 的判定條件有三：
                1. 窗口長度合規，就是 [ j, i ] 這段長度大於等於 k
                2. 在 [ i, j ] 之內，存在有至少 1 個字元 a ，使 s1[i] > s1[j]
                3. 概念同 2. ，只是換成字元 b

                g 作為一個 2*2 的 vector<int> ，就只是根據[奇數, 偶數]兩兩相配共四種組合來記錄四種情境下的最大值。
                可以注意到： 
                        
                            g[pa][pb] = max(g[pa][pb], s2[j] - s1[j]);

                就是遇到大的就更新，而且 s2[j] - s1[j] 就只是上述算式推導的結果而已，無須過度在意。
                */

                /*
                關於 g 與 need 在 parity 上的判定

                首先，根據題意，a 需要在區間 [j,i] 中出現奇數次；b 則是偶數次
                兩者在計算區間內出現數量的方式為 s1[i] - s1[j] ，其中 a 要注意：

                    因為要奇數次，所以 s1[i] 與 s1[j] 必為一奇一偶，是誰不重要，總之 parity 要不一樣
                
                而 b 則不同，因為是要偶數次，所以 s2[i] 與 s2[j] 的 parity 必相同。

                回到程式碼，pa, pb 分別代表兩種字元在 i 處的 parity ，而在查表時，用 1-pa 表示不同 parity ，而 pb 就直接用，畢竟是一樣的，
                最終在 g 中取出 (s2[j] -s1[j]) 的最大值，用來對 answer 最大化
                
                */

                // Step 3: Matrix for best difference at each parity
                int g[2][2] = {{INT_MIN, INT_MIN}, {INT_MIN, INT_MIN}};
                int j = 0; // j: left bound

                // Step 4: Sliding window
                for (int i = k; i <= n; ++i) // i: right bound
                {
                    while (i - j >= k && s1[i] > s1[j] && s2[i] > s2[j]) 
                    {
                        int pa = s1[j] % 2;
                        int pb = s2[j] % 2;
                        g[pa][pb] = max(g[pa][pb], s2[j] - s1[j]);
                        ++j;
                    }

                    // Step 5: Check if valid
                    int pa = s1[i] % 2;
                    int pb = s2[i] % 2;
                    int need = g[1 - pa][pb];
                    
                    if (need != INT_MIN) 
                    {
                        ans = max(ans, (s1[i] - s2[i]) + need);
                    }
                }
            }
        }

        return ans == INT_MIN ? -1 : ans;
    }
};