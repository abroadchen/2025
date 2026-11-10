//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
双哈希防碰撞：用两个不同的底数 + 两个不同模数分别做哈希，返回 pair<hash1, hash2>，几乎可判别两段是否相同。
get(l,r) 用前缀哈希 O(1) 取子串哈希
按 s 逐个字符，用 now 作为当前游标，把对应长度段从 t 里切出来。
断言：模式 s 里所有 '0' 段都必须与同一内容相同；所有 '1' 段也必须同一内容。任一不符返回 0。
最后排除“0段 == 1段”的情况
统计 s 里 '0' 和 '1' 的个数，让 c0 是较多那个（减少枚举循环，符号 x='0', y='1' 被交换）。
枚举 '0' 段长度 lx：
tot = c0*lx：所有 '0' 占用总长。
要求 tot < m（留空间给 c1 段）。
rem = m-tot：剩下给 '1' 段的总长，必须能被 c1 整除，得到 ly。
ly > 0 时用 check() 验证该组 (lx,ly) 是否可行，可行 ans++
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define ii pair<int, int>
#define int long long
using namespace std;

constexpr int N = 1e6+5, BS1 = 131, BS2 = 137, mod1 = 1e9+9, mod2 = 1e9+7;

int pw1[N], pw2[N], h1[N], h2[N], m;
string t;
inline void init() {
    pw1[0] = pw2[0] = 1;
    rep(i,m) {//幂
        pw1[i] = pw1[i-1]*BS1%mod1;
        pw2[i] = pw2[i-1]*BS2%mod2;
    }
    h1[0] = h2[0] = 0;
    rep(i,m) {//前缀哈希
        h1[i] = (h1[i-1]*BS1+t[i-1])%mod1;
        h2[i] = (h2[i-1]*BS2+t[i-1])%mod2;
    }
}

inline ii get(int l, int r) {//子串 [l,r) 的哈希
    int ha1 = (h1[r]-h1[l]*pw1[r-l]%mod1+mod1)%mod1;
    int ha2 = (h2[r]-h2[l]*pw2[r-l]%mod2+mod2)%mod2;
    return {ha1, ha2};
}

int n, lx, ly;
string s;
char x = '0', y = '1';
inline bool check() {
    int now = 0, px = -1, py = -1;
    ii hx, hy;
    for (int i = 0, l, r; i < n; i++) {
        if (s[i] == x) {//字符等于 '0'（默认 x='0'）
            l = now, r = now + lx;
            ii h = get(l, r);
            if (px == -1) { hx = h; px = l; }//第一次遇到0段，记录
            else if (h != hx) return 0;//后续0段必须与第一个0段完全相同
            now = r;
        } else {//字符为 '1'
            l = now, r = now + ly;
            ii h = get(l, r);
            if (py == -1) { hy = h; py = l; }//第一次遇到1段
            else if (h != hy) return 0;//后续1段必须一致
            now = r;
        }
    }
    //0段与1段内容不能完全相同（除非长度不同天然可区分？
    if (hx == hy) if (lx == ly) {//两哈希相等且长度相等 → 相同非空串
        if (t.substr(px, lx) == t.substr(py, ly))
            return 0;//确认真相同则非法
    }
    return 1;
}


signed main() {
    fast;
    cin >> s >> t; n = s.size(), m = t.size(); init();
    int c0 = count(s.begin(), s.end(), '0'), c1 = n - c0, ans = 0;
    if (c0 < c1) { swap(x, y); swap(c0, c1); }
    for (lx = 1; lx <= m; lx++) {
        int tot = c0*lx;
        if (tot >= m) break;
        int rem = m - tot;
        if (!(rem%c1)) {
            ly = rem/c1;
            if (ly > 0) ans += check();
        }
    }
    cout << ans << '\n';
    return 0;
}