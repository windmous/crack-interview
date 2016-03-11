题目链接: [76.Minimum Window Substring][1]
难度: Hard

- 给定S和T两个字符串，在S中找到包含T所有字符的最小窗口，时间复杂度限制为O(n)

# 哈希表+双指针

```cpp
string minWindow(string s, string t) {
	vector<int> map(128,0);   
	for(auto c: t) map[c]++;  
	int counter=t.size(), begin=0, end=0, d=INT_MAX, head=0;
	while(end < s.size()){
		if(map[s[end++]]-->0) counter--; //in t，t中没出现过的字符对应的map初始值为0，不会触发counter自减
		while(counter==0){ //valid
			if(end-begin<d)  d=end-(head=begin); //记录最小长度
			if(map[s[begin++]]++==0) counter++;  //make it invalid
		}  
	}
	return d==INT_MAX? "":s.substr(head, d);
}
```

作者给出的模板：
```cpp
int findSubstring(string s){
	vector<int> map(128,0);
	int counter; // check whether the substring is valid
	int begin=0, end=0; //two pointers, one point to tail and one  head
	int d; //the length of substring

	for() { /* initialize the hash map here */ }

	while(end<s.size()){
		if(map[s[end++]]-- ?){  /* modify counter here */ }      // end前进，修改counter
		while(/* counter condition */){ 						 // 若counter符合某个条件
			 /* update d here if finding minimum*/						// opt1.更新全局最优解（此时counter符合某个条件）
			//increase begin to make it invalid/valid again				// begin前进，直至使counter再次失效
			if(map[s[begin++]]++ ?){ /*modify counter here*/ }
		}
		/* update d here if finding maximum*/					 // opt2.更新全局最优解（此时counter不符合某个条件）
	}
	return d;
}

// 两处更新全局最优解选择哪个，要依照counter符合某个条件时修改全局解还是counter不符合某个条件时修改而定
```

用这个模板也能解P3 Longest Substring Without Repeating Characters

[1]: https://leetcode.com/problems/minimum-window-substring/