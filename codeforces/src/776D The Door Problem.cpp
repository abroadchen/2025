//
// Created by Psy.C on 2026/9/11.
//
/**
标准路径压缩并查集（构造时 f[i]=i 自环）。
find 找根，merge 合并，query 判是否同一集合。
每个实质元素 x 对应两个结点：x 表示"选/开/真"，x+m 表示"不选/关/假"（即反集思想，2-SAT 的补点）。这样把推导关系转成并查集连通
lck[x]：锁 x 的开关状态（0 表示"需合上/选解锁的钥匙"，非 0 表示其他；这里是每把锁被打开的"性质"）。
key[x]：记录是哪把钥匙（开关）第一次出现了锁 x，用来建立它与后续钥匙间的依赖
读入 n（锁数）、m（钥匙/开关数），再读入每把锁的状态 lck[i]
对于每把钥匙/开关 i 的列表里出现的锁 x——
若 key[x]==0（这把锁 x 第一次被某钥匙提到），记录下来 key[x]=i（这把锁与钥匙 i 关联）。
若 key[x]!=0（锁 x 已经被钥匙 key[x] 关联过，现在又出现于钥匙 i），说明锁 x 同时被开关 key[x] 和 i 控制，需要建立这两个开关状态之间的依赖：
若 lck[x]==0：表示两开关要状态相反（推导关系为"key[x] 与 i 互斥"）→ merge(key[x], i+m)（选 key[x] 则不选 i）与 merge(key[x]+m, i)（不选 key[x] 则选 i）——这就是 2-SAT 中"a ⇒ ¬b 且 ¬a ⇒ b"。
否则（lck[x]!=0）：表示两开关要状态相同 → merge(key[x], i) 与 merge(key[x]+m, i+m)（a ⇒ b 且 ¬a ⇒ ¬b）。
换句话说，lck 的高低/类型决定了同一把锁牵涉的两个开关是"must 同"还是"must 反"
一致性检查（无矛盾判定）‍：遍历每个开关 i，若它自己与自己"反集"（i 与 i+m）在同一个并查集集合里，说明推导出了 i 既真又假，产生矛盾 → 输出 NO。
全部检查通过则输出 YES
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5;
struct DSU {
    int f[N+5]{};
    DSU() { for (int i = 1; i <= N; ++i) f[i] = i; }
    int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
    void merge(int x, int y) { f[find(x)] = find(y); }
    int query(int x, int y) { return find(x) == find(y); }
} b;

int lck[(N>>1)+5], key[(N>>1)+5];
int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> lck[i];
    for (int i = 1, k; i <= m; ++i) {
        cin >> k;
        for (int j = 1, x; j <= k; ++j) {
            cin >> x;
            if (key[x] != 0) {
                if (lck[x] == 0) b.merge(key[x], i+m), b.merge(key[x]+m, i);
                else b.merge(key[x], i), b.merge(key[x]+m, i+m);
            } else key[x] = i;
        }
    }
    for (int i = 1; i <= m; ++i)
        if (b.query(i, i+m)) { cout << "NO\n"; return 0; }
    cout << "YES\n";
    return 0;
}