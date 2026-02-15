//
// Created by Psy.C on 2026/2/15.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define N 100010
#define low_bit(x) ((x)&(-x))
using namespace std;

int n, tmp[N], a[N], tt;
void lsh() {
    for (int i = 1; i <= n; ++i) tmp[i] = a[i];
    sort(tmp + 1, tmp + n + 1);
    tt = unique(tmp + 1, tmp + n + 1) - (tmp + 1);//去重后的元素个数
}

int ans[N];//以每个位置结尾的最长子序列长度
int mxx(const int a1, const int b) {
    return ans[a1] < ans[b] ? b : a1;//返回dp值更大的索引
}

int bit1[N];//维护前缀最大值
void update(int x, const int y) {
    for (; x <= tt; x += low_bit(x)) bit1[x] = mxx(bit1[x], y);
}
int query(int x) {
    int res = 0;
    for (; x; x -= low_bit(x)) res = mxx(bit1[x], res);
    return res;
}

int bit2[N];//维护后缀最大值（通过坐标映射实现）
void update2(int x, const int y) {
    for (; x <= tt; x += low_bit(x)) bit2[x] = mxx(bit2[x], y);
}
int query2(int x) {
    int res = 0;
    for (; x; x -= low_bit(x)) res = mxx(bit2[x], res);
    return res;
}

int d, to[N];//d为差值限制，to记录路径回溯
signed main() {
    fast;
    cin >> n >> d;
    for (int i = 1; i <= n; ++i) cin >> a[i]; lsh();
    for (int i = n; i >= 1; --i) {
        const int x = lower_bound(tmp + 1, tmp + tt + 1, a[i] + d) - tmp,
        y = upper_bound(tmp + 1, tmp + tt + 1, a[i] - d) - (tmp + 1);//a[j] <= a[i] - d
        const int res = mxx(query(y), query2(tt - x + 1));
        ans[i] = ans[res] + 1; to[i] = res;//更新当前位置的dp值和路径
        const int pos = lower_bound(tmp + 1, tmp + tt + 1, a[i]) - tmp;
        update(pos, i); update2(tt - pos + 1, i);
    }
    int s = 0;
    for (int i = 1; i <= n; ++i) s = mxx(s, i);
    cout << ans[s] << '\n';
    while (s) {
        cout << s << ' ';
        s = to[s];
    }
    cout << '\n';
    return 0;
}