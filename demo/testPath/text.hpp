// MergeLeetCode.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
#include <iostream>
#include <vector>
#include "text.hpp"

//#include <mytest> 
#include <mustpass1> 
#include <mustnotpass1>
#include <mustnotpass1> */ 

#include <t2.hpp>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (nums1.size() > m)
            nums1.erase(nums1.begin() + m, nums1.end());
        if (nums2.size() > n)
            nums2.erase(nums2.begin() + n, nums2.end());
        vector <int> result;
        result.resize(m + n);
        int p = 0;
        int q = 0;
        if (n != 0 && m != 0) {
            for (int i = 0; i < m + n; i++)
            {

                if ((p < m && q < n && nums1[p] < nums2[q]) )
                {
                    result[i] = nums1[p];
                    p++;
                }
                else if (q < n) {
                    result[i] = nums2[q];
                    q++;
                }
                else
                {
                    if (p < m)
                        result[i] = nums1[p];
                        p++;
                    if( q < n )
                        result[i] = nums2[q];
                        q++;
                }

            }
            nums1 = result;
        }
        else if (m == 0 && n != 0)
            nums1 = nums2;
    }
};

int main()
{
    Solution sol;
}