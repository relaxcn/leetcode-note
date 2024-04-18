#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // 动态分析
    string longestPalindrome(string s) {
        int n = s.size();
        if (n < 2)
            return s;

        int maxLen = 1;
        int begin = 0;

        // dp[i][j] 表示 i .. j 的子串
        vector<vector<int> > dp(n, vector<int>(n));
        // 长度为 1 的子串都是回文串
        for (int i = 0; i < n; ++i)
            dp[i][i] = true;
        // 子串长度
        for (int L = 2; L < n; ++L) {
            // 左边界
            for (int left = 0; left < n; ++left) {
                // 右边界
                int right = left + L - 1;

                if (right >= n) {
                    break;
                }

                if (s[left] != s[right])
                    dp[left][right] = false;
                else {
                    if (L <= 3)
                        dp[left][right] = true;
                    else
                        // 状态转移
                        dp[left][right] = dp[left+1][right-1];
                }

                if (dp[left][right] && L > maxLen) {
                    maxLen = L;
                    begin = left;
                }
            }
        }
        return s.substr(begin, maxLen);
    }

    pair<int, int> expendAroundCenter(string&s, int left, int right) {
        while (left >= 0 && right <= s.size() && s[left] == s[right]) {
            --left;
            ++right;
        }
        return make_pair(left + 1, right - 1);
    }
    // 中心拓展法 time O(n^2) space: O(1)
    string longestPalindrome_1(string s) {
        int start= 0, end = 0;
        for (int i = 0; i < s.size(); ++i) {
            auto [left1, right1] = expendAroundCenter(s, i, i);
            auto [left2, right2] = expendAroundCenter(s, i, i + 1);
            if (right1 - left1 > end - start) {
                start = left1;
                end = right1;
            }
            if (right2 - left2 > end - start) {
                start = left2;
                end = right2;
            }
        }
        return s.substr(start, end - start + 1);
    }
};