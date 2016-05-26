#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <cstdio>
#include <iterator>
#include <functional>
#include <ctime>
#include <chrono>
#include "timer.h"

using namespace std;

/**
 * 除非特别说明, 本脚本中所有区间格式均为[low, high)
 */

/**
 * 快速排序
 * 平均时间:O(nlogn)
 * 最坏时间:O(n^2)
 * 最好时间:O(nlogn)
 * 辅助存储:O(logn)
 * 是否稳定:否
 */
class QuickSort {
public:
    void sort(vector<int> &nums) {
        this->sort(nums, 0, nums.size());
    }

private:
    void sort(vector<int> &nums, const int low, const int high) {
        if (high - low <= 1) return ;
        int mid = this->partition(nums, low, high);
        sort(nums, low, mid);
        sort(nums, mid+1, high);
    }

    int partition(vector<int> &nums, const int low, const int high) {
        int i = low, j = high;
        const int pivot = nums[low];
        while (true) {
            // 下一步不能跳到一个不靠谱的位置
            while (nums[++i] < pivot) if (i == high - 1) break;
            while (pivot < nums[--j]) if (j == low) break;
            if (i >= j) break;
            swap(nums[i], nums[j]);
        }

        swap(nums[low], nums[j]);
        return j;
    }
};


/**
 * 选择排序
 * 平均时间:O(n^2)
 * 最坏时间:O(n^2)
 * 最好时间:O(n^2)
 * 辅助存储:O(1)
 * 是否稳定:是
 */
class SelectSort {
public:
    void sort(vector<int> &nums) {
        const int N = nums.size();
        for (int i = 0; i < N; ++ i) {
            int min_idx = i;
            for (int j = i + 1; j < N; ++ j) {
                if (nums[min_idx] > nums[j]) {
                    min_idx = j;
                }
            }

            swap(nums[min_idx], nums[i]);
        }
    }
};


/**
 * 插入排序
 * 平均时间:O(n^2)
 * 最坏时间:O(n^2)
 * 最好时间:O(n)
 * 辅助存储:O(1)
 * 是否稳定:是
 */
class InsertionSort {
public:
    void sort(vector<int> &nums) {
        const int N = nums.size();
        for (int i = 1; i < N; ++ i) {
            for (int j = i; j > 0 && nums[j] < nums[j-1]; -- j) {
                swap(nums[j-1], nums[j]);
            }
        }
    }
};


/**
 * 冒泡排序
 * 平均时间:O(n^2)
 * 最坏时间:O(n^2)
 * 最好时间:O(n^2) (注:如果判定一轮迭代中是否有过元素交换, 那么此处为O(n))
 * 辅助存储:O(1)
 * 是否稳定:是
 */
class BubbleSort
{
public:
    void sort(vector<int> &nums) {
        const int N = nums.size();
        for (int i = 0; i < N; ++ i) {
            for (int j = N-1; j > i; -- j) {
                if (nums[j-1] > nums[j]) {
                    swap(nums[j-1], nums[j]);
                }
            }
        }
    }
};


/**
 * 分治排序
 * 平均时间:O(nlogn)
 * 最坏时间:O(nlogn)
 * 最好时间:O(nlogn)
 * 辅助存储:O(n)
 * 是否稳定:是
 */
class MergeSort
{
public:
    void sort(vector<int> &nums) {
        _aux.resize(nums.size());
        sort(nums, 0, nums.size());
        _aux.clear();
    }

private:
    void sort(vector<int> &nums, int low, int high) {
        if (high - low <= 1)
            return;

        int mid = low + (high - low) / 2;
        this->sort(nums, low, mid);
        this->sort(nums, mid, high);
        merge(nums, low, mid, high);
    }

    void merge(vector<int> &nums, int low, int mid, int high) {
        copy(nums.begin()+low, nums.begin()+high, _aux.begin()+low);

        int i = low, j = mid, k = low;
        while (i < mid && j < high) {
            if (_aux[i] <= _aux[j]) nums[k++] = _aux[i++];
            else nums[k++] = _aux[j++];
        }

        while (i < mid) nums[k++] = _aux[i++];
        while (j < high) nums[k++] = _aux[j++];
    }

    vector<int> _aux;
};

/*
* 平均时间:O(nlogn)
* 最坏时间:O(nlogn)
* 最好时间:O(nlogn)
* 辅助存储:O(n)
* 是否稳定:是
*/
class MergeSortBottomUp
{
public:
    void sort(vector<int> &nums) {
        _aux.resize(nums.size());

        const int N = nums.size();
        for (int sz = 1; sz < N; sz *= 2) {
            for (int low = 0; low < N - sz; low += sz*2) {
                merge(nums, low, low+sz, min(low+sz*2, N));
            }
        }

        _aux.clear();
    }

private:
    void merge(vector<int> &nums, int low, int mid, int high) {
        copy(nums.begin()+low, nums.begin()+high, _aux.begin()+low);

        int i = low, j = mid, k = low;
        while (i < mid && j < high) {
            if (_aux[i] <= _aux[j]) nums[k++] = _aux[i++];
            else nums[k++] = _aux[j++];
        }

        while (i < mid) nums[k++] = _aux[i++];
        while (j < high) nums[k++] = _aux[j++];
    }

    vector<int> _aux;
};


/**
 * 堆排序
 * 平均时间:O(nlogn)
 * 最坏时间:O(nlogn)
 * 最好时间:O(nlogn)
 * 辅助存储:O(1)
 * 是否稳定:否
 */
class HeapSort {
public:
    void sort(vector<int> &nums) {
        const int N = nums.size();
        for (int i = N/2; i > 0; -- i) {
            sink(nums, i, N);
        }

        for (int i = N; i > 1; -- i) {
            swap(get(nums,i), get(nums, 1));
            sink(nums, 1, i-1);
        }
    }

private:
    void sink(vector<int> &nums, int low, int high) {
        // 闭区间
        while (2 * low <= high) {
            int j = 2 * low;
            if (j < high && get(nums, j) < get(nums, j+1)) ++ j;
            if (get(nums,low) >= get(nums, j)) break;
            swap(get(nums,j), get(nums,low));
            low = j;
        }
    }

    inline int& get(vector<int> &nums, int idx) {
        return nums[idx-1];
    }
};


/**
 * 基数排序 k为数字的位数, r为进制
 * 平均时间:O(kn)
 * 最坏时间:O(kn)
 * 最好时间:O(kn)
 * 辅助存储:O(n+r)
 * 是否稳定:是
 */
class RadixSort
{
public:
    void sort(vector<int> &nums) {
        const int N = nums.size();
        if (N == 0) return ;

        int max_ele = *max_element(nums.begin(), nums.end());
        int base = 1;
        vector<int> aux(nums.size());

        while (max_ele / base != 0) {
            int counter[10] = {0};
            for (int i = 0; i < N; ++ i) {
                ++ counter[(nums[i] / base) % 10];
            }
            partial_sum(counter, counter+10, counter);

            for (int i = N-1; i >= 0; -- i) {
                aux[--counter[(nums[i] / base) % 10]] = nums[i];
            }

            aux.swap(nums);
            if (INT_MAX / base >= 10) {
                base *= 10;
            } else {
                break;
            }
        }
    }
};


template <typename SorterType>
void test(const vector<int> &nums, SorterType sorter) {
    vector<int> sort_by_std = nums;
    vector<int> sort_by_func = nums;
    Timer timer;

    sort(sort_by_std.begin(), sort_by_std.end());
    auto std_time_cost = timer.tick();

    sorter.sort(sort_by_func);
    auto sorter_time_cost = timer.tick();

    if (sort_by_func != sort_by_std) {
        cout << "TEST FAILED!" << endl;
        exit(1);
    }
    cout << "TEST passed, cost " << sorter_time_cost
         << " ms,  std::sort cost " << std_time_cost
         << " ms" << endl;
}


int main()
{
#ifndef ONLINE_JUDGE
    freopen("data.txt","r", stdin);
#endif
    //auto sorter = QuickSort();
    // auto sorter = SelectSort();
    //auto sorter = InsertionSort();
    // auto sorter = MergeSort();
    // auto sorter = MergeSortBottomUp();
    // auto sorter = BubbleSort();
    // auto sorter = RadixSort();
    auto sorter = HeapSort();
    // TEST CASE 1
    vector<int> nums;
    test(nums, sorter);

    // TEST CASE 2
    nums = {1,2,3,4};
    test(nums, sorter);

    // TEST CASE 3
    nums = {4,3,2,1};
    test(nums, sorter);

    // TEST CASE 4
    nums = {1};
    test(nums, sorter);

    // TEST CASE 5
    nums = {2,2,1,1};
    test(nums, sorter);

    // TEST CASE 6
    for (int i = 0; i < 10000000; ++ i) {
        nums.push_back(rand());
    }
    test(nums, sorter);
    return 0;
}