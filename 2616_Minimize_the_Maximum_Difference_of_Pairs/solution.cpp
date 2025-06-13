class Solution {
public:
    bool canFormPairs(vector<int>& nums, int p, int maxDiff) {
        int count = 0;
        int i = 1;
        while (i < nums.size()) {
            if (nums[i] - nums[i - 1] <= maxDiff) {
                ++count;
                i += 2; // skip both used elements
            } else {
                ++i;
            }
        }
        return count >= p;
    }

    int minimizeMax(vector<int>& nums, int p) {
        /*
        先由小到大重新排序。

        這題要的 pair difference 來自任意兩元素的差值，排序可以讓相鄰元素的差值變成幾乎是最小解，
        儘管打亂了所有元素的位置，但位置在這題中無關緊要，只要關心是否重複使用到同個位置，因此打亂無所謂
        */
        sort(nums.begin(), nums.end());

        int left = 0;
        /*
        right 被初始化為 nums 內最大值減去最小值。

        這一併讓 answer 被初始化為理論最大值，不可能有比 nums.back() - nums.front() 還大的 pair difference
        */
        int right = nums.back() - nums.front();
        int answer = right;
        

        /*
        透過二分搜找出第 p 小的 pair difference

        一切始於最大可行解 right 與最小可行解 left = 0，每次搜索範圍都砍半，也就是 mid，
        由 canFormPairs() 檢查在目前的 mid 下是否足夠湊出 p 組以上的 pairs ，若可行，就繼續砍；若不可行，表示範圍太小了
        */
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canFormPairs(nums, p, mid)) {
                answer = mid;
                right = mid - 1; // try smaller diff
            } else {
                left = mid + 1; // increase allowed diff
            }
        }
        return answer;
    }
};
