//
// Created by Psy.C on 2025/12/3.
//
/*
*n: 字符串长度
d: 回文子串的最大长度
s[N]: 输入字符串
r[N]: 结果字符串
p[N]: 幂次数组，用于字符串哈希
ha[N]: 正向哈希值数组
rha[N]: 反向哈希值数组
 *
*rha[ed] - rha[st-1]*p[dx] 计算反向哈希值
乘以 p[st-1] 进行对齐
与正向哈希值 ha[ed] - ha[st-1] 比较
如果不相等则不是回文，返回true
 *
*循环尝试字符'a'到'z'：
如果t为真（仍在匹配原字符串），从s[x]开始
否则从'a'开始
*更新正向和反向哈希值：
正向：累加当前字符的哈希贡献
反向：滚动哈希计算
*检查条件：
长度为d的子串不是回文
长度为d+1的子串不是回文
递归处理下一个位置
如果满足条件，返回true
 *
*
寻找第一个不是'z'的字符并将其加1，之前的'z'重置为'a'
如果所有字符都是'z'，输出"Impossible"并退出
 *初始化幂次数组，基数为175
*从位置0开始DFS搜索，初始时仍在匹配原字符串
如果找不到解，输出"Impossible"
 *
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 500100
#define ull unsigned long long int
using namespace std;

int n, d;
char s[N], r[N];
ull p[N], ha[N], rha[N];


bool ok(int ed, const int dx) {//检查以ed结尾、长度为dx的子串是否为回文
    ed++;//转换为1-indexed，计算起始位置
    const int st = ed - dx + 1;
    if (st < 0) return true;//不是回文
    if ((rha[ed] - rha[st-1]*p[dx])*p[st-1]
        != ha[ed] - ha[st-1]) return true;
    return false;//是回文，返回false
}

//x为当前处理位置，t为是否仍在匹配原字符串的标志
bool dfs(const int x, const int t) {//构造结果字符串
    if (x == n) { cout << r << '\n'; return true; }//处理完所有字符
    for ((r[x] = t ? s[x] : 'a'); r[x] <= 'z'; ++r[x]) {
        ha[x + 1] = ha[x] + r[x] * p[x];
        rha[x + 1] = rha[x] * 175 + r[x];
        if (ok(x, d) && ok(x, d + 1) &&
            dfs(x + 1, t && r[x] == s[x])) return true;
    }
    return false;
}

int main() {
    fast;
    cin >> d >> s; n = static_cast<int>(strlen(s));
    int i = n - 1;
    for (; i >= 0 && s[i] == 'z'; --i) s[i] = 'a';
    if (i < 0) { cout << "Impossible" << '\n'; return 0; }
    s[i]++; p[0] = 1;
    for (i = 1; i < n + 100; ++i) p[i] = p[i - 1] * 175;
    if (dfs(0, 1) == false) cout << "Impossible" << '\n';
    return 0;
}