//
// Created by Psy.C on 2025/9/21.
//

#include <bitset>
#include <cstdio>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;
typedef long long ll;
const int N = 1010;

int n, m, k;// 点数、圆数、查询数
int kx[N], ky[N];// 存储点的坐标
bitset<N> f[N];// 位集数组，f[i]表示第i个点在哪些圆内

inline int read() {
    int x = 0, c = getchar(), f = 0;
    for (; c > '9' || c < '0'; f = c == '-', c = getchar());
    for (; c >= '0' && c <= '9'; x = (x << 1) + (x << 3) + c - '0', c = getchar());
    return f ? -x : x;
}

inline void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) write(x / 10);// 递归输出高位
    putchar(x % 10 + '0');// 输出当前位
}


int main() {

    n = read(), m = read(), k = read();
    rep (i, 1, n) kx[i] = read(), ky[i] = read();

    rep (i, 1, m) {
        ll r = read(); r *= r;// 读取半径并计算半径平方
        int cx = read(), cy = read();// 读取圆心坐标
        rep (j, 1, n)// 判断点到圆心距离的平方是否小于半径平方
            if ((ll)(kx[j] - cx) * (kx[j] - cx) + (ll)(ky[j] - cy) * (ky[j] - cy) < r)
                f[j].set(i);// 如果在圆内，设置对应位为1
    }

    for (; k--; ) {
        int a = read(), b = read();
        write((f[a] ^ f[b]).count());// 计算两个点所在圆集合的对称差集的元素个数
        puts("");
    }
    return 0;
}