题目链接: [97.Interleaving String][1]
难度: Hard

判断string s3是否为s1和s2的interleaving

# 动归

想象成一个table，当s3的下一个字符和s1的下一个字符相同时可以向右移动，和s2的下一个字符相同时可以向下移动，寻找从开始到右下角（终点）的路径。

https://leetcode.com/discuss/11694/my-dp-solution-in-c
```cpp
bool isInterleave(string s1, string s2, string s3) {

    if(s3.length() != s1.length() + s2.length())
        return false;

    bool table[s1.length()+1][s2.length()+1];

    for(int i=0; i<s1.length()+1; i++)
        for(int j=0; j< s2.length()+1; j++){
            if(i==0 && j==0)
                table[i][j] = true;
            else if(i == 0)
                table[i][j] = ( table[i][j-1] && s2[j-1] == s3[i+j-1]);
            else if(j == 0)
                table[i][j] = ( table[i-1][j] && s1[i-1] == s3[i+j-1]);
            else
                table[i][j] = (table[i-1][j] && s1[i-1] == s3[i+j-1] ) || (table[i][j-1] && s2[j-1] == s3[i+j-1] );
        }

    return table[s1.length()][s2.length()];
}
```

# BFS

注意到动归方法中，table不是每个元素都要访问的，所以可以将所有可行路径想象成一棵树，利用BFS完成。因为只能向右和向下走，所以不会出现回路问题。

https://leetcode.com/discuss/19973/8ms-c-solution-using-bfs-with-explanation
```cpp
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        typedef pair<int, int> index;
        unordered_set<int> visited;
        queue<index> q;
        q.push(index(-1, -1));

        int cols = s2.size() + 1;
        while (!q.empty()) {
            index idx = q.front();
            q.pop();

            int i = idx.first + 1;
            int j = idx.second + 1;

            if (i == s1.size() && j == s2.size()) {
                return i + j == s3.size();
            }

            if (i + j < s3.size()) {
                char next = s3[i + j];
                if (i < s1.size() && s1[i] == next) {
                    if (visited.insert((i + 1) * cols + j).second) {
                        q.push(index(i, j - 1));
                    }
                }
                if (j < s2.size() && s2[j] == next) {
                    if (visited.insert(i * cols + j + 1).second) {
                        q.push(index(i - 1, j));
                    }
                }
            }
        }

        return false;
    }
};
```

# DFS

DFS比BFS找解应该更快，而且更好写一点，（下面的解是java的版本）

```java
public boolean isInterleave(String s1, String s2, String s3) {
    char[] c1 = s1.toCharArray(), c2 = s2.toCharArray(), c3 = s3.toCharArray();
    int m = s1.length(), n = s2.length();
    if(m + n != s3.length()) return false;
    return dfs(c1, c2, c3, 0, 0, 0, new boolean[m + 1][n + 1]);
}

public boolean dfs(char[] c1, char[] c2, char[] c3, int i, int j, int k, boolean[][] invalid) {
    if(invalid[i][j]) return false;
    if(k == c3.length) return true;
    boolean valid = 
        i < c1.length && c1[i] == c3[k] && dfs(c1, c2, c3, i + 1, j, k + 1, invalid) || 
        j < c2.length && c2[j] == c3[k] && dfs(c1, c2, c3, i, j + 1, k + 1, invalid);
    if(!valid) invalid[i][j] = true;
    return valid;
}
```

[1]: https://leetcode.com/problems/interleaving-string/