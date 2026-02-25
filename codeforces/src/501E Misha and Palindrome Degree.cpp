//
// Created by Psy.C on 2026/2/25.
//
/**
n：数组长度
a[N]：存储输入的数组元素
f[N]：频次数组，记录每个数字出现的次数
m：奇数频次的元素个数
c[N]：临时计数数组

有多于1个元素出现奇数次，则无法构成回文
x：从两端开始匹配的位置
len：中间可扩展的长度
从两端向中间匹配相等的元素：
当两端元素相等时继续
对应频次减2（两边各用掉一个）
x向中间移动
特殊情况：如果整个数组都是回文，输出所有子串数量n(n+1)/2
从右端开始向左扩展检查
检查当前位置能否加入：
++c[a[i]]：当前元素计数加1
2*c[a[i]] > f[a[i]]：如果使用次数超过可用次数
判断是否可以继续：
i > n-i+1：不在对称位置
a[i] != a[n-i+1]：与对称位置元素不同
满足任一条件则停止
特殊处理中心位置：
i == n-i+1：在正中心
f[a[i]] % 2 == 0：但该元素频次为偶数（不能作为中心）
这种情况下也要停止

成功加入则长度加1

x：两端确定的回文部分
x+len：总的可构造回文前缀长度
乘积表示可能的回文子串数量
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+1;

int n, a[N], f[N], m, c[N];
int main() {
    fast;
    cin >> n; a[0] = -1;
    for (int i = 1; i <= n; ++i) cin >> a[i], ++f[a[i]];
    for (int i = 1; i <= n; ++i) m += f[i]&1;
    if (m > 1) return cout << "0\n", 0;
    int x = 1, len = 0;
    while (a[x] == a[n-x+1]) f[a[x++]] -= 2;
    if (x > n) return cout << 1ll*n*(n+1)/2, 0;
    for (int i = n-x+1; i >= 1; --i) {
        if (2*++c[a[i]] > f[a[i]]) {
            if (i > n-i+1 || a[i] != a[n-i+1]) break;
            if (i == n-i+1 && f[a[i]] % 2 == 0) break;
        }
        ++len;
    }
    memset(c, 0, sizeof c);
    for (int i = x; i <= n; ++i) {
        if (2*++c[a[i]] > f[a[i]]) {
            if (i < n-i+1 || a[i] != a[n-i+1]) break;
            if (i == n-i+1 && f[a[i]] % 2 == 0) break;
        }
        ++len;
    }
    cout << 1ll*x*(x+len) << '\n';
    return 0;
}