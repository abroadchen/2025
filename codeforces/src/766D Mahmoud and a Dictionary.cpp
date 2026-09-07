//
// Created by Psy.C on 2026/9/7.
//
/**
每个单词要占两个节点（正节点和反节点，见后），所以数组翻倍
路径压缩版 find：第一段循环找根 r；第二段循环把路径上所有节点直接挂到根上（压缩路径），使后续查找更快
合并：把 y 所在集合的根挂到 x 所在集合的根下（fa[ty]=tx），实现两集合合并
m：关系语句条数。
q：查询条数。
mp：从单词（字符串）到编号的映射
读入 xx（关系类型 1 或 2）、两个单词 s、ss。
yy、zz 是这两个单词的编号。
节点设计（关键）‍：每个单词编号 id 对应两个节点：

节点 id 表示"单词本身"；
节点 id + n 表示"该单词的反义词/对立面"（种类并查集的经典"拆点"技巧
冲突检查：如果 yy 和 zz 的反义词节点 zz+n 在同一集合（即 yy 的反≠zz 没成立，矛盾），或 zz 和 yy+n 在同一集合，则说明两词其实是"反义"矛盾，输出 NO（不能是近义词）。
否则：输出 YES，并合并：yy↔zz（正节点同类）、yy+n↔zz+n（反节点同类）。近义词的含义就是：正跟正同、反跟反同
冲突检查：若 yy 与 zz 正节点同集合，或反节点同集合，说明他们其实是"近义"矛盾，输出 NO。
否则：输出 YES，合并 yy↔zz+n（一个词的正 = 另一个词的反）、yy+n↔zz（交叉反义）。反义词 = 正反交叉相连
输出 1：xx 与 yy 正节点同集合，或反节点同集合 → 是近义词（同类）‍。
输出 2：xx 与 yy 的反节点同集合（或 yy 与 xx 反节点同集合）→ 是反义词（异类）‍。
输出 3：两者都不符合 → 关系未知/无关
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5;

int fa[N<<1], n;
void init() {
    for (int i = 0; i <= 2*n; ++i)
        fa[i] = i;
}
int find(int x) {
    int r = x;
    while (r != fa[r]) r = fa[r];
    int i = x, j;
    while (i != r) {
        j = fa[i]; fa[i] = r; i = j;
    }
    return r;
}
void uni(int x, int y) {
    int tx = find(x), ty = find(y);
    if (tx != ty) fa[ty] = tx;
}

int m, q;
map<string, int> mp;
int main() {
    fast;
    cin >> n >> m >> q; init();
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        mp[s] = i;
    }
    for (int i = 1, xx; i <= m; ++i) {
        string s, ss; cin >> xx >> s >> ss;
        int yy = mp[s], zz = mp[ss];
        if (xx == 1) {
            if (find(yy) == find(zz+n) || find(zz) == find(yy+n)) cout << "NO\n";
            else {
                cout << "YES\n";
                uni(yy, zz); uni(yy+n, zz+n);
            }
        } else if (xx == 2) {
            if (find(yy) == find(zz) || find(yy+n) == find(zz+n)) cout << "NO\n";
            else {
                cout << "YES\n";
                uni(yy, zz+n); uni(yy+n, zz);
            }
        }
    }
    for (int i = 1, xx, yy; i <= q; ++i) {
        string s, ss; cin >> s >> ss;
        xx = mp[s], yy = mp[ss];
        if (find(xx) == find(yy) || find(xx+n) == find(yy+n)) cout << "1\n";
        else if (find(xx) == find(yy+n) || find(yy) == find(xx+n)) cout << "2\n";
        else cout << "3\n";
    }
    return 0;
}