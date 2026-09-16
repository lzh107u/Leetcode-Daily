using namespace std;

class Solution {
public:

    struct Node;

    struct Edge {
        int start;
        int* end;
        int cnt = 0;
        Node* next_node = nullptr;

        Edge(int start_idx, int* end_ptr, int c, Node* next = nullptr) : start(start_idx), end(end_ptr), cnt(c), next_node(next) {}
    };

    struct Node {
        array<Edge*, 26> children{};
        Node* suffix_node = nullptr;

        Node(Node* link = nullptr) : suffix_node(link) {}
    };

    Node* root = nullptr;
    Node* cur_node = nullptr;
    Edge* cur_edge = nullptr;

    string longestDupSubstring(string s) {
        
        root = new Node(root);
        cur_node = root;

        string ans = "";
        int longest = 0;
        int i;
        int* pos = &i;
        int hidden_start = 0;
        int hidden_len = 0;
        
        bool dup_proc = false;

        for (i = 0; i < s.length(); ++i) {
            if (!dup_proc && !cur_node->children[s[i] - 'a']) { // 當前字母不存在
                Edge* new_edge = new Edge(i, pos, 1, nullptr); // 建立新 edge
                cur_node->children[s[i] - 'a'] = new_edge; // 為當前 node 註冊這個新字母開頭的 edge
                cur_edge = new_edge; // 幫最新的 edge 登記一下
            }
            else { // 當前字母已經存在
                
                if (s[i] != s[cur_edge->start + hidden_len]) { // 當前字母已經與 cur_edge 內的紀錄不同，該分割了
                    /* 待更新！ */
                    continue;
                }
                
                /* 以下開始，都是假定當前字母與紀錄中字母仍然一致 */

                if (!dup_proc) { // 還沒開始處理重複字母，也就是遇到這一輪第一個重複字母
                    dup_proc = true; // 打開 dup 處理模式
                    hidden_start = i; // 記住這次的開始位置
                    hidden_len = 1; // 開始登記這次重複的長度
                }

                if (hidden_start - cur_edge->start == hidden_len) { // 重複長度達標，仍然與當前字母一致
                    cur_edge->cnt++; // 計數器 + 1
                    if (longest < hidden_len) {
                        longest = hidden_len;
                        hidden_len = 0;
                    }
                }
            }
        }

        return ans;
    }

    
};