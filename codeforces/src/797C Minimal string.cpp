//
// Created by Psy.C on 2026/9/17.
//
/**
字符串 s 下标从 0 开始，而数组 a 下标约定为 1..n（对应 s[0..n-1]）‍。这里强行建立了映射：a[pos] 表示从 s[pos-1] 处开始的子串中，最小字符的下标（这个下标是1-based 的 a 下标，即"第 pos 个字符"）。
初始化：
a[n] = n-1：表示在"空后缀/末尾哨兵"位置，最小字符下标被设为 n-1。这是用来作为比较的兜底，避免越界。
循环（从后往前递推）：
j = n-i+1，当 i=2 时 j=n-1，i=3 时 j=n-2，… i=n 时 j=1。也就是 j 从 n-1 递减到 1。
s[j-1] 是第 j 个字符（1-based）对应的字符。
比较 s[j-1] < s[a[j+1]]：
若第 j 个字符比自己后缀（第 j+1 位之后）的最小字符还小，则从 j 开始的后缀最小字符就是它自己：a[j] = j-1。
否则，从 j 开始的后缀最小字符等于从 j+1 开始的后缀最小字符：a[j] = a[j+1]。
结论：a[j] 存的是：从第 j 个字符（s[j-1]）往后的后缀中，字典序最小字符的位置（1-based）‍。这就是经典的"后缀最小字符"预处理数组

st.push(s[i-1])：先把第 i 个字符压入栈中。
关键判断 s[a[i+1]] >= st.top()：
a[i+1] = 从第 i+1 个字符开始的后缀中最小字符的位置。
s[a[i+1]] = 那个"后缀最小字符"的值。
比较条件：若"后面还没处理的字符中最小的那个" ≥ 栈顶字符，则弹出栈顶并输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5;
int a[N+5];//从某个位置开始的后缀中、字典序最小的字符的下标
stack<char, list<char>> st;
int main() {
    fast;
    string s; cin >> s;
    int n = s.size(); a[n] = n-1;//下标 n 的"后缀"最小位置指向末尾
    for (int i = 2; i <= n; ++i) {
        const int& j = n-i+1;
        if (s[j-1] < s[a[j+1]]) a[j] = j-1;
        else a[j] = a[j+1];
    }
    for (int i = 1; i <= n; ++i) {
        st.push(s[i-1]);
        while ((!st.empty()) && s[a[i+1]] >= st.top()) {
            cout << st.top(); st.pop();
        }
    }
    while (!st.empty()) {
        cout << st.top(); st.pop();
    }
    return 0;
}