using System;

namespace Test
{
    class Program
    {
        static void Main(string[] args)
        {
            Solution s = new Solution();
            int[] array1 = { 1, 2 };
            int[] array2 = { 3, 4 };

            DateTime beforeDT = System.DateTime.Now;
            double result = s.FindMedianSortedArrays(array1, array2);
            DateTime afterDT = System.DateTime.Now;

            TimeSpan ts = afterDT.Subtract(beforeDT);
            Console.WriteLine("Resule: " + result);
            Console.WriteLine("Total time: " + ts.TotalMilliseconds + "ms");

            Console.ReadKey(true);
        }
    }

    public class Solution
    {
        public double FindMedianSortedArrays(int[] nums1, int[] nums2)
        {
            int n = nums1.Length + nums2.Length;
            if (n % 2 != 0)
                return FindKth(nums1, nums2, n / 2 + 1);
            else
                return (FindKth(nums1, nums2, n / 2) + FindKth(nums1, nums2, n / 2 + 1)) / 2.0;
        }

        public int FindKth(int[] nums1, int[] nums2, int k)
        {
            if (!(1 <= k && k <= nums1.Length + nums2.Length)) return -1;

            int left = Math.Max(0, k - nums2.Length);
            int right = Math.Min(k, nums1.Length);

            while (left < right)
            {
                int m = left + (right - left) / 2;
                if (nums2[k - m - 1] > nums1[m]) left = m + 1;
                else right = m;
            }
            // 循环结束时left即为所求位置，第K小即为max(nums1[left - 1], nums2[k - left - 1])，但是由于le可以为0、k,所以le-1或者k-le-1可能不存在，下面单独判断下
            int nums1LeftMax = left == 0 ? int.MinValue : nums1[left - 1];
            int nums2LeftMax = left == k ? int.MinValue : nums2[k - left - 1];
            return Math.Max(nums1LeftMax, nums2LeftMax);
        }
    }
}
