题目链接: [189.Rotate Array][1]
难度: Easy

描述：给一个数组以及一个整数k，请将后k个元素挪到数组最前面。

要求：空间复杂度为O(1)。

# 手工移动法(28ms)
时间复杂度：O(N)
空间复杂度：O(1)

假设有6个元素，k=2，本方法执行多轮移动，
第一次从元素0开始，将arr[0]-arr[2]-arr[4]移动为arr[4]-arr[0]-arr[2]
第二次从元素1开始，将arr[1]-arr[3]-arr[5]移动为arr[5]-arr[1]-arr[3]
至此移动完毕。
arr[0]-arr[2]-arr[4]形成了一个环。

```cpp
class Solution 
{
public:
    void rotate(vector<int>& nums, int k) {
        const int n = nums.size();
        if ((n == 0) || (k <= 0)) {
            return;
        }

        int cntRotated = 0;	// 已经“归位”的元素个数
        int start = 0;	// 环的开始
        int curr = 0;	// 当前位置，一旦回到start即已经循环一周
        int numToBeRotated = nums[0];	// 环开始的元素
        
        // Keep rotating the elements until we have rotated n 
        // different elements.
        while (cntRotated < n) {
            do {
                swap(nums[(curr + k)%n], numToBeRotated);
                curr = (curr + k)%n;
                cntRotated++;
            } while (curr != start);
            // Stop rotating the elements when we finish one cycle, 
            // i.e., we return to start.

            // Move to next element to start a new cycle.
            start++;
            curr = start;
            numToBeRotated = nums[curr];
        }
    }
};
```

# 逆序法(24ms)
时间复杂度：O(N)
空间复杂度：O(1)

经典方法，先将前N-K个元素逆序，再将后K个元素逆序，最后总的逆序一次

```cpp
class Solution 
{
public:
    void rotate(vector<int>& nums, int k) {
        if (nums.size() == 0) return ;
        k = nums.size() - k % nums.size();
        
        reverse(nums.begin(), nums.begin()+k);
        reverse(nums.begin()+k, nums.end());
        reverse(nums.begin(), nums.end());
    }
};
```

# 逐步rotate法(24ms)
时间复杂度：O(N)
空间复杂度：O(1)

该方法先将最后面k个元素跟最前面k个元素互换，然后问题变成后N-K个元素中将k个元素挪到前面。写成递归是最容易理解了，下面写成了迭代的样子。

当K<=N/2时是容易理解的。但当K>N/2时有些微妙。此时的效果是前N-K个元素会向后滚动，效果如下：
```
arr={1,2,3,4,5,6,7}, k=4， 则实际是前3个元素在向后滚动，前4个元素最终被挪到前面：
iter=1: {4,[2,3,1],5,6,7}
iter=2: {4,5,[3,1,2],6,7}
iter=3: {4,5,6,[1,2,3],7}
iter=4: {4,5,6,7,[2,3,1]}
```

而前N-K个元素到滚到最后N-K个位置的时候它们的顺序是不确定的，比如：
```
arr = {1,2,3,4,5,6,7,8}，        k=6，得到{3 4 5 6 7 8; 1 2}，顺序正确
arr = {1,2,3,4,5,6,7,8,9}，      k=6，得到{4 5 6 7 8 9; 1 2 3}，顺序正确
arr = {1,2,3,4,5,6,7,8,9,10}，   k=6，得到{5 6 7 8 9 10; 3 4 1 2}，顺序错误，我们期望后四个{1,2,3,4}
arr = {1,2,3,4,5,6,7,8,9,10,11}, k=6，得到{6 7 8 9 10 11; 2 3 4 5 1}，顺序错误，我们期望后5个为{1,2,3,4,5}
```

但是下面的代码依然运行正确，能正确计算出下轮迭代的K值。设前N-K个元素组成的串为A，那么实际上当K>1/2N时且A的元素滚动到最终位置时，*相当于完成了(N-K)%K次将A的第一个元素移动到最后位置*。设A数组移动到最后由于顺序错乱变成了B串，而我们想要B变成A，只要将B的后(N-K)%K个元素挪到前面即可，这正是第一个for循环完成的事情。

```cpp
class Solution 
{
public:
    void rotate(vector<int>& nums, int k) {
        for (int n = nums.size(), base=0; k = k%n; n -= k, base += k)
        {
            // Swap the last k elements with the first k elements. 
            // The last k elements will be in the correct positions
            // but we need to rotate the remaining (n - k) elements 
            // to the right by k steps.
            for (int i = 0; i < k; i++)
            {
                swap(nums[base+i], nums[base+n - k + i]);
            }
        }
    }
};
```

# 交换子数组法(24ms)
时间复杂度：O(N)
空间复杂度：O(1)

比较简单，看代码即可。

```cpp
class Solution 
{
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        if ((n == 0) || (k <= 0) || (k%n == 0)) {
            return;
        }

        k = k%n;
        // Rotation to the right by k steps is equivalent to swapping 
        // the two subarrays nums[0,...,n - k - 1] and nums[n - k,...,n - 1].
        int start = 0;
        while (k > 0) {
            if (n - k >= k) {
                // The left subarray with size n - k is longer than 
                // the right subarray with size k. Exchange 
                // nums[n - 2*k,...,n - k - 1] with nums[n - k,...,n - 1].
                for (int i = 0; i < k; i++) {
                    swap(nums[start + n - 2*k + i], nums[start + n - k + i]);
                }

                // nums[n - 2*k,...,n - k - 1] are in their correct positions now.
                // Need to rotate the elements of nums[0,...,n - k - 1] to the right 
                // by k%n steps.
                n = n - k;
                k = k%n;
            } else {
                // The left subarray with size n - k is shorter than 
                // the right subarray with size k. Exchange 
                // nums[0,...,n - k - 1] with nums[n - k,...,2*(n - k) - 1].
                for (int i = 0; i < n - k; i++) {
                    swap(nums[start + i], nums[start + n - k + i]);
                }

                // nums[n - k,...,2*(n - k) - 1] are in their correct positions now.
                // Need to rotate the elements of nums[n - k,...,n - 1] to the right 
                // by k - (n - k) steps.
                int tmp = n - k;
                n = k;
                k -= tmp;
                start += tmp;
            }
        }
    }
};
```

# STL法(24ms)
时间复杂度：O(N)
空间复杂度：O(1)

std::rotate的函数原型：
```cpp
template <class ForwardIterator>
  ForwardIterator rotate (ForwardIterator first, ForwardIterator middle,
                          ForwardIterator last);
```
注意它完成的功能是将[first, middle)内的元素移动后面去。

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        std::rotate(nums.begin(), 
                    nums.begin()+nums.size()-k%nums.size(), 
                    nums.end());
    }
};
```

# 其它方法
[这里][2]有一个方法

[1]: https://leetcode.com/problems/rotate-array/
[2]: https://leetcode.com/discuss/30527/three-way-solve-this-problem-the-first-way-interesting-java