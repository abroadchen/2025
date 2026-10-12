//
// Created by Psy.C on 2026/10/12.
//
/**
构造目标是让每对相邻数 (v[i], v[i+1]) 满足特定二进制关系——这里通过「找到不超过 i 的最大 2 的幂 t，把 i 和 t-(i-t)-1 = 2t - i - 1 配对」来实现。i + x = 2t - 1（是 2t-1，也就是一个 "全 1 的数"），这类构造常被用于「相邻异或」或「相邻和为 2 的幂 - 1」的排列题。
if (t > i) t >>= 1：让 t 回落到当前区间内有效的 2 的幂。
if (!v[i])：因为配对是 i ↔ x 双向填的，大的 i 会先配对掉对应的小 x，所以再从大到小扫描时只需处理还没被配对的。
奇偶判断 if (n&1)：n 为奇数时这种配对关系无法闭合成完美排列，故 NO
判断条件 n == y || n < 6：n 是 2 的幂或过小 → 无解。
n == 6 特判手工答案。
其他 n：固定前缀 7 3 6 5 1 2 4，然后用 for(i=8; i<=n;) 按 i..2i-1 的块，输出 i+1, i+2, ..., 2i-1, i 的轮转顺序，构造出满足「相邻差为 2 的幂」一类性质
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; --i)
using namespace std;

constexpr int N = 1e5+10;

int n, y(1), v[N];
int main() {
    fast;
    cin >> n;
    while (y<<1 <= n) y <<= 1;//y = 最大的 ≤n 的 2 的幂
    if (n&1) cout << "NO\n";//n 为奇数 → 无解
    else {
        cout << "YES\n";
        int t = y;
        per(i,n,1) {
            if (t > i) t >>= 1;//保证 t 是 [i, 2i] 区间里的 2 的幂
            if (!v[i]) {//i 还没被配对
                int x = t - (i-t) - 1;//算出与 i 配对的位置
                v[i] = x; v[x] = i;//双向填，保证 v 是排列
            }
        }
        rep(i,1,n) cout << v[i] << ' ';
        cout << '\n';
    }
    if (n == y || n < 6) cout << "NO\n";
    else {
        cout << "YES\n";
        if (n == 6) cout << "3 6 2 5 1 4\n";
        else {
            cout << "7 3 6 5 1 2 4 ";
            for (int i = 8; i <= n; ) {
                int j = min(i<<1, n+1);
                rep(k,i,j-2) cout << k+1 << ' ';
                cout << i << ' ';
                i = j;
            }
        }
    }
    return 0;
}