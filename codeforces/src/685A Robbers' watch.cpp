//
// Created by Psy.C on 2026/4/15.
//
/**
vis[10]：用于记录数字出现情况的数组
xx, yy：记录两个数字在7进制下的位数
将vis数组清零，用于统计0-6各数字的出现次数
处理x：获取x在7进制表示下的每一位数字，并在vis数组中标记
通过 a%7 获取最低位，a/=7 去掉最低位
处理y：类似地处理y在7进制表示下的每一位数字
检查重复：如果任何数字(0-6)出现了2次或以上，返回false；否则返回true

保存n和m的原始值到nn和mm中，然后将n和m都减1
计算n和m在7进制表示下的位数，分别存储在xx和yy中
最小化处理：确保xx和yy至少为1
遍历所有可能的坐标对(i,j)，其中i从0到nn-1，j从0到mm-1
对每一对坐标，检查它们在7进制表示下是否有相同的数字
如果没有重复数字，则计数器ans加1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int vis[10], xx, yy;
bool check(int x, int y) {
    int a = x, b = y;
    for (int i = 0; i <= 6; ++i) vis[i] = 0;
    for (int i = 1; i <= xx; ++i) {
        vis[a%7]++;
        a/=7;
    }
    for (int i = 1; i <= yy; ++i) {
        vis[b%7]++;
        b/=7;
    }
    for (int i = 0; i <= 6; ++i)
        if (vis[i] >= 2) return false;
    return true;
}

int n, m;
signed main() {
    fast;
    cin >> n >> m;
    if (n*m > 6543210) {
        cout << 0 << '\n';
        return 0;
    }
    int nn = n, mm = m; n--, m--;
    while (n) { xx++; n/=7; }
    while (m) { yy++; m/=7; }
    xx = max(xx, 1ll), yy = max(yy, 1ll);
    int ans = 0;
    for (int i = 0; i < nn; ++i)
        for (int j = 0; j < mm; ++j)
            if (check(i, j)) ans++;
    cout << ans << '\n';
    return 0;
}