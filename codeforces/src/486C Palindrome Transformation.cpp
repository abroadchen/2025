//
// Created by Psy.C on 2026/2/17.
//
/**
n: 字符串长度
p: 起始位置
s[N]: 输入字符串
v: 存储需要操作的位置

res = 0: 总操作成本
m = n/2: 只需检查前一半，因为要对称
int t = abs(s[i] - s[n-i-1]): 计算位置i和对称位置n-i-1的字符差异
t = min(t, 26-t): 考虑字母表循环，取顺时针或逆时针的较小距离
例如：'a'到'z'可以是+25（a→z）或-1（z→a），取较小值1
res += t: 累加操作成本
if (t): 如果需要改变字符
abs(i+1-p) < abs(n-i-p): 比较哪个位置离起点p更近
? i+1 : n-i: 选择更近的位置加入v

m = v.size(): 获取需要操作的位置数
if (m == 0) return res: 如果无需操作，直接返回成本
ranges::sort(v): 排序操作位置
return res + v[m-1] - v[0] + min(abs(v[m-1]-p), abs(v[0]-p)):
res: 字符转换成本
v[m-1] - v[0]: 访问所有位置的最小移动距离（直线移动）
min(abs(v[m-1]-p), abs(v[0]-p)): 从起点到访问区间的最小距离

时间复杂度：O(n log n)（主要是排序）
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

int n, p;
char s[N];
vector<int> v;
int get() {
    int res = 0, m = n/2;
    for (int i = 0; i < m; ++i) {
        int t = abs(s[i] - s[n-i-1]);
        t = min(t, 26-t);
        res += t;
        if (t) v.push_back(abs(i+1-p) < abs(n-i-p) ? i+1 : n-i);
    }
    m = v.size();
    if (m == 0) return res;
    ranges::sort(v);
    return res + v[m-1] - v[0] + min(abs(v[m-1]-p), abs(v[0]-p));
}

int main() {
    fast;
    cin >> n >> p >> s;
    cout << get() << '\n';
    return 0;
}