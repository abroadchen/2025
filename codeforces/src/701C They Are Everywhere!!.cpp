//
// Created by Psy.C on 2026/4/18.
//
/**
#define idx(x) (x-'A'): 宏定义，将字符映射到索引0-25（大写字母）或0-57（包括小写字母）
n: 字符串长度
vis[58]: 访问计数数组，记录每个字符的出现次数
A-Z: 索引0-25, a-z: 索引26-51, 其他字符可能占用52-57
c[N]: 输入字符数组
读入字符串长度和字符串本身
遍历字符串，统计有多少种不同的字符
dif: 不同字符的种类数

ans = inf: 最短子串长度，初始化为无穷大
ant = 0: 当前窗口中不同字符的数量
st = 0: 滑动窗口的起始位置
扩展窗口
i: 滑动窗口的右边界
id = idx(c[i]): 获取当前字符的索引
if (!vis[id]) ant++: 如果该字符首次出现，不同字符数加1
vis[id]++: 该字符出现次数加1
缩小窗口
if (ant == dif): 当窗口包含所有不同字符时
while (ant == dif): 尝试缩小窗口直到不再包含所有字符
ans = min(ans, i-st+1): 更新最短长度
int t = idx(c[st]): 获取左边界字符的索引
if (vis[t] == 1) ant--: 如果该字符只剩一个，不同字符数减1
vis[t]--: 该字符出现次数减1
st++: 左边界右移

扩展阶段：右指针i向右移动，扩大窗口直到包含所有字符
收缩阶段：左指针st向右移动，缩小窗口直到不再包含所有字符
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define idx(x) (x-'A')
using namespace std;
constexpr int N = 1e5+5, inf = 0x3f3f3f3f;
int n, vis[58];
char c[N];
int main() {
    fast;
    cin >> n;
    cin >> c; int dif = 0;
    for (int i = 0; i < n; ++i)
        if (!vis[c[i]-'A']) { dif++; vis[c[i]-'A']++; }
    int ans = inf, ant = 0, st = 0;
    memset(vis, 0, sizeof vis);
    for (int i = 0; i < n; ++i) {
        int id = idx(c[i]);
        if (!vis[id]) ant++;
        vis[id]++;
        if (ant == dif) {
            while (ant == dif) {
                ans = min(ans, i-st+1);
                int t = idx(c[st]);
                if (vis[t] == 1) ant--;
                vis[t]--;
                st++;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}