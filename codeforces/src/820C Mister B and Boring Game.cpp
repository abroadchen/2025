//
// Created by Psy.C on 2026/9/23.
//
/**
ans 初始化：若 a <= b，初始上界为 a+1，否则为 2a - b（这是某种保守上界/平凡解的答案，通常对应「不压缩时的最多字符能被控制在某个数」之类的贪心界）。
T = 2*(a+b)：把整个序列视为周期为 T 的循环节，只关心一个周期内的构造。
若区间长度 r-l >= T（覆盖了至少一个完整循环节），则所有字符必然都出现（不用优化，保持原 ans）。
否则将 l, r 都对 T 取模（折叠到单个周期内），并枚举 dfs('a'+i)：分别尝试用字符 'a'..'a'+a-1 作为「填充字符块 cp」来构造，取不同字符数的最小值作为答案
前 a 个位置依次填 a, a+1, ..., a+a-1（即字符 'a' 到 'a'+a-1，注意这里 s[i] = 'a'+i，所以前 a 个字符是 'a','b','c',...）。
中间 b 个位置全部填 cp（要枚举的填充字符）。
记录这一段中出现的字符到 vis
在 [a+b, 2a+b) 这一段（长度 a）填充「还没用过的字符」，按序取 'a' 开始第一个未使用字符 ed。这就是一种贪心的「尽量复用已出现字符、只补充最少新字符」的构造。
由于已出现的字符最少时（a 个新字符 + cp 这一种），这里会把未出现的最小字符依次填入
最后统计区间 [l,r] 内不同字符的种类数。若 l <= r 直接数；若 l > r（因为取模后可能跨周期环绕），则分两段数 [0,r] 和 [l,T)。
返回这个区间内不同字符数 cnt
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 200, M = 27;

int a, b, T, l, r;
char s[N];
bool vis[M];
int dfs(char cp) {
    int cnt = 0;
    for (int i = 0; i < a; ++i) s[i] = 'a' + i;
    for (int i = a; i < a+b; ++i) s[i] = cp;
    memset(vis, false, sizeof(vis));
    for (int i = b; i < a+b; ++i) vis[s[i]-'a'] = true;
    int st = a+b, ed = 0;
    while (st < 2*a+b) {
        while (vis[ed]) ed++;
        s[st] = ed + 'a';
        st++, ed++;
    }
    for (int i = 2*a+b; i < T; ++i) s[i] = s[i-1];
    memset(vis, false, sizeof(vis));
    if (l <= r) {
        for (int i = l; i <= r; ++i)
            if (!vis[s[i]-'a'])
                cnt++, vis[s[i]-'a'] = true;
    } else {
        for (int i = 0; i <= r; ++i)
            if (!vis[s[i]-'a'])
                cnt++, vis[s[i]-'a'] = true;
        for (int i = l; i < T; ++i)
            if (!vis[s[i]-'a'])
                cnt++, vis[s[i]-'a'] = true;
    }
    return cnt;
}

int ans;
int main() {
    fast;
    cin >> a >> b >> l >> r; l--, r--;
    if (a <= b) ans = a + 1; else ans = 2*a - b;
    T = 2*(a+b);
    if (r - l >= T) {}
    else {
        r %= T, l %= T;
        for (int i = 0; i < a; ++i)
            ans = min(dfs('a' + i), ans);
    }
    cout << ans << '\n';
    return 0;
}