//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
sum[k]：整个数组第 k 类位（0偶/1奇）的总和。
p[k]：已扫过部分（下标 < i）第 k 类位的和。 用 p[0]、p[1] 记录已经扫过（i 之前）‍的偶/奇位和
ans：满足条件的删除位置数
读入并一次性求出整数组奇偶索引总和 sum[0]、sum[1]
sum[i%2] -= a[i]：此时 sum[0]、sum[1] 表示从 i+1 到 n 的各奇偶位总和（等价于把第
i 个剔除后的“剩余部分”，但注意奇偶关系在删除后发生互换——用 sum[1] 对应偶、sum[0] 对应奇来体现）。
判断：
删除 i 后，
偶数位总和 =（i 之前偶数位 p[0]）+（i 之后，原本是奇数位、删除后左移变偶数位的 sum[1]）
奇数位总和 =（i 之前奇数位 p[1]）+（i 之后原本偶数位变奇数位的 sum[0]）
相等则 ans++。
p[i%2] += a[i]：把 i 计入"已扫过部分"，供后续位置判断用
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 2e5+5;

int n, a[N], sum[2], p[2], ans;
int main() {
    fast;
    cin >> n;
    rep(i,n) { cin >> a[i]; sum[i%2] += a[i]; }
    rep(i,n) {
        sum[i%2] -= a[i];
        if (p[0] + sum[1] == p[1] + sum[0]) ans++;
        p[i%2] += a[i];
    }
    cout << ans;
    return 0;
}