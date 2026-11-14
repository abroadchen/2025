//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
标准交互格式：询问区间 [l,r]，读一个整数返回
情况 A：n == 1
单元素，直接输出初始值 m。
情况 B：n 为奇数
"反复询问直到返回值改变" 来探测某个量：

for(x=m; x==m; x=ask(...)) ask(...) 意思是"先问一次，若返回仍等于 m 就再问"，直到拿到与当前 m 不同的值 x。
通过比较 x < m 判断方向，并维护一个 rev[] 全局翻转数组（按区间的某些边界异或翻转）。
逐位由 ans[i+1] 推导 ans[i]
情况 C：n 为偶数
偶数情况从后往前 per(i,n)，每次反复问单点 [i,i]，同样维护 rev[]，最后按位与 rev 异或得到 ans[i]
最后输出 ! 加每一位的答案


ans[i+1]：右边一位的答案（已算出）。
rev[i+1] 与 rev[i]：第 i+1、i 位的翻转状态。
ans[i+1] ^ rev[i+1]：先用翻转状态还原/反转 ans[i+1] 的真实值。
(m+x-n)/2 + 1 - (还原后的 ans[i+1])：利用左右相邻关系 + 某区间统计量反推 ans[i] 的原始值。这里的 (m+x-n)/2 + 1 是一个由询问得到的两数 m, x 及总数 n 算出的基准/边界。
最后 ^ rev[i]：再把第 i 位的翻转状态加回去，得到真正的 ans[i]
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define per(i,n) for (int i=n; i>=1; i--)
using namespace std;

constexpr int N = 305;

int ask(int l, int r) {
    cout << "? " << l << ' ' << r << endl;
    int q; cin >> q;
    return q;
}

int n, m, ans[N], rev[N];
int main() {
    fast;
    cin >> n >> m;
    int x;
    if (n == 1) ans[1] = m;
    else if (n&1) {
        for (x = m; x == m; x = ask(1,n-1)) ask(1,n-1);
        ans[n] = x < m; rev[n] = 1;
        per(i,n-1) {
            for (m = x; x == m; x = ask(i,i+1)) ask(i,i+1);
            rep(j,n) rev[j] ^= j < i || j > i + 1;//除了 j == i 和 j == i+1 这两个位置之外，其余所有位置的 rev 都被翻转一次
            ans[i] = (m+x-n)/2+1-(ans[i+1]^rev[i+1])^rev[i];
        }
    } else {
        x = m;
        per(i,n) {
            for (m = x; x == m; x = ask(i,i)) ask(i,i);
            rep(j,n) rev[j] ^= j < i || j > i;
            ans[i] = (m+x-n+1)/2^rev[i];
        }
    }
    cout << "! ";
    rep(i,n) cout << ans[i];
    fflush(stdout);
    return 0;
}