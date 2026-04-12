//
// Created by Psy.C on 2026/4/12.
//
/**
chkbit(ar,i): 检查第i位是否为1（位压缩优化）
(i)>>6: i/64，定位到数组的哪个元素
((i)>>1)&31: (i/2)%32，定位到该元素的哪一位
setbit(ar,i): 将第i位设为1
isprime(x): 判断x是否为质数的函数

N = 100: 小于某个阈值的质数个数上限
M = 1e5+5: 数组大小阈值
P = 6e5+5: 质数数组大小
K = 1e7+5: 筛法的最大范围
dp[N][M]: 动态规划表，用于计算phi函数
ar[(K>>6)+5]: 位压缩的筛法数组，每个unsigned int存储32个数的质数信息
len: 质数个数计数器
pri[P]: 存储质数的数组
cnt[K]: cnt[i]表示≤i的质数个数

计算n以内满足特定条件的数的个数（可能是半质数或其他）
第一个循环处理pq形式的数（p<q）
第二个循环处理p³形式的数

 */
#include <bits/stdc++.h>
#define ll long long
#define chkbit(ar,i) (((ar[(i)>>6])&(1<<(((i)>>1)&31))))
#define setbit(ar,i) (((ar[(i)>>6])|=(1<<(((i)>>1)&31))))
#define isprime(x) (((x)&&((x)&1)&&(!chkbit(ar,(x))))||((x)==2))
using namespace std;
constexpr int N = 100, M = 1e5+5, P = 6e5+5, K = 1e7+5;

namespace pcf {
    ll dp[N][M];
    unsigned int ar[(K>>6)+5] = {};
    int len = 0, pri[P], cnt[K];

    void Sieve() {
        setbit(ar,0), setbit(ar, 1);//0和1不是质数
        for (int i = 3; i*i < K; i++, i++) {//从3开始，只检查奇数
            if (!chkbit(ar, i)) {//如果i是质数
                int k = i<<1;//k = 2*i，即偶数步长
                for (int j = i*i; j < K; j+=k) setbit(ar, j);//标记i的奇数倍数
            }
        }
        for (int i = 1; i < K; i++) {
            cnt[i] = cnt[i-1];//累计计数
            if (isprime(i))
                pri[len++] = i, cnt[i]++;//存储质数并更新计数
        }
    }
    void init() {
        Sieve();
        for (int n = 0; n < N; n++)
            for (int m = 0; m < M; m++) {
                if (!n) dp[n][m] = m;//没有质数时，phi(m,0)=m
                else dp[n][m] = dp[n-1][m] - dp[n-1][m/pri[n-1]];
            }
    }
    ll phi(ll m, int n) {
        if (n == 0) return m;
        if (pri[n-1] >= m) return 1;//如果最大的质数≥m，结果为1
        if (m < M && n < N) return dp[n][m];//使用预计算值
        return phi(m, n-1) - phi(m/pri[n-1], n - 1);//递归计算
    }
    ll Lehmer(ll m) {
        if (m < K) return cnt[m];//小于阈值直接返回预计算结果
        ll res = 0;
        int a, s, y;
        s = sqrt(0.9 + m), y = cbrt(0.9 + m);//计算平方根和立方根
        a = cnt[y], res = phi(m, a) + a - 1;//计算主要部分
        for (int i = a; pri[i] <= s; i++)//计算剩余部分
            res = res - Lehmer(m/pri[i]) + Lehmer(pri[i]) - 1;
        return res;
    }
}

ll get(ll n) {
    ll res = 0;
    for (int i = 0; i < pcf::len; i++) {
        ll x = pcf::pri[i], y = n/x;
        if (x*x > n) break;
        res += pcf::Lehmer(y) - pcf::Lehmer(x);
    }
    for (int i = 0; i < pcf::len; i++) {
        ll x = pcf::pri[i];
        if (x*x*x > n) break;
        res++;
    }
    return res;
}

ll n;
int main() {
    cin >> n; pcf::init();
    cout << get(n) << '\n';
    return 0;
}