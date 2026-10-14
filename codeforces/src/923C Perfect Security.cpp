//
// Created by Psy.C on 2026/10/14.
//
/**
一个 01 字典树节点，含两个儿子 son[0], son[1]（分别对应当前 bit 为 0/1）和一个计数 cnt。
L=31 表示处理 31 个二进制位（int 最高位）
从根往下，按 x 的二进制位从高位到低位走。
每个经过节点 cnt += k：k=+1 插入，k=-1 删除。
p 递减直到 0（递归 31 层）
经典贪心求最大异或：为了让 x^y 最大，每一高位尽量让 y 与 x 相反（异或得 1）。
0^chk：与 x 该位相反的位；如果该方向有节点（cnt>0）就走它，否则被迫走相同位方向。
递归把逐位选出的 y 组合出来（(位)<<(p-1) 累加），返回那个与 x 异或最大的数 y。
注意函数名虽叫 query，实际找的是使异或最大的数（贪心取相反位
先把全部 p[i] 插入 Trie。
逐个处理 a[i]：从当前的 p 集合中找与 a[i] 异或最大的数 x（贪心），输出 x^a[i]，然后把这个数 x 从 Trie 中删掉（不可重复使用）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 9e6+10, L = 31;

struct node { int son[2], cnt; } tr[N];

int cnt;
void update(int &v, int x, int p, int k) {
    if (!v) v = ++cnt; tr[v].cnt += k;
    if (!p) return;
    int c = (x>>(p-1))&1;//取 x 第 p 位
    update(tr[v].son[c], x, p-1, k);
}
int query(int v, int x, int p) {
    if (!p) return 0;
    int chk = (x>>(p-1))&1;
    if (tr[tr[v].son[0^chk]].cnt)
        return ((0^chk)<<(p-1)) + query(tr[v].son[0^chk], x, p-1);
    return ((1^chk)<<(p-1)) + query(tr[v].son[1^chk], x, p-1);
}

int n, a[N], p[N], rt;
int main() {
    fast;
    cin >> n;
    rep(i,1,n) cin >> a[i];
    rep(i,1,n) {
        cin >> p[i];
        update(rt, p[i], L, 1);//把所有 p 插入 Trie
    }
    rep(i,1,n) {
        int x = query(rt, a[i], L);
        cout << (x^a[i]) << ' ';
        update(rt, x, L, -1);//用掉后删除 x
    }
    return 0;
}