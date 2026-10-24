//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
用一万进制（bit=1000，每格存 0-999）存大数。len 为有效位数，a[1..len] 存每一位。
N 是 FFT 长度上限（2^21，约 200 万）
清空：长度归零，数组全 0
先比位数（位数多必大），再逐位从高位往下比，全部相同则相等（返回 1）
把每个单元 a[i] 超出 1000 的部分向高位进位，并扩充 len
每一位乘以小整数 x，然后统一进位。用于乘以 3
复数结构：实部 r、虚部 i；重载加减乘（复数乘法公式）。用于 FFT 蝶形运算
迭代式 FFT（非递归）。
第一层：位反转交换（R[i] 是 i 的反转位数）。
三层循环：蝶形运算，标准 Cooley–Tukey 迭代实现
这是大数乘法核心，用 FFT 把卷积转成点乘 O(n log n)。
把两个大数的每一位当作多项式系数，FFT 相乘后再逆变换取整，得到乘积的十进制（万进制）各位
快速幂计算 x = 3^y。递归：先算 3^(y/2)，平方，奇数再乘 3。用 FFT 乘法 get 完成大数平方
把 x 乘以系数 y（小倍数），与目标 n 比较，判断是否已达标
读入十进制数 s，按每 3 位一组转换到万进制存储（pw 分别对应个位/十位/百位权重）
用对数估计 m：n.len*log10(3)?  实际是 n.len * (log10 / log3) 估计 10 进制位数对应的 3 的指数，减 3 保险。
修正 n 的 len 到万进制真正的长度
若 n 就是 1，输出 1 结束
不断增大 3 的指数，对每个指数测试倍数 x*2, x*3, x*4 是否 ≥ n。
一旦满足就输出 m*3 + i 并结束
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i=1; i<=n; i++)
#define per(i,n) for (int i=n; i>=1; i--)
#define pi acos(-1.)
#define ll long long
#define db double
using namespace std;

constexpr int N = (1<<21)+1;

int bit = 1e3;
struct Big {
    int len; ll a[N];
    void clear() { len = 0; memset(a,0,sizeof(a)); }
    bool operator>=(Big & o) const {
        if (len != o.len) return len > o.len;
        per(i,len) if (a[i] != o.a[i]) return a[i] > o.a[i];
        return 1;
    }
    void push() {
        rep(i,len) a[i+1] += a[i]/bit, a[i]%=bit;
        while (a[len+1]) {
            len++;
            a[len+1] = a[len]/bit;
            a[len]%=bit;
        }
    }
    void operator*=(int x) {
        rep(i,len) a[i] *= x;
        push();
    }
} n, x, tmp;

struct C {
    db r, i;
    C(){}
    C(db _r, db _i) : r(_r), i(_i){}
    C operator+(C x) const { return {r+x.r, i+x.i}; }
    C operator-(C x) const { return {r-x.r, i-x.i}; }
    C operator*(C x) const { return {r*x.r-i*x.i, r*x.i+i*x.r}; }
} A[N], B[N], w[N];

int R[N];
void fft(C a[], int n) {
    for (int i = 0; i < n; i++) if (R[i] > i) swap(a[i], a[R[i]]);
    for (int t = n>>1, d=1; d < n; d <<= 1, t >>= 1)
        for (int i = 0; i < n; i += d<<1)
            for (int j = 0; j < d; j++) {
                C tmp = w[t*j]*a[i+j+d];
                a[i+j+d] = a[i+j] - tmp;
                a[i+j] = a[i+j] + tmp;
            }
}

void get(Big &a, Big &b, Big &c) {
    int n, d;
    for (n = 1, d = 0; n < a.len+b.len; n <<= 1, d++) {}//找 2 的幂长度
    for (int i = 0; i < n; i++) {
        R[i] = (R[i>>1]>>1)|((i&1)<<(d-1));//位反转表
        w[i] = C(cos(pi*2*i/n), sin(pi*2*i/n));//单位根
        A[i] = B[i] = C(0, 0);
    }
    rep(i,a.len) A[i-1].r = a.a[i];//装入多项式 a
    rep(i,b.len) B[i-1].r = b.a[i];//装入多项式 b
    fft(A, n), fft(B, n);//正变换
    for (int i = 0; i < n; i++) A[i] = A[i]*B[i], w[i].i *= -1.0;// 频域相乘 + 取共轭
    fft(A, n); c.clear();//逆变换
    for (int i = 0; i < n; i++) c.a[i+1] = 1ll*(A[i].r/n+0.5);//除以 n 取整
    c.len = n;
    while (c.a[c.len] == 0 && c.len > 1) c.len--;//去前导0
    c.push();//进位整理
}

void ksm(int y) {
    if (y == 0) {
        x.clear(); x.a[x.len=1] = 1;
        return;
    }
    ksm(y/2);
    get(x, x, x);
    if (y&1) x *= 3;
}
bool check(Big &x, int y) {
    tmp = x; tmp *= y;
    return tmp >= n;
}

char s[N];
int pw[3] = {1, 10, 100}, m;
int main() {
    scanf("%s", s+1); n.len = strlen(s+1);
    rep(i,n.len) n.a[(n.len-i+1-1)/3+1] += pw[(n.len-i)%3]*(s[i]-'0');
    m = max(0, (int)(n.len*log(10)/log(3))-3);//估计 3^m ≈ n 的数量级
    n.len = (n.len-1)/3 + 1;//实际万进制位数
    if (n.len == 1 && n.a[1] == 1) { puts("1"); return 0; }
    ksm(m);
    while (1) {
        for (int i = 2; i <= 4; i++) if (check(x, i)) {
            printf("%d", m*3+i);
            return 0;
        }
        x *= 3;
        m++;
    }
    return 0;
}