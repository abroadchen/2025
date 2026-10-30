//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
mx：记录读入元素的最大值（用于限定后面的扫描范围）。
t[N]：计数数组，t[x] 表示数值 x 出现的次数（桶计数）。
n：目标参数
check(x)：判断"以 x 为每份大小，能凑出至少 n 个分组"是否可行。
遍历 i = 1..mx，对每个数值 i，把它的出现次数 t[i] 按每份 x 个来分，能分出 t[i] / x 份（整数除法）。
累加得到总共能分出的份数 l。
如果 l >= n 返回 true（可行），否则 false
读入 n 和 k。
循环读入 k 个数 a[i]：
t[a[i]]++：计数。
mx = max(mx, a[i])：记录最大值。
ans = max(ans, t[a[i]])：ans 始终记录当前读入过程中出现次数最多的那个值的出现次数（即所有颜色里出现次数的最大值）。
循环结束后 ans 就是全局最大出现次数，作为二分上界
在 [1, ans] 区间上二分查找最大可行解：
mid = (l+r)/2。
若 check(mid) 为真（mid 可行），说明可以尝试更大的值，记录 ret = mid，l = mid + 1。
否则 r = mid - 1。
循环结束后 ret 存的是最大的可行 x，输出 ret
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e5+5;

int mx, t[N], n;
bool check(int x) {
    int l = 0;
    rep(i,mx) l += t[i]/x;
    if (l < n) return false;
    return true;
}

int k, a[N], ans, ret;
int main() {
    fast;
    cin >> n >> k;
    rep(i,k) {
        cin >> a[i]; t[a[i]]++;
        mx = max(mx, a[i]);
        ans = max(ans, t[a[i]]);
    }
    int l = 1, r = ans;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (check(mid)) { ret = mid; l = mid + 1; }
        else r = mid - 1;
    }
    cout << ret << '\n';
    return 0;
}