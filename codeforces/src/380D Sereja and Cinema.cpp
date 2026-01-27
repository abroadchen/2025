//
// Created by Psy.C on 2026/1/26.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100007
#define mod 1000000007
using namespace std;

template<class T, class S>//将b加到a上
void add(T& a, S b) { a += b; if (a >= mod) a -= mod; }

int pw(int a, int b) {
    int ans = 1;
    while (b) {
        if (b&1) ans = static_cast<int>(1ll * ans * a % mod);
        a = static_cast<int>(1ll * a * a % mod);
        b >>= 1;
    }
    return ans;
}

int inv[N], F_inv[N], F[N];
void init() {
    inv[1] = F[0] = F_inv[0] = 1;
    //递推计算逆元
    for (int i = 2; i < N; ++i) inv[i] = static_cast<int>(1ll * (mod - mod / i) * inv[mod % i] % mod);
    //计算阶乘
    for (int i = 1; i < N; ++i) F[i] = static_cast<int>(1ll * F[i-1] * i % mod);
    //计算阶乘的逆元
    for (int i = 1; i < N; ++i) F_inv[i] = static_cast<int>(1ll * F_inv[i-1] * inv[i] % mod);
}

int cb(const int n, const int m) {
    if (n < m || n < 0) return 0;
    return static_cast<int>(1ll * F[n] * F_inv[m] % mod * F_inv[n - m] % mod);
}

int pre[N], a[N];//前缀和数组 输入数组
int dfs(const int l, const int r) {//区间[l,r]的方案数
    if (pre[l-1] == pre[r]) return pw(2, r - l);//区间内全是0，返回2^(r-l)
    int p, q;//左右边界指针
    for (p = l; p <= r; ++p) if (a[p] != 0) break;//左边第一个非0元素
    for (q = r; q >= l; --q) if (a[q] != 0) break;//右边第一个非0元素
    if (p == q && a[p] == 1) return cb(r - l, p - l);//只有一个1，返回组合数
    int ans = 0;
    if (a[p] >= a[q]) {//左边元素大于等于右边
        if (const int l2 = p, r2 = l2 + a[p] - 1; r2 >= q && r2 <= r)//是否能形成有效区间
            add(ans, 1ll * dfs(l2+1, r2)*cb(r-l-r2+l2, l2-l)%mod);
    }
    if (a[q] >= a[p]) {
        if (const int r2 = q, l2 = r2 - a[q] + 1; l2 >= l && l2 <= p)
            add(ans, 1ll * dfs(l2, r2-1)*cb(r-l-r2+l2, l2-l)%mod);
    }
    return ans;
}

int main() {
    fast;
    init();
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) pre[i] = pre[i-1] + (a[i] != 0);
    cout << dfs(1, n) << '\n';
    return 0;
}