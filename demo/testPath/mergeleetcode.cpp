// MergeLeetCode.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "text.hpp"

//#include <mytest> 
#include <mustpass1> /*
#include <mustnotpass1>
#include <mustnotpass1> */ #include <mustpass2>
#include <mustpass3>

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

    
//    std::vector <int> first = {1,2,3,0,0,0};
//    std::vector <int> second = { 2,5,6 };
//    sol.merge(first, 3, second, 3);

    /*
    std::vector <int> first = { 2,0 };
    std::vector <int> second = { 1 };
    sol.merge(first, 1, second, 1);
    */

    std::vector <int> first = { 4,5,6,0,0,0 };
    std::vector <int> second = { 1,2,3 };
    sol.merge(first, 3, second, 3);


    std::cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.


/*for(int i =0; i < m+n; i++ )
            {
                
                ifm(nus1[p] < nums2[q] && p < n && q< m )
                {
                    result[i] = nums1[p];
                    p++;
                } else { 
                    result[i] = nums2[q];
                    q++;
                }
            }*/