//
// Created by Psy.C on 2025/11/11.
//

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;
const int N = 510, mod = (int)1e8;

int len(0);//用于记录最小长度

struct hi {
    int n, a[N];// n表示当前数字占用的位数，a[]存储各位数字
    hi() { memset(a, 0, sizeof(a)); n = 1; }
    hi(int x) {// 带参数构造函数，将整数x转换为高精度数
        memset(a, 0, sizeof(a)); n = 0;
        do {
            a[++n] = x % mod, x /= mod;// 将x按mod进制分解存储
        } while (x);
    }
    void init(int x) {
        memset(a, 0, sizeof(a)); n = 0;
        do {
            a[++n] = x % mod, x /= mod;
        } while (x);
    }
    void cut() {// 调整有效位数，去除前导零
        len = min(len, n);
        while (n > 1 && !a[n]) --n;// 当高位为0且不是最后一位时，减少位数
    }
    int cmp(hi p) {// 比较两个高精度数的大小
        if (n > p.n) return 1;// 当前数位数更多，返回1
        if (n < p.n) return -1;
        for (int i = n; i >= 1; --i) {// 从高位开始逐位比较
            if (a[i] > p.a[i]) return 1;
            else if (a[i] < p.a[i]) return -1;
        }
        return 0;// 相等返回0
    }
    void add(int d) {// 加上一个小整数d
        int g = d; ++n;// g为进位值，先增加一位防止溢出
        for (int i = 1; i <= n; ++i) {
            if (!g) break;// 如果没有进位就退出
            g += a[i], a[i] = g % mod, g /= mod;// 执行加法和进位操作
        }
        cut();// 调整位数
    }
    void mul(int d) {// 乘以一个小整数d
        ll g = 0; n += 2;//预留两位
        for (int i = 1; i <= n; ++i) {
            g = (ll)a[i] * d + g, a[i] = g % mod, g /= mod;
        }
        cut();
    }
    void div(int d) {
        int g = 0;// g为余数
        for (int i = n; i >= 1; --i) {// 从高位开始做除法
            g = g * mod + a[i], a[i] = g / d, g %= d;
        }
        cut();
    }
    hi operator+(hi p) {
        hi ret; ret.init(0);
        int g = 0; ret.n = max(n, p.n) + 1; // 计算最大位数并加1
        for (int i = 1; i <= ret.n; ++i) {
            g += a[i] + p.a[i], ret.a[i] = g % mod, g /= mod;// 逐位相加
        }
        ret.cut();
        return ret;
    }
    hi operator-(hi p) {
        hi ret; ret.init(0);
        int g = 0; ret.n = n;// 结果位数等于被减数位数
        for (int i = 1; i <= ret.n; ++i) {
            ret.a[i] = g + a[i] - p.a[i];
            if (ret.a[i] < 0) g = -1, ret.a[i] += mod;// 处理借位
            else g = 0;
        }
        ret.cut();
        return ret;
    }
    hi operator/(hi p) {
        hi d, R, tmp; d.init(0), R.init(0);
        d.n = n;
        for (int i = n; i >= 1; --i) {
            R.mul(mod);// 将余数左移一位
            R.add(a[i]);// 加上当前位
            int l = 0, r = mod - 1;
            while (l <= r) {// 二分查找商的这一位
                int m = (l + r) / 2;
                hi t = p;
                t.mul(m);
                int c = R.cmp(t);
                if (!c) { d.a[i] = m; break; }// 找到精确值
                if (c > 0) d.a[i] = m, l = m + 1;// 商偏小，增大
                else r = m - 1;
            }
            hi t = p;
            t.mul(d.a[i]);
            R = R - t;// 更新余数
        }
        d.cut();
        return d;
    }
    void print() {
        printf("%d", a[n]);
        for (int i = n - 1; i >= 1; --i) printf("%08d", a[i]);
    }
};

hi gcd(hi a, hi b) {
    int t(0);
    while (b.n > 1 || b.a[1]) {// 当b不为0时继续
        while (!(a.a[1] & 1) && !(b.a[1] & 1))// 当a和b都是偶数时
            a.div(2), b.div(2), ++t;// 同时除以2，并计数
        while (!(a.a[1] & 1)) a.div(2);
        while (!(b.a[1] & 1)) b.div(2);
        if (a.cmp(b) > 0) swap(a, b);// 确保a≤b
        b = b - a;// 执行减法
    }
    while (t) a.mul(2);// 将之前提取的因子2乘回去
    return a;
}

int n, m, t, c;
hi a, b;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (t = 0; !(n&1); n /= 2) ++t;// 统计n中因子2的个数
    if (n == 1) { printf("%d/1", t); return 0; }// 如果n是2的幂，则直接输出
    c = 0, m = 1, a.init(0), b.init(1);
    do {
        ++c, m <<= 1;// c递增，m乘以2
        a.mul(2);
        b.mul(2);
        if (m > n) { m -= n; a.add(c); }
    } while (m > 1);

    a.mul(n);
    a.add(c);
    b = b - *(new hi(1));// b减去1
    hi cc = b;
    cc.mul(t);
    a = a + cc;

    cc = gcd(a, b);
    a = a / cc; b = b / cc;
    a.print();
    printf("/");
    b.print();
    printf("\n");
    return 0;
}