题目链接: [165.Compare Version Numbers][1]
难度: Easy

描述：给定一系列版本号，请比较版本号的大小。模板号是一堆整数，它们之间用'.'做间隔。

有一些corner case要注意，比如1.0和1两个版本号是一样的。以及01和1也是一样的。


# 模拟法(0ms)
时间复杂度：O(N)
空间复杂度：O(N)

将版本号切成若干个段，然后比较这些段。使用STL可以很容易做到。

```cpp
class Solution {
public:
    int compareVersion(string version1, string version2) {
        replace(version1.begin(), version1.end(), '.', ' ');
        replace(version2.begin(), version2.end(), '.', ' ');
        
        vector<int> v1_parts, v2_parts;
        istringstream in_v1(version1), in_v2(version2);

        using IS_Iter = istream_iterator<int>;
        copy(IS_Iter(in_v1), IS_Iter(), back_inserter(v1_parts));
        copy(IS_Iter(in_v2), IS_Iter(), back_inserter(v2_parts));

        v1_parts.resize(max(v1_parts.size(), v2_parts.size()));
        v2_parts.resize(max(v1_parts.size(), v2_parts.size()));
        return v1_parts < v2_parts ? -1 : (v2_parts < v1_parts ? 1 : 0);
    }
};
```

# 模拟2(0ms)
时间复杂度：O(N)
空间复杂度：O(1)

我们可以弄两个循环来分别求每一段的版本号，而不是预先计算所有版本号。

```cpp
class Solution {
public:
    int compareVersion(string version1, string version2) {
        for (int i=0, j=0; i<version1.size() || j<version2.size(); ++i, ++j) {
            int num1 = 0, num2 = 0;
            
            while(i < version1.size() && version1[i]!='.'){
                num1 = num1*10+(version1[i]-'0');
                i++;
            }
    
            while(j < version2.size() && version2[j]!='.'){
                num2 = num2*10+(version2[j]-'0');;
                j++;
            }
    
            if (num1 > num2) return 1;
            else if(num1 < num2) return -1;
        }
    
        return 0;
    }
};
```

# 模拟3(0ms)
时间复杂度：O(N)
空间复杂度：O(1)

更简略的一个版本

```cpp
class Solution {
public:
    int compareVersion(string version1, string version2) {
        istringstream ver1(version1 + "."), ver2(version2 + ".");
        
        while (ver1.good() || ver2.good()) {
            int val1 = 0, val2 = 0;
            char dot;
            
            if (ver1.good()) ver1 >> val1 >> dot;
            if (ver2.good()) ver2 >> val2 >> dot;
            
            if (val1 > val2) return 1;
            else if (val1 < val2) return -1;
        }
        
        return 0;
    }
};
```

[1]: https://leetcode.com/problems/compare-version-numbers/