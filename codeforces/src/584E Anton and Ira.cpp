//
// Created by Psy.C on 2026/3/17.
//
/**
n：数组长度
p[N]：置换数组
s[N]：目标序列
pos[N]：s数组中每个值的位置
ans：交换次数
v：存储交换操作

将p数组中的值替换为其在s数组中的位置
这样p[i]表示原来p[i]这个值在s数组中的位置
计算数组p相对于有序数组的偏移量
这个偏移量除以2近似等于需要的交换次数

对于每个位置i，找到值为i的元素所在位置cur
如果cur ≠ i，说明需要移动
从cur位置开始向前扫描，找到所有值≥cur的元素
与当前元素交换，并记录交换操作
更新cur位置

时间复杂度：
O(n²)，最坏情况下需要O(n²)次交换
空间复杂度：
O(n)，用于存储数组和操作记录
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ii pair<int, int>
using namespace std;
constexpr int N = 2005;
int n, p[N], s[N], pos[N], ans;
vector<ii> v;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> p[i];
    rep(i,n) cin >> s[i], pos[s[i]] = i;
    rep(i,n) p[i] = pos[p[i]];
    rep(i,n) ans += abs(i - p[i]);
    ans /= 2;
    rep(i,n) {
        int cur = 0;
        rep(j,n) if (p[j] == i) cur = j;
        if (cur != i) {
            for (int j = cur; j >= i; --j)
                if (p[j] >= cur) {
                    swap(p[cur], p[j]);
                    v.emplace_back(cur, j);
                    cur = j;
                }
        }
    }
    cout << ans << '\n';
    cout << v.size() << '\n';
    for (auto &[fst, snd] : v)
        cout << fst << ' ' << snd << '\n';
    return 0;
}