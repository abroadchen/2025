//
// Created by Psy.C on 2026/4/12.
//
/**
n: 字符串长度
m: 操作次数
p: 初始光标位置
b[N]: 存储括号匹配位置
str: 输入字符串
op: 操作字符串
s, t: 两个栈（s是光标左边，t是光标右边）

将光标左边的字符索引放入s
将光标右边的字符索引放入t（逆序，模拟栈）
b[S.top()] = i：左括号匹配右括号
b[i] = S.top()：右括号匹配左括号
如果删除的是左括号（p < b[p]）：删除该括号及其匹配的右括号之间的所有字符
如果删除的是右括号（b[p] < p）：删除该括号及其匹配的左括号之间的所有字符
然后将光标移到下一个位置

输出s中的字符（正序）
输出t中的字符（逆序，因为t是栈结构）
形成最终的字符串

 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e5+5;

int n, m, p, b[N];
char str[N], op[N];
vector<int> s, t;
int main() {
    cin >> n >> m >> p;
    scanf("%s", str + 1);
    for (int i = 1; i <= p; ++i) s.push_back(i);
    for (int i = n; i > p; --i) t.push_back(i);
    stack<int> S;
    for (int i = 1; i <= n; ++i) {
        if (str[i] == '(') S.push(i);
        if (str[i] == ')') b[S.top()] = i, b[i] = S.top(), S.pop();
    }
    scanf("%s", op + 1);
    for (int i = 1; i <= m; ++i) {
        if (op[i] == 'L') t.push_back(s.back()), s.pop_back();//光标左移
        if (op[i] == 'R') s.push_back(t.back()), t.pop_back();//光标右移
        if (op[i] == 'D') {
            p = s.back();
            if (p < b[p]) {
                s.pop_back();
                while (!t.empty() && t.back() <= b[p]) t.pop_back();
            }
            if (b[p] < p)
                while (!s.empty() && s.back() >= b[p]) s.pop_back();
            if (!t.empty())
                s.push_back(t.back()), t.pop_back();
        }
    }
    for (int i : s) printf("%c", str[i]);
    for (int i = t.size()-1; i >= 0; --i) printf("%c", str[t[i]]);
    printf("\n");
    return 0;
}