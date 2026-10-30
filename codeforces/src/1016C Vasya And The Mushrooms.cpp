//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
n：物品对数。
a[i]：第 i 个位置第一行（先手层）物品价值。
b[i]：第 i 个位置第二行物品价值。
sum[i]：从 i 到 n 的 a[j]+b[j] 后缀和。
sa[]、sb[]：两种"从左往右折返收集"策略的后缀贡献和。
sc[i]：按蛇形（i 从 1 逐个折返）取到第 i 个位置后的累计价值。
ans：已取物品的计数（从 0 开始，第 k 个取的物品系数是 k，即"取到它的那一刻步数"）。
res：蛇形前缀累计价值。
mx：最终答案（最大总价值）
读入 n，第一行 n 个数存入 a[1..n]，第二行 n 个数存入 b[1..n]
从 n 往前递推：sum[i] = sum[i+1] + a[i] + b[i]，表示位置 i 及其右侧所有物品的价值总和。用于后面大量累加一个连续区间的总价值
注意这里同时维护了两个游标：i 从 n 递减到 1，j 从 n 递增。
sa[i] = sa[i+1] + (i-1)*a[i] + j*b[i]。
结合 j 每次 +1，后面在计算答案时用它给"若从位置 i 的某层开始续接"赋予正确权重。
这是代码确定行为。它构造了一个从 i 到 n 的加权后缀，权重沿 i、j 各按等差数列变化
与 sa 类似但轮换 a、b 的顺序和系数：sb[i] = sb[i+1] + i*b[i] + j*a[i]，且 j 从 n+1 起步。

最后单独补 sb[1] = sb[2] + b[1]：因为 sb 的循环从 i≥2 开始，i=1 处只有 b[1] 一项计入（a[1] 已在其他地方处理），所以单独补上一项 b[1]
核心模拟"蛇形取物"：

在奇数位 i（i%2==1）：先取 a[i]（系数用当前 ans，即第 ans 个取到），ans++，再取 b[i]，ans++。
在偶数位 i（i%2==0）：顺序反一反，先取 b[i] 再取 a[i]。
即走法整体呈现折返：1 号位取过一次后，方向改变，后面按 a、b 交替顺序取。res 累加每次的"价值×已取数量"，sc[i] 存档到第 i 列结束时的累计价值
i 遍历 0..n，表示切换点：前 i 列按蛇形前缀（sc）走，之后 i+1..n 列换用另一种策略（sa 或 sb）续接。
sc[i]：前 i 列的蛇形累计价值。
若 i 为奇数 i%2==1：续接 sb[i+1]，并加上 (i-1)*sum[i+1]（给剩余区间整体补一个 (i-1) 的权重）。
若 i 为偶数 i%2==0：续接 sa[i+1]，加 i*sum[i+1]。
取所有情况的 max 作为最终答案 mx 输出。
这个式子把「两种折返方向的后续贡献 sa/sb」和「剩余区间总价值 sum 的整体系数」组合在一起，遍历最优切换位置取最大
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define per(i,n) for (int i=n; i>=1; i--)
#define ll long long
using namespace std;

constexpr int N = 1e6+1, inf = 0x3f3f3f3f;

int n;
ll a[N], b[N], sum[N], sa[N], sb[N], sc[N], ans, res;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    rep(i,n) cin >> b[i];
    per(i,n) sum[i] = sum[i+1] + a[i] + b[i];
    for (int i = n, j = n; i >= 1; i--, j++) sa[i] = sa[i+1] + (i-1)*a[i] + j*b[i];
    for (int i = n, j = n+1; i >= 2; i--, j++) sb[i] = sb[i+1] + i*b[i] + j*a[i];
    sb[1] = sb[2] + b[1];
    rep(i,n) {
        if (i%2) {
            res += ans*a[i]; ans++;
            res += ans*b[i]; ans++;
            sc[i] = res;
        } else {
            res += ans*b[i]; ans++;
            res += ans*a[i]; ans++;
            sc[i] = res;
        }
    }
    ll mx = -inf;
    for (int i = 0; i <= n; i++) {
        if (i%2) mx = max(mx, sc[i]+sb[i+1]+(i-1)*sum[i+1]);
        else mx = max(mx, sc[i]+sa[i+1]+i*sum[i+1]);
    }
    cout << mx << '\n';
    return 0;
}