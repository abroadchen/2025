//
// Created by Psy.C on 2026/10/12.
//
/**
n, m，然后一个长度为 n 的字符串 a。
a[i] 是 '0' 或 '1'。
初始化：

f[1..n] = inf，f[1] = 0。
flg[i] = 位置 i 是否可走（a[i-1]=='1' 为 true）
从位置 1 出发，只能落在 '1' 的格子上，每步最多向前跳 m 格，问到达 n 所需的最少步数
把字符数组转成 flg[]（1-indexed）：a[i]=='1' → 位置 i+1 可走。
f[i] = 从位置 1 跳到位置 i 的最少步数。这里只更新 flg[i]==true 的可走格，且只从可走的前驱 j 转移（一步最多跨 m 格，所以 j ≥ i-m）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e2, inf = 1e3;

int n, m, f[N];
char a[N];
bool flg[N];
int main() {
    fast;
    cin >> n >> m >> a;//读 n、步长上限 m、地面字符串
    for (int i = 1; i <= n; ++i) f[i] = inf;
    f[1] = 0;//起点是位置 1，步数为 0
    for (int i = 0; i < n; ++i) {//i 是字符串下标 0..n-1
        if (a[i] == '0') flg[i+1] = false;//位置 i+1 不可走
        else flg[i+1] = true;
    }
    for (int i = 2; i <= n; ++i) {//对每个位置 i（从 2 开始）
        if (flg[i] == true) {//只有 i 可走才更新它
            for (int j = max(1, i-m); j <= i-1; ++j)//枚举从 j 跳来，j∈[i-m, i-1]
                if (flg[j] == true)//j 也必须可走
                    f[i] = min(f[i], f[j]+1);
        }
    }
    //终点不可达 → -1
    if (f[n] == inf) cout << -1; else cout << f[n];
    return 0;
}