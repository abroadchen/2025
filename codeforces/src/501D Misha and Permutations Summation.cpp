//
// Created by Psy.C on 2026/2/25.
//
/**
处理负数：输出负号，递归输出绝对值
递归输出：先输出高位数字，再输出当前位（ASCII码转换）

树状数组单点更新：
在位置x增加v
向上更新所有相关的节点
树状数组前缀和查询：
计算[1,x]区间内的元素和
向下累加所有相关的节点

二分查找函数，找第x小的元素位置
query(mid-1)计算比mid小的元素个数
根据比较结果调整搜索区间

a[N]：原始数组
s1[N]：第一次处理的逆序对统计
s2[N]：第二次处理的逆序对统计
s[N]：进位数组

a[i] = read<ll>()+1：读入数据并偏移1（避免0）
update(i, 1)：在树状数组中标记位置i存在元素
计算第一组数据的逆序对：
query(a[i]-1)：统计比a[i]小的元素个数
update(a[i], -1)：移除已处理的元素


处理进位运算：
将两组逆序对统计相加
处理超出范围的进位
处理第一位的进位并取模

重新初始化树状数组
根据统计结果重构数组：
get(s[i])：找到应该放在位置i的元素
update(a[i], -1)：标记该元素已被使用

输出结果（减去之前加的偏移量）
 */
#include <bits/stdc++.h>
#define ll long long
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

template<class T>
T read() {
    int f = 0, ch = 0; T x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) {
        putchar('-');
        write(-x);
        return;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}

constexpr int N = 2e5+1;
ll low_bit(const ll x) { return x & -x; }

ll n, t[N];
void update(ll x, const ll v) {
    while (x <= n)
        t[x] += v, x += low_bit(x);
}
ll query(ll x) {
    ll res = 0;
    while (x) {
        res += t[x];
        x -= low_bit(x);
    }
    return res;
}
ll get(const ll x) {
    ll l = 1, r = n + 1;
    while (l < r) {
        const ll mid = (l+r)>>1;
        if (const ll num = query(mid-1); num > x) r = mid;
        else l = mid + 1;
    }
    return l - 1;
}

ll a[N], s1[N], s2[N], s[N];
int main() {
    n = read<ll>();
    rep(i,n) a[i] = read<ll>()+1, update(i, 1);
    rep(i,n) { s1[i] = query(a[i]-1); update(a[i], -1); }
    rep(i,n) a[i] = read<ll>()+1, update(i, 1);
    rep(i,n) { s2[i] = query(a[i]-1); update(a[i], -1); }
    for (int i = n-1; i >= 2; --i) {
        s[i] += s1[i] + s2[i];
        if (s[i] >= n-i+1) {
            s[i-1] += s[i]/(n-i+1);
            s[i] %= n-i+1;
        }
    }
    (s[1] += s1[1] + s2[1]) %= n;
    rep(i,n) update(i, 1);
    rep(i,n) { a[i] = get(s[i]); update(a[i], -1); }
    rep(i,n) write(a[i]-1), putchar(' ');
    putchar('\n');
    return 0;
}