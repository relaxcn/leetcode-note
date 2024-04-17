/*
 * @lc app=leetcode.cn id=4 lang=cpp
 *
 * [4] 寻找两个正序数组的中位数
 */
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// @lc code=start
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        int totalLength = n1 + n2;
        // 奇数
        if (totalLength % 2) {
            // 第 k 小的数就是中位数
            int k = (totalLength + 1) / 2;
            return getMedia(nums1, 0, n1-1, nums2, 0, n2-1, k);
        }
        // 偶数
        else {
            // 第 k 小的数字和第 k + 1 小的数字的和的一半就是中位数
            int k = totalLength / 2;
            return (getMedia(nums1, 0, n1-1, nums2, 0, n2-1, k) + getMedia(nums1, 0, n1-1, nums2, 0, n2-1, k+1)) / 2;
        }

    }

    // 在有序数组 nums1 和 nums2 中找到第 k 小的数字的值
    static double getMedia(vector<int>& nums1, int num1StartIndex, int num1EndIndex, 
                            vector<int>& nums2, int num2StartIndex, int num2EndIndex, int k)
    {
        int nums1_length = num1EndIndex - num1StartIndex + 1;
        int nums2_length = num2EndIndex - num2StartIndex + 1;

        if (nums1_length > nums2_length) {
            return getMedia(nums2, num2StartIndex, num2EndIndex, nums1, num1StartIndex, num1EndIndex, k);
        }

        if (nums1_length == 0) {
            return nums2[num2StartIndex + k - 1];
        }

        //  找第 1 小的数，就是当前的指向的两个数组中最小的那个数
        if (k == 1) {
            return min(nums1[num1StartIndex], nums2[num2StartIndex]);
        }

        // 如果 k 大于 1，找第 k 小的数字
        int curNum1Index = num1StartIndex + min(k/2, nums1_length) - 1;
        int curNum2Index = num2StartIndex + min(k/2, nums2_length) - 1;
        if (nums1[curNum1Index] >= nums2[curNum2Index]) {
            return getMedia(nums1, num1StartIndex, num1EndIndex, nums2, curNum2Index + 1, num2EndIndex, k - min(k/2, nums2_length));
        }
        else {
            return getMedia(nums1, curNum1Index + 1, num1EndIndex, nums2, num2StartIndex, num2EndIndex, k - min(k/2, nums1_length));
        }


    }
};
// @lc code=end

int main()
{
    Solution s;
    vector<int> v1 = {1, 3};
    vector<int> v2 = {2};
    cout << s.findMedianSortedArrays(v1, v2) << endl;
    return 0;
}
