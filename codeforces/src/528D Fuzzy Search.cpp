//
// Created by Psy.C on 2026/3/3.
//
/**
N = 1<<19 = 524288: FFT数组大小（2的幂次）
mod = 998244353: 模数，是一个NTT友好质数
G = 3: 模mod的原根
invG = 332748118: G的模逆元
rev[N]: 位逆序置换数组
计算位逆序置换数组
b = log2(x): 计算二进制位数
(rev[i>>1]>>1): 右移一位
((i&1)<<(b-1)): 最低位移到最高位
实现二进制位翻转

快速数论变换，类似FFT但在模意义下
第一层循环：位逆序置换
第二层循环：按长度分组进行蝴蝶变换
y: 当前长度下的单位根
蝴蝶变换公式：a[i+j] = a0+a1, a[i+j+x] = a0-a1
逆数论变换
调用NTT，参数为-1（使用原根的逆元）
乘以n的模逆元完成归一化

n, m: 两个字符串的长度
k: 扩展距离
f[N], g[N]: FFT变换用数组
tmp[N]: 临时数组
s, t: 输入的两个字符串

预处理字符c在字符串中的匹配情况
f[i] = s[i] == c: 标记s中字符c的位置
g[i] = t[i] == c: 标记t中字符c的位置
两次扫描扩展f数组：将字符c前后k范围内的位置都设为1
f[i] = 1 - f[i]: 取反，原来为0的变1，原来为1的变0
reverse(g, g + m): 翻转g数组用于卷积
对字符c执行卷积操作
清空数组
调用pre处理字符c
对f和g进行NTT变换
逐项相乘（频域相乘相当于时域卷积）
逆NTT变换回到时域
更新结果数组h

计算FFT所需长度（2的幂次）
初始化位逆序数组
对每个DNA字符(A,G,C,T)执行卷积操作
统计h数组中为0的位置个数（即完全匹配的起始位置）
输出结果

时间复杂度为O(|S|log|S|)，远优于朴素算法的O(|S||T|)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1<<19, mod = 998244353, G = 3, invG = 332748118;
int rev[N];
void init(const int x) {
    const int b = log2(x);
    for (int i = 0; i < x; ++i)
        rev[i] = (rev[i>>1]>>1) + ((i&1)<<(b-1));
}
int ksm(int a, int b) {
    int res = 1;
    for (; b; a = 1ll*a*a%mod, b>>=1)
        if (b&1) res = 1ll*res*a%mod;
    return res;
}

void ntt(int *a, const int n, const int t=1) {
    for (int i = 0; i < n; ++i)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int x = 1; x <= n>>1; x<<=1) {
        const int y = ksm(t == 1 ? G : invG, (mod-1)/(x<<1));
        for (int i = 0; i < n; i += x<<1) {
            int k = 1;
            for (int j = 0; j < x; j++, k = 1ll*k*y%mod) {
                const int a0 = a[i+j], a1 = 1ll*k*a[i+j+x]%mod;
                a[i+j] = (a0+a1)%mod;
                a[i+j+x] = (a0-a1+mod)%mod;
            }
        }
    }
}
void i_ntt(int *a, const int n) {
    ntt(a, n, -1);
    const int inv = ksm(n, mod-2);
    for (int i = 0; i < n; ++i)
        a[i] = 1ll*a[i]*inv%mod;
}

int n, m, f[N], g[N], k, tmp[N];
string s, t;
void pre(const char c) {
    for (int i = 0; i < n; ++i) f[i] = s[i] == c;
    for (int i = 0; i < m; ++i) g[i] = t[i] == c;
    for (int i = 0, cnt = 0; i < n; i++, cnt--) {
        if (f[i]) cnt = k+1;
        if (cnt > 0) tmp[i] = 1;
    }
    for (int i = n-1, cnt = 0; i >= 0; i--, cnt--) {
        if (f[i]) cnt = k+1;
        if (cnt > 0) tmp[i] = 1;
    }
    for (int i = 0; i < n; ++i) f[i] |= tmp[i];
    for (int i = 0; i < n; ++i) f[i] = 1 - f[i];
    reverse(g, g + m);
}

int len = 1, h[N];
void get(const char c) {
    fill_n(f, len, 0); fill_n(g, len, 0);
    fill_n(tmp, len, 0);
    pre(c);
    ntt(f, len), ntt(g, len);
    for (int i = 0; i < len; ++i) f[i] = 1ll*f[i]*g[i]%mod;
    i_ntt(f, len);
    for (int i = 0; i < n-m+1; ++i) h[i] |= f[i+m-1];
}


int main() {
    fast;
    cin >> n >> m >> k >> s >> t;
    while (len <= n + m) len <<= 1;
    init(len);
    get('A'), get('G'), get('C'), get('T');
    int cnt = 0;
    for (int i = 0; i < n-m+1; ++i)
        if (h[i] == 0) cnt++;
    cout << cnt;
    return 0;
}