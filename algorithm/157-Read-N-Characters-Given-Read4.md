题目链接: [157.Read N Characters Given Read4][1]
难度: Easy

The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function will only be called once for each test case.

# 模拟法(0ms)
时间复杂度：O(N)
空间复杂度：O(1)

Discussion中的很多答案都是错的，要防止缓冲区溢出。

```cpp
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int read_cnt = 0, real_read = 4;
        while (n - read_cnt >= 4) {
            real_read = read4(buf+read_cnt);
            read_cnt += real_read;
            if (real_read < 4) return read_cnt;
        }
        
        if (n != read_cnt) {
            char temp_buf[4];
            real_read = read4(temp_buf);
            memcpy(buf+read_cnt, temp_buf, min(real_read, n-read_cnt));
            read_cnt += min(real_read, n-read_cnt);
        }
        
        return read_cnt;
    }
};
```

[1]: https://leetcode.com/problems/read-n-characters-given-read4/