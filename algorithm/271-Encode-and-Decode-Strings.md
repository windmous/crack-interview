题目链接: [271.Encode and Decode Strings][1]
难度: Medium

Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.

Machine 1 (sender) has the function:

string encode(vector<string> strs) {
  // ... your code
  return encoded_string;
}
Machine 2 (receiver) has the function:
vector<string> decode(string s) {
  //... your code
  return strs;
}
So Machine 1 does:

string encoded_string = encode(strs);
and Machine 2 does:

vector<string> strs2 = decode(encoded_string);
strs2 in Machine 2 should be the same as strs in Machine 1.

Implement the encode and decode methods.

Note:
The string may contain any possible characters out of 256 valid ascii characters. Your algorithm should be generalized enough to work on any possible characters.
Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
Do not rely on any library method such as eval or serialize methods. You should implement your own encode/decode algorithm.

# 数字前缀法(69ms)
时间复杂度：O(N)
空间复杂度：O(N)

```cpp
class Codec {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string result;
        for (const string &part : strs) {
            result += to_string(part.size());
            result += "#";
            result += part;
        }
        return result;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> result;
        long idx = 0;
        while (idx < s.size()) {
            auto seperator_idx = s.find_first_of('#', idx);
            long part_len = std::stoi(s.substr(idx, seperator_idx - idx));
            result.emplace_back(s.substr(seperator_idx+1, part_len));
            idx = seperator_idx + part_len + 1;
        }
        return result;
    }
};
```

# Seperator方法
时间复杂度：O(N)
空间复杂度：O(1)

```python

class Codec:

    def encode(self, strs):
        """Encodes a list of strings to a single string.

        :type strs: List[str]
        :rtype: str
        """
        return "".join(s.replace("@", "@@") + " @ " for s in strs)


    def decode(self, s):
        """Decodes a single string to a list of strings.

        :type s: str
        :rtype: List[str]
        """
        return [part.replace("@@", "@") for part in s.split(" @ ")[:-1]]

```

[1]: https://leetcode.com/problems/encode-and-decode-strings/