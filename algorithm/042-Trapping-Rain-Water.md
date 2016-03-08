题目链接: [42.Trapping Rain Water][1]
难度: Hard

- 坑洼地面求积水


# O(n) time, O(n) space，8ms，3 pass

- 每个坐标假如有积水，则积水高度 = min（其左侧的最高高度，其右侧的最高高度）

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        const int n = height.size();
        vector<int> max_left(n, 0), max_right(n, 0);
        
        for (int i = 1; i < n; ++i) {
            max_left[i] = max(max_left[i - 1], height[i - 1]);
            max_right[n - 1 - i] = max(max_right[n - i], height[n - i]);
        }
        
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int h = min(max_left[i], max_right[i]);
            if (h > height[i]) 
                sum += h - height[i];
        }
        
        return sum;
    }
};
```

# O(n) time, O(1) space，8ms，2 pass

先找到最高峰，然后每个坐标假如有积水，则积水高度 = 该坐标非高峰那边的最高高度

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        const int n = height.size();
        int maxIdx = 0; // 最高峰对应坐标
        for (int i = 0; i < n; ++i) 
            if (height[i] > height[maxIdx]) maxIdx = i;
            
        int sum = 0;
        for (int i = 0, peak = 0; i < maxIdx; ++i) 
            if (height[i] > peak) peak = height[i];
            else                  sum += peak - height[i];
        
        for (int i = n - 1, peak = 0; i > maxIdx; --i) 
            if (height[i] > peak) peak = height[i];
            else                  sum += peak - height[i];
        
        return sum;
    }
};
```

# O(n) time, O(1) space，8ms，1 pass

将maxleft和maxright的维护隐藏到left和right的推进过程中

```cpp
class Solution {
public:
	int trap(vector<int>& height) {
		const int n = height.size();
		int left = 0; int right = n - 1;
		int res = 0;
		int maxleft = 0, maxright = 0;
		while (left <= right){
			if (height[left] <= height[right]){ // && maxleft < height[right]，此时height[right]替代了maxright的作用
				if (height[left] >= maxleft) maxleft = height[left];
				else res += maxleft - height[left];
				left++;
			}
			else{ // 此时height[left]替代了maxleft的作用
				if (height[right] >= maxright) maxright = height[right];
				else res += maxright - height[right];
				right--;
			}
		}
		return res;
	}
};
```


[1]: https://leetcode.com/problems/trapping-rain-water/