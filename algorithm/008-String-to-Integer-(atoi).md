题目链接: [8.String to Integer (atoi)][1]
难度: Easy

- 实现atoi
- 难点在于要自己想边界条件。题目中的边界情况是：

1. 开头可以有空格
2. 可带一个+-号
3. 尾巴可以跟着其他非数字字符
4. 溢出返回INT_MAX或INT_MIN，数字无效返回0


```cpp
int atoi(const char *str) {
    int sign = 1, base = 0, i = 0;
    while (str[i] == ' ') { i++; }
    if (str[i] == '-' || str[i] == '+') {
        sign = 1 - 2 * (str[i++] == '-'); 
    }
    while (str[i] >= '0' && str[i] <= '9') {
        if (base >  INT_MAX / 10 || (base == INT_MAX / 10 && str[i] - '0' > 7)) {
            if (sign == 1) return INT_MAX;
            else return INT_MIN;
        }
        base  = 10 * base + (str[i++] - '0');
    }
    return base * sign;
}
```

[1]: https://leetcode.com/problems/string-to-integer-atoi/