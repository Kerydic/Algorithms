# FindKth

## 题目描述

给定两个大小为 m 和 n 的有序数组 nums1 和 nums2，请找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。

请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。

你可以假设 nums1 和 nums2 不会同时为空。

示例 1:nums1 = [1, 3]   nums2 = [2] 则中位数是 2.0

示例 2:nums1 = [1, 2]   nums2 = [3, 4]  则中位数是 (2 + 3)/2 = 2.5

## 题目来源

Leet Code   [4. 寻找两个有序数组的中位数](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/)

## 解题思路

面试时，被问到log(n+m)求两个有序数组的第K大元素，其实寻找两个有序数组的中位数可以转为求第K小。
官方题解给的解法不太通用，而且边界条件太多了。
方法一：二分法找两个有序数组的第K小元素

@liweiwei1419这位同学总结的二分法模板非常好，基本是C++ STL中lower_bound函数和upper_bound函数实现的方式，强烈推荐！其实二分思想就是从数组的两边夹逼或排除，由循环不变式可知循环返回的那个位置就是满足查找条件(比如插入的位置)的位置。
a数组长度为n，b数组长度为m；
首先，找a和b两个有序数组中第K小，就是在a中找某个位置i，在b中找某个位置j，其满足条件为：
1、i+j=k
2、a[i-1]<=b[j]&&b[j-1]<=a[i]
这样第K小即为：max(a[i-1],b[j-1]);
其次，我们就可以在a数组中二分查找位置i，相应b中位置j=k-i，但是要注意b中j的位置不能越过b的边界即：0<=j<=m，
这样可以得到在a数组中二分查找的范围：0<=i<=n且k-m<=i<=k即max(0,k-m)<=i<=min(k,n);
我们可以在这个范围内用二分模板查找i的位置。
最后，二分找到i即代码中的le后，注意边界判断如果位置i和j前面都有元素，第k小=max(a[i-1],b[j-1]);如果i=0，
第k小=b[j-1];如果j=0;第k小=a[i-1];
两个有序数组的中位数即为：1、两个数组长度(m+n)为奇数，求第(m+n)/2+1小元素；2、两个数组长度(m+n)为偶数，求
第(m+n)/2小、第(m+n)/2+1小,两者平均值。

方法二：二分+递归（太麻烦，可以了解下）

```c++
class Solution {
public:
    //寻找第K大、小元素
    int findKthElm(vector<int>& a,int abeg,int aend,vector<int>& b,int bbeg,int bend,int k){
        if(abeg>aend){//如果a数组没有元素，直接返回b数组的第K大、小元素
            return b[bbeg+k-1];
        }
        if(bbeg>bend){//如果b数组没有元素，直接返回a数组的第K大、小元素
            return a[abeg+k-1];
        }
        int amid=(abeg+aend)/2;
        int bmid=(bbeg+bend)/2;
        if(a[amid]<b[bmid]){//这里写成a[amid]<b[bmid]是求第k小，改成a[amid]>b[bmid]就是求第K大,本题是求第k小
            if(amid-abeg+bmid-bbeg+2>k){//如果a[mid]<b[bmid]且k小于两个数组大小之和的一半，k一定不在b的右半部分，所以递归在
                //整个数组a和b的左半部分找第K小
                return findKthElm(a,abeg,aend,b,bbeg,bmid-1,k);
            }
            else{//如果a[mid]<b[bmid]且k大于等于两个数组大小之和的一半，k一定不在a的左半部分，所以递归在整个b数组和a数组的
                //右半部分寻找第(k-a左半部分长度)小
                return findKthElm(a,amid+1,aend,b,bbeg,bend,k-(amid-abeg+1));
            }
        }
        else{//和以上注解一样
            if(amid-abeg+bmid-bbeg+2>k){
                return findKthElm(a,abeg,amid-1,b,bbeg,bend,k);
            }
            else{
                return findKthElm(a,abeg,aend,b,bmid+1,bend,k-(bmid-bbeg+1));
            }
        }
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int sz=nums1.size()+nums2.size();
        if(sz%2==0){//偶数
            int a=findKthElm(nums1,0,nums1.size()-1,nums2,0,nums2.size()-1,sz>>1);
            int b=findKthElm(nums1,0,nums1.size()-1,nums2,0,nums2.size()-1,(sz>>1)+1);
            return (a+b)/2.0;
        }
        else{//奇数
            return findKthElm(nums1,0,nums1.size()-1,nums2,0,nums2.size()-1,(sz>>1)+1);
        }
    }
};
```

作者：nojoker
链接：<https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/jiang-qi-zhuan-wei-zhao-liang-ge-you-xu-shu-zu-de-/>
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

## 解题结果

![cpp](Image\cpp.png)

C++代码执行结果如上，平均运行时间不超过1.1us

![csharp](Image\csharp.png)

C#代码执行结果如上，平均运行时间不超过1ms，实际结果可能因C#使用了类函数而有偏差
