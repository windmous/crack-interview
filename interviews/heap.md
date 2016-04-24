#include <iostream>
#include <vector>
using namespace std;

class MaxPQ{
public:
	MaxPQ() : vec(1, -1) { } // 存储于vec[1..n]，vec[0]没有使用

	MaxPQ(vector<int> vi) {
		vec.push_back(-1);
		for (auto elem : vi)
			push(elem);
	}

	bool empty() { return vec.size() == 1; }
	int size()   { return vec.size() - 1; }
	int top()    { return vec[1]; }
	void push(int val) {
		vec.push_back(val);
		swim(vec.size() - 1);
	}
	
	void pop() {
		swap(vec[1], vec.back());
		vec.pop_back();
		sink(1);
	}

private:
	vector<int> vec;

	void swim(int k) { 
		while (k > 1 && vec[k / 2] < vec[k]) {
			swap(vec[k / 2], vec[k]);
			k /= 2;
		}
	}

	void sink(int k) {
		int noElem = vec.size() - 1; // noElem是最后一个元素的id
		while (2 * k <= noElem) {
			int j = 2 * k;
			if (j < noElem && vec[j] < vec[j + 1]) ++j; // j指向vec[k]的两个儿子中较大一方
			if (vec[k] >= vec[j]) break; // vec[k] 比两个儿子都大，无需下沉
			swap(vec[k], vec[j]);
			k = j;
		}
	}
};

void test(MaxPQ pq) {
	while (!pq.empty()) {
		cout << pq.top() << endl;
		pq.pop();
	}
	cout << endl;
}

int main()
{
	test(MaxPQ(vector < int > {1, 3, 2, 4, 5, 7, 6, 8}));
	test(MaxPQ(vector < int > {}));
	test(MaxPQ(vector < int > {1,1,1,1,2}));
	test(MaxPQ(vector < int > {INT_MAX, INT_MIN, INT_MIN, INT_MAX}));

	return 0;
}