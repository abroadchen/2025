//
// Created by Psy.C on 2026/2/26.
//
/**
n：区间数量
l[N], r[N]：每个区间的左右边界
len[N]：每个区间的长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1201;
int fa[N];
inline int find(const int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int n, l[N], r[N], len[N];
char s[N];//结果字符串数组
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> l[i] >> r[i];
    for (int i = 1; i <= n+4; ++i) fa[i] = i;
    //最后一个区间的左边界必须≤1
    if (l[n] > 1) return cout << "IMPOSSIBLE\n", 0;
    len[n] = 2;//最后一个区间的长度为2
    for (int i = n-1; i >= 1; --i) {
        int t = 1;//累计长度
        if (l[i] == 1) { len[i] = 2; continue; }
        for (int j = find(i+1); j <= n; j = find(j)) {
            t += len[j];//累加后面区间的长度
            fa[j] = j+1;//在并查集中合并区间
            if (l[i] <= t && t <= r[i]) {
                len[i] = t + 1;//确定当前区间长度
                break;
            }
        }
        if (!len[i]) return cout << "IMPOSSIBLE\n", 0;//无法确定长度
    }
    int x = 1;
    for (int i = 1; i <= n; ++i) {
        while (s[x]) ++x;//找到第一个空位置
        s[x] = '(', s[x+len[i]-1] = ')';
    }
    cout << s + 1 << '\n';//跳过s[0]
    return 0;
}