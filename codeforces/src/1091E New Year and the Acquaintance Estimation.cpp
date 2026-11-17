//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
copy(a+1..n, b+1)，并在 b[n+1]=x：把原序列放入 b，追加新度数 x，共 n+1 个元素。
sort(b+1..n+2, greater<>())：降序排序度序列。
s[i]=∑b：前缀和。
p=n+1：指针
b[p] < k 时 p 左移，找到前 p 个中 ≥k 的分界；
右侧 = k(k-1) + k·max(0,p-k) + Σ_{i=min...}（用前缀和 s[n+1]-s[max(k,p)]）；
若违反（s[k] > v）则不可图。
返回值的巧妙设计：

返回 x >= b[k] ? 1 : -1，用来区分"是新加的 x 太大导致失败（1）"还是"x 太小"（-1）——从而让二分单调化。
全部满足返回 0（可图）
p = (∑a) mod 2：现有度数之和的奇偶性。握手定理要求总度数和为偶数，所以新度数 x 必须与 p 同奇偶（x ≡ p (mod 2)）
把 x 参数化为 2*mid+p（保证奇偶性一致）。
mid 宏是 (l+r)>>1。
第一个二分：找满足 check(2*mid+p) ≥ 0 的最小 mid → L
第二个二分：找满足 check(2*mid+p) ≤ 0 的最大 mid → R。
L>R：无可行 x → 输出 -1。
否则把区间 [L,R] 内每个 i 映射回实际度数 2i+p 并全部输出（空格分隔）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
#define mid ((l+r)>>1)
using namespace std;

constexpr int N = 5e5+5;

int a[N], b[N], n;
ll s[N];
int check(int x) {
    copy(a+1,a+n+1, b+1), b[n+1] = x;
    sort(b+1,b+n+2, greater());
    rep(i,n+1) s[i] = s[i-1] + b[i];
    int p = n+1;
    rep(k,n+1) {
        while (p > 0 && b[p] < k) p--;
        ll v = 1ll*k*(k-1) + 1ll*k*(max(k,p)-k) + s[n+1] - s[max(k,p)];
        if (s[k] > v) return x >= b[k] ? 1 : -1;
    }
    return 0;
}

int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    int p = accumulate(a+1,a+n+1,0ll)&1;
    int L = 0, R = -1;
    for (int l = 0, r = (n-p)/2; l <= r; ) {
        if (check(2*mid+p) >= 0) L = mid, r = mid-1;
        else l = mid+1;
    }
    for (int l = 0, r = (n-p)/2; l <= r; ) {
        if (check(2*mid+p) <= 0) R = mid, l = mid+1;
        else r = mid-1;
    }
    if (L > R) cout << -1;
    else { for (int i = L; i <= R; i++) cout << 2*i+p << ' '; }
    return 0;
}