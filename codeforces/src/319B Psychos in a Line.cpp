//
// Created by Psy.C on 2026/1/7.
//
/**
* 使用单调栈算法
遍历数组a，维护一个单调递减的栈
当栈顶元素小于等于当前元素时，弹出并更新b[i]
增加b[i]的值
如果栈为空，设置b[i] = 0；否则更新res
将当前索引压入栈
 */
#include <iostream>
#include <vector>
#include <stack>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n,res = 0; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    stack<int> s;
    for (int i = 0; i < n; ++i) {
        while (!s.empty() && a[s.top()] <= a[i]) {
            b[i] = max(b[i], b[s.top()]);
            s.pop();
        }
        b[i]++;
        if (s.empty()) b[i] = 0; else res = max(res, b[i]);
        s.push(i);
    }
    cout << res;
    return 0;
}