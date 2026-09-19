//
// Created by Psy.C on 2026/9/19.
//
/**
三正则图（每个点度 = 3）的边数 =
3
n
/
2
3n/2，边数必须是整数，因此
n
n 必须为偶数
三正则简单图存在当且仅当
n
n 为偶数且
n
≥
4
n≥4（
n
=
2
n=2 也不行，因为两个点无法各自有 3 个不同邻居）。本代码判断 n%4==2 || n%4==3 输出 NO，也就是说只允许
n
≡
0
n≡0 或
n
≡
1
(
m
o
d
4
)
n≡1(mod4)。
代码把点按 (4q+1, 4q+2, 4q+3, 4q+4) 分组（q 从 0 开始），每组 4 个点。

情况 A：
n
≡
0
(
m
o
d
4
)
n≡0(mod4)（正好整组）

f(i) 对一组 4 个点输出 6 条边：
这是
K
4
K
4
​
 （4 个点的完全图），每个点度 = 3。所以当
n
≡
0
n≡0 时，把点分成
n
/
4
n/4 组
K
4
K
4
​
  即可，每组内部独立是 3 正则。

情况 B：
n
≡
1
(
m
o
d
4
)
n≡1(mod4)（有一组多出 1 个点）

f2(i) 对"第
n
n 点"+ 一组 4 点的输出 10 条边（4+6 结构，把特殊点 n 与每个点/交叉连满保证度 3）：

构造性地输出一个图（本质是完全图
K
n
K
n
​
 ）。代码把 n 个点按 4 个一组分组：组内连成
K
4
K
4
​
 （余数 1 时补第 n 点成
K
5
K
5
​
 ），组间两两调用 get 使每个点与另一组所有点全连，从而覆盖所有点对边；仅当
n
  
m
o
d
  
4
∈
{
0
,
1
}
nmod4∈{0,1} 时输出（多组数据中如 n=6 等 %4=2/3 的情况输出 NO——这反映题目对 n 的取模限制或构造模板仅覆盖这些规模）。校验每组内部的度：情况 A 每点度
4
G
−
1
=
n
−
1
4G−1=n−1，情况 B 每点度
4
G
=
n
−
1
4G=n−1，恰好都是完全图的度，因此最终输出的是
K
n
K
n
​
  的完整边集
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int d1, d2, d3, d4;
void f(int q) {
    q--; d1 = 4*q+1; d2 = 4*q+2; d3 = 4*q+3; d4 = 4*q+4;
    cout << d1 << ' ' << d2 << '\n'; cout << d3 << ' ' << d4 << '\n';
    cout << d1 << ' ' << d4 << '\n'; cout << d2 << ' ' << d3 << '\n';
    cout << d1 << ' ' << d3 << '\n'; cout << d2 << ' ' << d4 << '\n';
}

int n;
void f2(int q) {
    q--; d1 = 4*q+1; d2 = 4*q+2; d3 = 4*q+3; d4 = 4*q+4;
    cout << d1 << ' ' << n << '\n'; cout << d1 << ' ' << d2 << '\n';
    cout << d2 << ' ' << n << '\n'; cout << d3 << ' ' << n << '\n';
    cout << d3 << ' ' << d4 << '\n'; cout << d4 << ' ' << n << '\n';
    cout << d1 << ' ' << d4 << '\n'; cout << d2 << ' ' << d3 << '\n';
    cout << d1 << ' ' << d3 << '\n'; cout << d2 << ' ' << d4 << '\n';
}

int v1, v2, v3, v4;
void get(int q, int w) {
    q--; d1 = 4*q+1; d2 = 4*q+2; d3 = 4*q+3; d4 = 4*q+4;
    w--; v1 = 4*w+1; v2 = 4*w+2; v3 = 4*w+3; v4 = 4*w+4;
    cout << d1 << ' ' << v1 << '\n'; cout << d2 << ' ' << v2 << '\n';
    cout << d1 << ' ' << v2 << '\n'; cout << d2 << ' ' << v1 << '\n';
    cout << d1 << ' ' << v3 << '\n'; cout << d2 << ' ' << v4 << '\n';
    cout << d1 << ' ' << v4 << '\n'; cout << d2 << ' ' << v3 << '\n';
    cout << d3 << ' ' << v1 << '\n'; cout << d4 << ' ' << v2 << '\n';
    cout << d3 << ' ' << v2 << '\n'; cout << d4 << ' ' << v1 << '\n';
    cout << d3 << ' ' << v3 << '\n'; cout << d4 << ' ' << v4 << '\n';
    cout << d3 << ' ' << v4 << '\n'; cout << d4 << ' ' << v3 << '\n';
}


int main() {
    fast;
    cin >> n;
    if (n%4 == 2 || n%4 == 3) { cout << "NO"; return 0; }
    cout << "YES\n";
    if (n%4 == 0) {
        for (int i = 1; i <= n/4; ++i) f(i);
    } else {
        for (int i = 1; i <= n/4; ++i) f2(i);
    }
    for (int i = 1; i <= n/4; ++i)
        for (int j = i+1; j <= n/4; ++j) get(i, j);
    return 0;
}