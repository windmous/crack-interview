题目链接: [125.Valid Palindrome][1]
难度: Easy

判断字符串是否是回文。只考虑字符串中的字母和数字，忽略其他，忽略大小写。

Corner case：空字符串也是回文。

# 挺简单的

isalnum: The result is true if either isalpha or isdigit would also return true.

```cpp
bool isPalindrome(string s) {
    for (int i = 0, j = s.size() - 1; i < j; i++, j--) { // Move 2 pointers from each end until they collide
        while (isalnum(s[i]) == false && i < j) i++; // Increment left pointer if not alphanumeric
        while (isalnum(s[j]) == false && i < j) j--; // Decrement right pointer if no alphanumeric
        if (toupper(s[i]) != toupper(s[j])) return false; // Exit and return error if not match
    }

    return true;
}
```


[1]: https://leetcode.com/problems/valid-palindrome/