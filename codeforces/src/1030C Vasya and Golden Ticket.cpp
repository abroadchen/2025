//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
读入 0/1 串，转成整数数组，求前缀和 sum
假设第一段是 [1..i]，那么目标每段和 = sum[i] = x，第二段从 k=i 后面开始尝试切分。
从 k 开始，尝试每段和恰为 x：用双指针 cur 到 i，判断区间和是否等于 x。
跳过连续的 0 很关键：0 不改变和，起"占位/延展"作用，但允许段可以包含多个 0 仍保持和相同。
全部切完后，tot = 段数；要求 tot ≥ 2（即至少切成两段），且最后一段和也要是 x
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 200;

int n, sum[N];
bool check(int x, int k) {
    int cur = k, tot = 1;
    for (int i = k+1; i <= n; i++) {
        if (sum[i] - sum[cur] == x) {//找到一段和恰为 x
            cur = i, tot++;//切一段
            while (sum[i] == sum[i+1]) i++, cur++;//跳过连续的 0(和为0不影响)
        }
        else while (sum[i+1] == sum[i]) i++;//当前段和不够,跳过连续 0
    }
    if (sum[n] - sum[cur] != x && cur != n) return 0;//最后一段和不是 x → 失败
    if (tot > 1) return 1;//至少分了两段 → 成功
    return 0;
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

char s[N];
int a[N];
int main() {
    fast;
    read(n); scanf("%s", s+1);
    if (n == 1) { cout << "NO\n"; return 0; }
    rep(i,n) a[i] = s[i] - '0';
    rep(i,n) sum[i] = sum[i-1] + a[i];
    rep(i,n) if (check(sum[i], i)) { cout << "YES\n"; return 0; }
    cout << "NO\n";
    return 0;
}