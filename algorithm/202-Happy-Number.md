题目链接：[202. Happy Number][1]

# Trival方法(4ms)
使用hash表记录前进过程中产生的临时数字

注意，32位整数下，最大的数字变换后不会超过2x2 + 9x9x9 (2,999,999,999)，所以直接开一个大小为1000的数组当hash表也是OK的。

```cpp
class Solution {
public:
    int next(int x) {
        int res = 0;
        while (x) {
            const int tmp = x % 10;
            res += tmp * tmp;
            x /= 10;
        }
        return res;
    }
    
    bool isHappy(int n) {
        unordered_set<int> ss;
        while (ss.find(n) == ss.end()) {
            ss.insert(n);
            
            if ((n = next(n)) == 1) {
                return true;
            }
        }
        return false;
    }
};
```

# Floyd Cycle detection(4ms)
使用一快一慢两个指针。本题确定总是有环，所以快慢指针必会相遇。

```cpp
class Solution {
public:
    int next(int x) {
        int res = 0;
        while (x) {
            const int tmp = x % 10;
            res += tmp * tmp;
            x /= 10;
        }
        return res;
    }
    
    bool isHappy(int n) {
        int slow = n, fast = next(n);
        while (slow != fast) {
            slow = next(slow);
            fast = next(next(fast));

            // 添加下面这行可能更快一点？
            //if (fast == 1) return true;
        }
        
        return slow == 1;
    }
};
```

# 以空间换时间方法(1ms)
我们基于空间换时间。上面提到，Int下所有整数的各个digit求平方加和后不会超过1000（实际不会超过810），所以我们直接求[0,1000]内所有整数是否是happy number即可。具体代码参考[这里][4]。

```java
/this is the bitset representation of happy numbers in range[0,810)
private static final long[]happyMark = new long[]{580548859274370L, 35812649762896L, 
                          5764889547766761510L, 158621866461187L, -9061136725337702208L, 
                         -8574391826910016959L, 4683743612499927428L, 286423854940160L, 
                          29290989780729856L, 7566260683533189120L, 1170945809492058640L, 
                          720593571220033568L, 292095590400L};  

public boolean isHappy(int n) {
    if( n>810 ){
        int sum = 0, remainder = 0;
        while( n>0 ){
            remainder = n%10;
            sum += remainder*remainder;
            n /= 10;
        }
        n = sum;
    }
    // 将n变换为索引
    int idx = ( n>>6 );
    long bitRep = ( 1L<< (n&0x3f) );
    return ( happyMark[idx]&bitRep )!=0;
}
```
# 数学方法1(4ms)
All numbers in [2, 6] are not happy (and all not happy numbers end on a cycle that hits this interval).

证明在[这里][2].

基于上述定理，我们只要一直前进，直到落到上述区间即可。

```cpp
class Solution {
public:
    int next(int x) {
        int res = 0;
        while (x) {
            const int tmp = x % 10;
            res += tmp * tmp;
            x /= 10;
        }
        return res;
    }
    
    bool isHappy(int n) {
        while ((n = next(n)) > 6) ;
        return n == 1;
    }
};
```

# 数学方法2(4ms)
If a number is NOT happy, there is always a 4 in the cycle.

实际上还有很多MAGIC number，参考[这里][3]

证明同上。

```cpp
class Solution {
public:
    int next(int x) {
        int res = 0;
        while (x) {
            const int tmp = x % 10;
            res += tmp * tmp;
            x /= 10;
        }
        return res;
    }
    
    bool isHappy(int n) {
        const int MAGIC = 4;
        while (n != MAGIC && n != 1)
            n = next(n);
            
        return n == 1;
    }
};
```

# 数学方法3(4ms)
All numbers' calculation will goes into a single digit at some time. Only 1 and 7 are happy numbers.

```cpp
class Solution {
public:
    int next(int x) {
        int res = 0;
        while (x) {
            const int tmp = x % 10;
            res += tmp * tmp;
            x /= 10;
        }
        return res;
    }
    
    bool isHappy(int n) {
        while (n >= 10)
            n = next(n);
            
        return n == 1 || n == 7;
    }
};
```

[1]: https://leetcode.com/problems/happy-number/
[2]: https://en.wikipedia.org/wiki/Happy_number
[3]: https://leetcode.com/discuss/53719/fastest-java-code-so-far-with-comments