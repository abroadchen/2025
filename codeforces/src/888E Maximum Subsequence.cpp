//
// Created by Psy.C on 2026/10/8.
//
/**
读 n 个数，每个先对 mod 取模
把前一半
m
=
⌊
n
/
2
⌋
m=⌊n/2⌋ 个数的
2
m
2
m
  个子集和全部算出来放进数组 b，并排序
枚举后半每个子集和 t。
find(mod-t-1)：在后半排序好的 b 中，二分找不大于 mod-t-1 的最大元素 x（find 内部就是标准的上界二分，返回 <=x 的最大 b[mid]）。
这样 (x+t) % mod 尽量接近 mod 而不越界，得到尽可能大的模值；更新 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 40, M = 1e6+10;

int cnt, b[M];
int find(int x) {
    int l = 1, r = cnt, t = 0;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (b[mid] <= x) {
            l = mid+1; t = mid;
        } else r = mid-1;
    }
    return b[t];
}

int a[N];
int main() {
    fast;
    int n, mod; cin >> n >> mod;
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; a[i] %= mod;
    }
    int m = n/2;
    for (int i = 0; i < 1<<m; ++i) {
        int t = 0;
        for (int j = 0; j < m; ++j)
            if (i&(1<<j)) t = (t + a[j]) % mod;
        cnt++;
        b[cnt] = t;
    }
    sort(b+1, b+cnt+1);
    m = n-n/2;
    int ans = 0;
    for (int i = 0; i < 1<<m; ++i) {
        int t = 0;
        for (int j = 0; j < m; ++j)
            if (i&(1<<j)) {
                int k = j + n/2;//映射回原数组下标
                t = (t + a[k]) % mod;
            }
        int x = find(mod - t - 1);//找前半中 <= mod-t-1 的最大值
        ans = max(ans, (x+t)%mod);
    }
    cout << ans << '\n';
    return 0;
}