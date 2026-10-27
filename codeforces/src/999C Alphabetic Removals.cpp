//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
a[c] 表示字符 'a'+c 在 s 中出现的次数。
之后转换成前缀和：a[i] 表示小于等于字符 'a'+i 的字符总数
遍历字母 i（升序），当前缀和 a[i] ≥ k 时：

说明前 i+1 种字母（'a'..'a'+i）总个数 ≥ k，即我们要删掉的 k 个字符都落在这前面这些较小字母的范围内。
令 p = i，这是第 k 个字符所在的那个字母（分界字母）。
然后 k -= a[i-1]：把 k 减去所有比字母 p 更小的字符总数，剩下的 k 表示要从字母 p 本身中删掉多少个。
break
字符 < p：continue，不输出 → 被删除。
字符 > p：直接 cout → 保留。
字符 == p：若是前 k 个（k 未用完），k-- 即删除；k 耗尽后，剩下的该字母 cout 保留
把所有 > p 的字符留着，把 < p 的删掉、再从 p 删 k 个，这样剩余的字符是从小到大尽量保留，且删掉的总数正好 k 个。
保留相对小的、删相对大的 → 前缀字符尽可能小 → 字典序最小
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
using namespace std;

constexpr int N = 26;

int n, k, a[N];
string s;
int main() {
    fast;
    cin >> n >> k >> s;
    rep(i,n) a[s[i]-'a']++;
    for (int i = 1; i < N; i++) a[i] += a[i-1];
    int p = 0;
    rep(i,N) if (a[i] >= k) { p = i; k -= a[i-1]; break; }
    rep(i,n) {
        if (s[i]-'a' < p) continue;
        if (s[i]-'a' > p) cout << s[i];
        else {
            if (k) k--;
            else cout << s[i];
        }
    }
    return 0;
}