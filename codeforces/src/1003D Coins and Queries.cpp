//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
m[面额] = 张数，map 按键升序存储。
m.end() 指向末尾之后，--it 即可从最大面额开始
读入 n 张纸币（面额为 a），累加该面额的张数。
相同面额合并计数
核心 mn = min(b/(面额), 张数)：优先用大面额尽量多取，直到手头不够或目标变小。
每轮从大到小遍历所有面额。
退出条件：
若已遍历到最小面额（it == m.begin()）且 b 还没减到 0 → 说明凑不出，输出 -1。
若 b == 0 → 凑满，输出张数 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i = 1; i <= (n); i++)
using namespace std;

int n, q, i, a, b, ans, mn;
map<int, int> m;
int main() {
    fast;
    cin >> n >> q;
    rep(i,n) { cin >> a; m[a]++; }
    rep(i,q) {
        ans = 0;
        cin >> b;
        auto it = m.end();
        while (true) {
            --it;
            mn = min(b/(it->first), it->second);//最多能取多少张：min(目标值能容纳的张数, 手头张数)
            b -= mn*(it->first);
            ans += mn;
            if (it == m.begin() && b != 0) { cout << "-1\n"; break; }
            if (b == 0) { cout << ans << '\n'; break; }
        }
    }
    return 0;
}