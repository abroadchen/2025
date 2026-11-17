//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
读 n，然后读 n 个数，每个数当场取模 2 存进 a[i]。于是 a[i] 只有 0（偶数）或 1（奇数
对每个元素：
q[++t] = a[i]：入栈（t 先自增再写入，模拟把元素压到栈顶）。
if (t > 1 && q[t] == q[t-1]) t -= 2;：检查栈顶两个元素是否相等（同为 0 或同为 1）。若相等，则 t -= 2——相当于把这对相同元素弹出栈（指针回退 2 格，覆盖读丢弃）
结束后看栈内剩余元素个数 t：
t < 2（即 0 或 1 个剩）→ 输出 YES；
否则（t ≥ 2）→ 输出 NO
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1;i<=n;i++)
using namespace std;

constexpr int N = 2e6+5;

int n, a[N], q[N], t;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i], a[i] = a[i]%2;
    rep(i,n) {
        q[++t] = a[i];
        if (t > 1 && q[t] == q[t-1]) t -= 2;
    }
    cout << (t < 2 ? "YES" : "NO") << '\n';
    return 0;
}