//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
change(id)：把 id 对应叶节点 +1 并回溯更新（计数数组中的已出现值）。
ask(L,R)：区间求和（统计已经出现过且值的 val 落在 [L,R] 的个数，用于逆序对）
cnt*(cnt-1)/4 mod：这正是"cnt 个不同随机数两两之间，前者大于后者的概率 = 1/2"，所以内部逆序对数期望 = C(cnt,2)·(1/2) = cnt(cnt-1)/4。除以 4 因为在模意义：cnt(cnt-1) 和整体除以 4（即乘 inv(4)）
位置在 a[i] 之前的未知数个数 = cc。
位置在 a[i] 之后的未知数个数 = cnt-cc。
某个已知值 a[i] 与一个随机未知数（取值剩余未用值的均匀随机）比较，a[i] > 未知数 的概率以及未知数 > a[i] 的概率不是简单 1/2，而是依赖当前树里"已出现值"的计数（这里用 ask(1,a[i]-1) 表示已出现且值 < a[i] 的个数，ask(a[i]+1,n) 表示已出现且值 > a[i] 的个数），再乘以对应权限的未知概率 1/cnt。
这就是"已知-未知"逆序对的期望增量
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
#define mid ((l+r)>>1)
#define int long long
using namespace std;

constexpr int N = 2e5+5, M = 8e5+5, mod = 998244353;

int sum[M];
void build(int l, int r, int x) {
    sum[x] = r-l+1 - sum[x];
    if (l == r) return;
    build(l,mid,x<<1); build(mid+1,r,x<<1|1);
}
void change(int id, int l, int r, int x) {
    if (l == r) { sum[x]++; return; }
    if (id <= mid) change(id,l,mid,x<<1);
    else change(id,mid+1,r,x<<1|1);
    sum[x] = sum[x<<1] + sum[x<<1|1];
}
int ask(int L, int R, int l, int r, int x) {
    if (L <= l && r <= R) return sum[x];
    int ret = 0;
    if (L <= mid) ret += ask(L,R,l,mid,x<<1);
    if (R > mid) ret += ask(L,R,mid+1,r,x<<1|1);
    return ret;
}

int ksm(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) { res *= a; res %= mod; }
        a *= a; a %= mod;
        b >>= 1;
    }
    return res;
}

int a[N];
signed main() {
    fast;
    int n; cin >> n;
    int cnt = 0;
    rep(i,n) {
        cin >> a[i];
        if (a[i] == -1) cnt++;
    }
    int ans = cnt*(cnt-1)%mod*ksm(4,mod-2)%mod;
    rep(i,n) {
        if (a[i] == -1) continue;
        if (a[i] != n) ans += ask(a[i]+1,n,1,n,1);//统计前面比 a[i] 大的已知值的个数
        change(a[i],1,n,1);// 把 a[i] 标记为已出现
    }
    build(1,n,1);//重置线段树
    int cc = 0, nc = ksm(cnt,mod-2);//nc=1/cnt
    rep(i,n) {
        if (a[i] == -1) { cc++; continue; }//cc=当前已遇到的未知数个数（在其前的未知数）
        if (a[i] != n) {
            ans += ask(a[i]+1,n,1,n,1)*cc%mod*nc%mod;
            ans %= mod;
        }
        if (a[i] != 1) {
            ans += ask(1,a[i]-1,1,n,1)*(cnt-cc)%mod*nc%mod;
            ans %= mod;
        }
    }
    cout << ans;
    return 0;
}