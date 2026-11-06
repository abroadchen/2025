//
// Created by Psy.C on 2026/11/6.
//

/**
真正学会的起点..
埃氏/线性筛，np[x]=1 表示 x 不是质数，pr 存素数，cnt 计数。
之后 srand(time(0)) 为随机化做准备
读 n 个数存入 a，d = 所有数的全局 gcd。
若 d != 1：所有数有公共因子 >1，无法拆成互质子集 → 输出 -1。
排序后若 最小数是 1：因为 1 与任何数互质，一个集合即可覆盖 → 答案是 1
对 a 去重：若 v[a[i]] 未被标过，则保留进 b，并把它的所有倍数标记（v[j]=1）。
含义：如果 x 是 a[i] 的倍数，那么 a[i] 已经"代替"了 x（因为任何与 a[i] 互质的设计对 x 也成立，从而 x 可以删除）。
这样大大压缩集合规模 n→m。然后清空 v
初始 m（去重后的数个数），ans=2（答案至少 2？需结合题意——若所有数都能互质配对，最小也是 2 之类）。
每轮：随机打乱 a、b，然后对每对 (a[i], b[j])：
若 gcd == 1 → 已出现互质对，输出当前 ans 结束。（互质对出现说明已达可行层数）
否则把产生的 gcd t 记入 c（去重），这些 gcd 会成为下一轮的集合。
下一轮：b = c（即新集合 = 上一轮所有 gcd 集合），m=新大小，ans++。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 3e5+5;

inline int gcd(int x, int y) { return y ? gcd(y, x%y) : x; }

int np[N], pr[N],cnt;
inline void sieve() {
    for (int i = 2; i <= N-5; ++i) {
        if (!np[i]) pr[++cnt] = i;
        for (int j = 1, k = pr[j]; j <= cnt && i*k <= N-5; k = pr[++j]) {
            np[i*k] = 1;
            if (!(i%k)) break;
        }
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int a[N], b[N], c[N], v[N];
int main() {
    fast;
    sieve(); srand(time(0));
    int n = rd(), d = rd(), m = 0, ans = 2, l = 0; a[1] = d;
    for (int i = 2; i <= n; ++i) a[i] = rd(), d = gcd(d, a[i]);
    if (d != 1) return cout << "-1\n", 0;
    sort(a+1, a+n+1);
    if (a[1] == 1) return cout << "1\n", 0;
    rep(i,n) if (!v[a[i]]) {
        b[++m] = a[i];
        for (int j = a[i]; j <= N-5; j += a[i]) v[j] = 1;
    }
    n = m;
    rep(i,n) a[i] = b[i];
    memset(v, 0, sizeof(v));
    while (1) {
        random_shuffle(a+1, a+n+1);
        random_shuffle(b+1, b+m+1);
        rep(i,n) rep(j,m) if (a[i] != b[j]) {
            int t = gcd(a[i], b[j]);
            if (t == 1) return cout << ans << '\n', 0;
            if (!v[t]) v[t] = 1, c[++l] = t;
        }
        rep(i,l) v[b[i]=c[i]] = 0;
        m = l, l = 0, ++ans;
    }
    return 0;
}