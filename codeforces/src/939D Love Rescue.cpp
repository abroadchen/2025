//
// Created by Psy.C on 2026/10/17.
//
/**
cc = pair<char,char>，用于存放一对要输出的字符。
a[N]、b[N]：两个等长字符串（字符数组）。
p[30]：并查集的父指针数组，下标对应字母 0-25
路径压缩的 find：返回 x 的根，同时把路径上的节点直接指向根，加速后续查询
读入 n 与两个字符串 a、b。

初始化并查集：p[i]=i，26 个字母各自成组。

ans = 0：记录"需要建立的连接数"。

对字符串的每个位置 i：

fa = find(a[i]-'a')，fb = find(b[i]-'a')：找出 a[i] 和 b[i] 各自所在集合的根。
if (fa == fb) continue;：如果两个字母已经在同一集合，说明它们已经（直接或间接）被连接，无需再建连接，跳过。
否则：p[fa]=fb（合并两个集合）、ans++（连接数 +1）、把这对字符 (fa+'a', fb+'a') 存入 c。
输出 ans（连接总数），再逐行输出每对要连接/成立的字符对
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define cc pair<char, char>
using namespace std;

constexpr int N = 2e5;


char a[N], b[N];
int p[30];

int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }

vector<cc> c;
int main() {
    fast;
    int n; cin >> n >> a >> b;
    for (int i = 0; i < 26; ++i) p[i] = i;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int fa = find(a[i]-'a'), fb = find(b[i]-'a');
        if (fa == fb) continue;
        p[fa] = fb;
        ans++;
        c.emplace_back(fa+'a', fb+'a');
    }
    cout << ans << '\n';
    for (auto &[fst, snd] : c) cout << fst << ' ' << snd << '\n';
    return 0;
}