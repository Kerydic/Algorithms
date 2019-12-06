#include <iostream>
#include <vector>
#include <cassert>
#include <time.h>
#include <windows.h>// QueryPerformanceFrequency,QueryPerformanceCounter头文件
using namespace std;

int findKthElm(vector<int>& nums1, vector<int>& nums2, int k) {
    assert(1 <= k && k <= nums1.size() + nums2.size());
    int le = max(0, int(k - nums2.size())), ri = min(k, int(nums1.size()));
    while (le < ri) {
        int m = le + (ri - le) / 2;
        if (nums2[k - m - 1] > nums1[m]) le = m + 1;
        else ri = m;
    }
    //循环结束时的位置le即为所求位置，第k小即为max(nums1[le-1]),nums2[k-le-1])，但是由于le可以为0、k,所以le-1或者k-le-1可能不存在,下面单独判断
    int nums1LeftMax = le == 0 ? INT_MIN : nums1[le - 1];
    int nums2LeftMax = le == k ? INT_MIN : nums2[k - le - 1];
    return max(nums1LeftMax, nums2LeftMax);
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size() + nums2.size();
    if (n & 1) {
        // 长度和为奇数
        return findKthElm(nums1, nums2, (n >> 1) + 1);
    }
    else {
        // 长度和为偶数
        return (double(findKthElm(nums1, nums2, n >> 1)) + double(findKthElm(nums1, nums2, (n >> 1) + 1))) / 2.0;
    }
}

int main()
{
    vector<int> array1 = { 1, 2 };
    vector<int> array2 = { 3, 4 };

    LARGE_INTEGER nFreq, t1, t2;
    double dt;

    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&t1);
    double result = findMedianSortedArrays(array1, array2);
    QueryPerformanceCounter(&t2);

    dt = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;

    cout << "Resule: " << result << endl;
    cout << "Total time: " << dt * 1000000 << "us" << endl;

    return 0;
}