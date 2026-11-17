//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
两组 (mod, base)，分别是 (1e9+7, 73) 和 (998244353, 47)，用于双哈希减少碰撞几率
st：s1 中出现过的字母集合掩码。
v, v1：对 s 某个前缀的双哈希值。
id：原始输入编号。
operator<：按 v → v1 → st 三级排序，使相同元素相邻，便于分组
G[i]：第 i 组的成员 id 列表
读入 s、s1。
st 用位掩码记录 s1 中出现了哪些字母：每个字母对应一位，1<<p。
存下 st 和 id
从 s 的末尾向前扫描，找到第一个不在 s1 中出现过的字母的位置 f。

if ((st&(1<<p)) == 0)：若字母 p 在 s1 中没出现过（对应位为 0），记录位置 j 为 f 并 break。
也就是说 f 是"从 s 尾部往前看，首个不属于 s1 字母集的字符下标"
对 s 的前缀 [0..f]（到首个外来字符为止）做双哈希：

p = s[j]-'a'+1：字母转成 1..26 的数值（+1 避免 0 造成哈希歧义）。
v：base=73, mod=1e9+7 的滚动哈希。
v1：base=47, mod1=998244353 的第二组滚动哈希。
结果存入 v, v1。
总结每个元素特征：(st, v, v1) = s1 字母集 + s 到首个非 s1 字母为止的前缀双哈希
按 v→v1→st 排序，相同特征聚到一起。
l 指向当前组开头，r 向右扩展。
当 a[l] 与 a[r] 的三项特征全部相等时，把 a[r].id 加入当前组 G[cnt]，r 前进。
一旦不相等，说明新组开始：l = r，cnt++。
循环结束，cnt 是组数
第一行输出组数。
每组输出：该组元素个数 + 组内各元素原始 id（空格分隔，行尾换行）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
using namespace std;

constexpr int N = 1e5+10, mod = 1e9+7, base = 73, mod1 = 998244353, base1 = 47;

struct node {
    int st, v, v1, id;
    bool operator<(const node& o) const {
        if (v == o.v) {
            if (v1 == o.v1) return st < o.st;
            return v1 < o.v1;
        }
        return v < o.v;
    }
} a[N];

vector<int> G[N];
int main() {
    fast;
    int n; cin >> n;
    rep(i,1,n) {
        string s, s1; cin >> s >> s1;
        int st = 0;
        rep(j,0,s1.size()-1) { int p = s1[j] - 'a'; st |= 1<<p; }
        a[i].st = st; a[i].id = i;
        int f = -1;
        for (int j = s.size()-1; j >= 0; j--) {
            int p = s[j] - 'a';
            if ((st&(1<<p)) == 0) { f = j; break; }
        }
        int v = 0, v1 = 0;
        rep(j,0,f) {
            int p = s[j] - 'a' + 1;
            v = 1ll*base*v%mod + p; v %= mod;
            v1 = 1ll*base1*v1%mod1 + p; v1 %= mod1;
        }
        a[i].v = v; a[i].v1 = v1;
    }
    sort(a+1,a+n+1);
    int l = 1, r = 1, cnt = 1;
    while (r <= n) {
        if (a[l].v == a[r].v && a[l].v1 == a[r].v1 && a[l].st == a[r].st) {
            G[cnt].push_back(a[r].id); r++;
        } else l = r, cnt++;
    }
    cout << cnt << '\n';
    rep(i,1,cnt) {
        cout << G[i].size() << ' ';
        rep(j,0,G[i].size()-1)
            cout << G[i][j] << (j==G[i].size()-1?'\n':' ');
    }
    return 0;
}