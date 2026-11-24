//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
dfs(x, w) 表示对位置 x 执行"加 w（可为 ±1）"，连带 x+1 也加 w。
关键：由于相邻两位必须一起变，若改 x+1 会越界（超出 '0'..'9'），就递归把操作转移到 x+1 并取反方向 -w（即在更右的位置反向操作来抵消），保证始终在合法数字范围内。
每次执行后输出 x w，并递减 ans，ans 是"总操作数上限"，输满就 exit(0) 提前结束。
w 决定方向：t[i] > s[i] 时 w=+1（需要变大的位置加），反之为 -1
a[i] 是某种差分/前缀累积：(t[i]-s[i]) 再叠加上一层 -a[i-1]。
ans 是所有 abs(a[i]) 之和，作为理论上最少需要的操作次数。
a[n] 必须为 0（差分闭合，即总量能被救回来），否则无解输出 -1。
最小操作数定为 ans
若 ans 为 0 直接结束（无需操作）。
把 ans 限制在 inf=1e5 以内，避免输出过多。
从左到右，对每个位置 i，只要 s[i] != t[i] 就调用 dfs(i, 方向)，由前面分析，方向取"需要变大则 +1，否则 −1"，操作会连带影响下一个位置，再靠 dfs 内的递归处理越界问题
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
#define ll long long
using namespace std;

constexpr int N = 1e6+5, inf = 1e5;

string s;
ll ans;
void dfs(int x, int w) {
    if (s[x+1]+w < '0' || s[x+1]+w > '9') dfs(x+1, -w);
    cout << x << ' ' << w << '\n';
    s[x] += w; s[x+1] += w;
    if (!--ans) exit(0);
}

int n;
string t;
ll a[N];
int main() {
    fast;
    cin >> n >> s >> t; s = ' ' + s; t = ' ' + t;
    rep(i,n) {
        a[i] = -a[i-1] + t[i] - s[i];
        ans += abs(a[i]);
    }
    if (a[n]) { cout << "-1\n"; return 0; }
    cout << ans << '\n';
    if (!ans) return 0;
    ans = min(ans, (ll)inf);
    rep(i,n-1) while (s[i] != t[i]) dfs(i,t[i] > s[i] ? 1 : -1);
    return 0;
}