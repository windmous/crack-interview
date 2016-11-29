题目链接: [158.Read N Characters Given Read4 II - Call multiple times][1]
难度: Hard

The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function may be called multiple times.

由于可能被多次调用，注意额外读到的数据需要缓存起来。

# queue模拟
时间复杂度：O(N)
空间复杂度：O(1)
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
        int read_cnt = 0;
        while (read_cnt < n && !read_buff.empty()) {
            buf[read_cnt ++] = read_buff.front();
            read_buff.pop();
        }
        
        while (n - read_cnt >= 4) {
            int real_read = read4(buf+read_cnt);
            read_cnt += real_read;
            if (real_read < 4) return read_cnt;
        }
        
        if (n != read_cnt) {
            char temp_buff[4];
            int real_read = read4(temp_buff);
            memcpy(buf+read_cnt, temp_buff, min(real_read, n-read_cnt));
            for (int i = n - read_cnt; i < real_read; ++ i) {
                read_buff.push(temp_buff[i]);
            }
            read_cnt += min(real_read, n - read_cnt);
        }
        return read_cnt;
    }
    
private:
    queue<char> read_buff;
};
```

# 专用内存法
时间复杂度：O(N)
空间复杂度：O(1)

这里额外开了一块内存用来调用read4，然后再拷贝到用户空间中。

```cpp
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    Solution() : buff_cnt(0), buff_idx(0) {
        
    }
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int read_cnt = 0;
        while (read_cnt < n && (buff_idx < buff_cnt || (buff_idx=0, buff_cnt=read4(read_buff)) != 0))
            buf[read_cnt ++] = read_buff[buff_idx ++];
        return read_cnt;
    }
    
private:
    char read_buff[4];
    int buff_cnt, buff_idx;
};
```

[1]: https://leetcode.com/problems/read-n-characters-given-read4-ii-call-multiple-times/