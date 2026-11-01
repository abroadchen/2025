//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
int n, a[N];         // 数组 a（可能含 0，0 表示"待填充"）
int f[N][30];        // Sparse Table：f[i][j] 表示区间 [i, i+2^j-1] 的最小值
int pr[N], re[N];    // pr[i]：值 i 第一次出现的位置；re[i]：值 i 最后一次出现的位置
int q;               // 数值的上限（值范围为 1..q）
a[i] 中 0 表示该位置尚未确定（需要填充）。
tot：0 的个数。
mx：当前数组最大值（不含 0）
如果整个数组都是 0，就直接全部填成 q（最大允许值）→ 输出 YES
如果当前数组中没有出现 q，而题目要求必须出现一次 q（通常题目要求数值 q 必须在数组中），则需要把某个 0 填成 q。
找到第一个 0 位置填成 q。
如果连 0 都没有（flg == false），说明 q 无处安放 → 输出 NO。
否则调用 solve() 继续校验

从左到右，遇到 0 就用前一个非 0 值填充（把 0 补齐成左边的值）
从右到左再补一次（这样最左边的 0 也能被填充，因为可能前面全是 0）。
f[i][0] = a[i]：稀疏表第一层，即单元素区间的最小值就是它本身
rep(i,n) if (pr[a[i]] == 0) pr[a[i]] = i;   // 值 a[i] 第一次出现的位置
per(i,n) if (re[a[i]] == 0) re[a[i]] = i;   // 值 a[i] 最后一次出现的位置
经典的 ST 表构建，f[i][j] 保存 [i, i+2^j-1] 区间最小值
对每个出现的数值 i，它第一次出现位置 pr[i] 到最后一次出现位置 re[i] 之间的整个区间的最小值必须等于 i。

也就是说：值 i 一定是我在该区间内能看到的最小值，区间内不能出现比 i 更小的值。
用 ST 表 O(1) 查询区间 [pr[i], re[i]] 的最小值。
若最小值不等于 i → 不合法，输出 NO
填充后的完整数组输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(i=1;i<=n;i++)
#define per(i,n) for(i=n;i>=1;i--)
using namespace std;

constexpr int N = 2e5+10;

int n, a[N], f[N][30], pr[N], re[N], q;
void solve() {
    int i, j;
    rep(i,n) if (a[i] == 0) a[i] = a[i-1];
    per(i,n) {
        if (a[i] == 0) a[i] = a[i+1];
        f[i][0] = a[i];
    }
    rep(i,n) if (pr[a[i]] == 0) pr[a[i]] = i;
    per(i,n) if (re[a[i]] == 0) re[a[i]] = i;
    rep(j,log2(n)) rep(i,n-(1<<j)+1)
        f[i][j] = min(f[i][j-1], f[i+(1<<(j-1))][j-1]);
    int s;
    rep(i,q) {
        if (re[i] == 0 || pr[i] == 0) continue;
        s = log2(re[i] - pr[i] + 1);
        if (i != min(f[pr[i]][s], f[re[i]-(1<<s)+1][s])) { cout << "NO"; return; }
    }
    cout << "YES\n";
    rep(i,n) cout << a[i] << ' ';
}

int mx, tot;
int main() {
    fast; int i;
    cin >> n >> q;
    rep(i,n) {
        cin >> a[i];
        if (a[i] == 0) tot++;
        mx = max(mx, a[i]);
    }
    if (tot == n) {
        cout << "YES\n";
        rep(i,n) cout << q << ' ';
        return 0;
    }
    bool flg = false;
    if (mx < q) {
        rep(i,n) if (a[i] == 0) { a[i] = q; flg = true; break; }
        if (flg == false) { cout << "NO"; return 0; }
        solve();
        return 0;
    }
    solve();
    return 0;
}