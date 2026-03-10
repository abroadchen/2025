//
// Created by Psy.C on 2026/3/10.
//
/**
st: 存储操作数的栈
op: 存储运算符的栈

从操作数栈取出a和b（注意顺序：先取的是右操作数）
从运算符栈取出运算符
根据运算符执行加法或乘法
将结果压入操作数栈

在运算符栈压入左括号，字符串末尾添加右括号（确保所有运算完成）
数字：转换为整型并压入操作数栈
左括号：直接压入运算符栈
右括号：计算直到遇到左括号，然后弹出左括号
运算符：根据优先级规则进行运算，然后压入当前运算符

t1, t2: 临时字符串变量
x[]: 记录乘号位置的数组
cnt: 乘号计数器
ans: 最大答案
输入原始表达式，记录所有乘号的位置

枚举所有可能的括号插入方案
外层循环：确定左括号位置（在第i个乘号后）
内层循环：确定右括号位置（在第j个乘号后或字符串末尾）
对每种括号组合计算表达式值，并更新最大值

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 5e3+5;

stack<ll> st;
stack<char> op;
void get() {
    ll a = st.top(); st.pop();
    ll b = st.top(); st.pop();
    ll c = 0;
    char p = op.top(); op.pop();
    if (p == '+') c = a + b;
    if (p == '*') c = a * b;
    st.push(c);
}

string s;
ll calc() {
    while (!st.empty()) st.pop();
    while (!op.empty()) op.pop();
    op.push('('), s += ')';
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] >= '0' && s[i] <= '9') st.push(s[i] - '0');
        else if (s[i] == '(') op.push(s[i]);
        else if (s[i] == ')') {
            while (op.top() != '(') get();
            op.pop();
        } else {
            while (!op.empty() && op.top() != '(' &&
                (s[i] == '+' || op.top() == '*')) get();
            op.push(s[i]);
        }
    }
    return st.top();
}

string t1, t2;
ll x[N], cnt, ans;
int main() {
    fast;
    cin >> s; t1 = s; x[0] = -1;
    for (int i = 0; i < s.size(); ++i)
        if (s[i] == '*') x[++cnt] = i;
    for (int i = 0; i <= cnt; ++i, s = t1) {
        s.insert(x[i]+1, "(");
        t2 = s;
        for (int j = i + 1; j <= cnt+1; ++j, s = t2) {
            s.insert(j<=cnt ? x[j]+1 : s.size(), ")");
            ans = max(ans, calc());
        }
    }
    cout << ans;
    return 0;
}