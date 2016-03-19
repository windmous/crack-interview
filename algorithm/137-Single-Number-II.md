题目链接: [137.Single Number II][1]
难度: Medium

给定一个数组，所有元素都出现3次，但只有一个元素出现了1次或2次，找出该元素。

# 三进制法
```cpp
public int singleNumber(int[] A) {
    int ones = 0, twos = 0;
    for(int i = 0; i < A.length; i++){
        ones = (ones ^ A[i]) & ~twos;
        twos = (twos ^ A[i]) & ~ones;
    }
    return ones;
}
```

[1]: https://leetcode.com/problems/single-number-ii/