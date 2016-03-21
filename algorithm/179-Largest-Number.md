题目链接: [179.Largest Number][1]
难度: Medium

描述：给出一系列正数，将其首尾拼接成一个新数，要求新数尽可能大。

# 比较法(8ms)

```cpp
class Solution {
public:
    string largestNumber(vector<int> &num) {
        vector<string> arr;
        arr.reserve(num.size());

        transform(num.begin(), num.end(), back_inserter(arr), 
                    [](int x){return to_string(x);});
        sort(arr.begin(), arr.end(), [](string &s1, string &s2){ return s1+s2>s2+s1; });
        auto result = accumulate(arr.begin(), arr.end(), string());
        
        return (!result.size()||result[0]=='0')? "0":result;
    }
    
};
```

我们需要证明两点：

1. 这个数组是Sortable的，意味着若A<B， B<C，也应该有A<C

2. 把排序后的数组拼起来即可得到最值。

先证明1：
```
Proof:

    Let us define f(X) = 10^(lgX + 1), then XY = f(Y)X + Y

    If AB <= BA, then we have
    f(B)A + B <= f(A)B + A
    (f(B) - 1)A <= (f(A) - 1)B
    that is
    A <= B·(f(A) - 1) / (f(B) - 1)   (1)

    If BC <= CB, then we have
    f(C)B + C <= f(B)C + B
    (f(C) - 1)B <= (f(B) - 1)C
    that is
    B <= C·(f(B) - 1) / (f(C) - 1)   (2)

    Combine (1), (2), we have
    A <= C·(f(A) - 1) / (f(C) - 1)
    (f(C) - 1)A <= (f(A) - 1)C
    f(C)A + C <= f(A)C + A
    AC <= CA
```

证明2:

![图1](https://i.imgsafe.org/8de935e.png)

![图2](https://i.imgsafe.org/90816ce.png)

[1]: https://leetcode.com/problems/largest-number/