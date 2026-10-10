//
// Created by Psy.C on 2026/10/9.
//
/**
因为 y.x（y 除掉全部 p 的质因子后的部分）与 p 互质，所以它在模 p 下存在逆元，可用扩展欧几里得求出。除法：可逆部分乘逆元，质因子指数相减（若为负，最后 solve 时会用快速幂乘 s[i] 的幂补回来）
对每个质因子 s[i]，反复整除并累加指数；剩下的 y 就是互质部分
把 p 质因数分解存入 s[1..tot]（tot ≤ 9，因为 2e5 以内质因子数量有限）；然后用递推 c[i] = c[i-1] * get(i) 预处理好所有阶乘的 node 表示（c[i] 代表 i! 拆成互质部分+各质因子指数）
solve 把存好的 node 还原成真实模 p 数值（互质部分 × 各质因子幂）。C(x,y) 用阶乘 node 做两次除法得到组合数，再还原成模 p 值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;
struct node {
    ll x;//与 p 互质的部分
    int num[10]{};//各质因子 s[i] 的指数
    node() { memset(num, 0, sizeof(num)); x = 0; }
    void init() { x = 1; }
} c[N];

int p, tot;
node operator*(const node &x, const node &y) {
    node z; z.x = x.x*y.x%p;//互质部分相乘取模
    for (int i = 1; i <= tot; ++i) z.num[i] = x.num[i]+y.num[i];//指数相加
    return z;
}

void ex(int a, int b, ll& x, ll& y) {
    if (b == 0) { x = 1, y = 0; return; }
    ex(b, a%b, y, x);
    y -= a/b*x;
}
node operator/(const node &x, const node &y) {
    node z;
    ll r, t; ex(y.x, p, r, t);//求 y.x 在模 p 下的逆元 r
    z.x = (x.x*r%p+p)%p;//可逆部分相乘逆元
    for (int i = 1; i <= tot; ++i) z.num[i] = x.num[i]-y.num[i];//指数相减
    return z;
}

int s[15];
node get(int y) {
    node x;
    for (int i = 1; i <= tot; ++i)
        while (y%s[i] == 0) y /= s[i], x.num[i]++;//统计每个质因子指数
    x.x = y;//剩下的是与 p 互质的部分
    return x;
}

void init() {
    int now = p;
    for (int i = 2; i*i <= p; ++i)//质因数分解 p
        if (now%i == 0) {
            s[++tot] = i;
            while (now%i == 0) now /= i;
        }
    if (now > 1) s[++tot] = now;//剩余大质因子
    c[0].init();//c[0].x = 1, num 全 0（0! = 1）
    for (int i = 1; i <= N-5; ++i) c[i] = c[i-1]*get(i);
}

ll ksm(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y&1) ans=ans*x%p;
        x=x*x%p;
        y>>=1;
    }
    return ans;
}
ll solve(node x) {
    ll ans = x.x;
    for (int i = 1; i <= tot; ++i)
        ans = ans*ksm(s[i], x.num[i])%p;//把质因子幂乘回来
    return ans;//得到真实模 p 值
}
ll C(int x, int y) {
    if (x < y || x < 0 || y < 0) return 0;
    return solve((c[x]/c[x-y])/c[y]);
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, l, r;
int main() {
    fast;
    n = rd(), p = rd(), l = rd(), r = rd(); init();
    ll ans = 0;
    for (int i = l; i <= n; ++i) {
        int x = max(0, (i-r+1)/2)-1, y = (i-l)/2;
        ll num = C(n, i)*(C(i, y)-C(i, x)+p)%p;
        ans = (ans + num)%p;
    }
    cout << ans << '\n';
    return 0;
}