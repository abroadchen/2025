//
// Created by Psy.C on 2026/4/7.
//
///O(n × 字母表大小 × 2 × m)，其中字母表大小为26（因为使用了'a'-'a'转换）
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
///位置、前一个字母、标志位
int f[10][10][2], m;
string a[40], b[40];
int dfs(int pos, int pre, int flag) {
    if (!pos) return flag;//没有剩余位置需要填充
    if (f[pos][pre][flag] != -1) return f[pos][pre][flag];
    int res = 0;
    for (int i = 0; i < m; ++i)
        //剩余需求减1 当前选择字符串a[i]的第一个字母转换为数字 之前状态有效且当前字符串b[i]首字母等于前一个字母
        res += dfs(pos - 1, a[i][0] - 'a', flag&&b[i][0]-'a'==pre);
    f[pos][pre][flag] = res;
    return res;
}

int n;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) cin >> a[i] >> b[i];
    memset(f, -1, sizeof f);
    cout << dfs(n-1, 0, 1) << '\n';
    return 0;
}