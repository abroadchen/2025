//
// Created by Psy.C on 2026/10/7.
//
/**
a[i][j]：k 个属性（i），n 个基础列（j），属性值在 1..1e5。
s[i] 的长度 N=4100 ≥ 2^k，所以 k ≤ 12（2^12=4096）。bitset 的位下标表示"属性掩码 S"（0..2^k−1），对应哪些属性被选中
把前 k 个 s[i] 设成"单位掩码指示位"：

s[i][S] = 1 ⟺ 掩码 S 包含属性 i。
也就是说，原始列 i 表示"属性 i 这个原子谓词"——当查询掩码 S 里包含属性 i 时为真
每次操作分配一个新的"列号 idx"。
s[x] | s[y]：新谓词 = 旧谓词的 OR。
s[x] & s[y]：新谓词 = 旧谓词的 AND。
因为是逐位的真值表（对每个掩码 S 独立做布尔运算），所以对任意属性子集 S，组合谓词的真值 = 成分谓词真值的 OR/AND，完全符合布尔表达式的语义
把第 y 列（物品）的 k 个属性值排序，从大到小逐个当作候选阈值 p[i]。
对每个阈值，算出掩码 S = {j | a[j][y] ≥ p[i]}（第 y 列中"属性值不低于该阈值"的属性集）。
查列 x（那个由 AND/OR 构造出来的谓词）的真值表 s[x][S]：若在"值≥阈值的属性集 S"上为真，就输出 p[i] 并停止。
因为从大到小枚举，第一个命中的就是满足条件的最大阈值（若全不成立则不输出/输出边界默认）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 4100, M = 1e5+5;

int a[15][M];
bitset<N> s[M];
int main() {
    fast;
    int n, k, q; cin >> n >> k >> q;
    for (int i = 1; i <= k; ++i)
        for (int j = 1; j <= n; ++j) cin >> a[i][j];
    for (int i = 1; i <= k; ++i)
        for (int j = 0; j < 1<<k; ++j) {
            if (j>>(i-1)&1) s[i][j] = 1;
            else s[i][j] = 0;
        }
    int idx = k;
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int x, y; cin >> x >> y;
            s[++idx] = s[x]|s[y];
        } else if (t == 2) {
            int x, y; cin >> x >> y;
            s[++idx] = s[x]&s[y];
        } else {
            int x, y; cin >> x >> y;
            vector<int> p;
            for (int i = 1; i <= k; ++i) p.push_back(a[i][y]);//第 y 列的 k 个属性值
            ranges::sort(p);
            for (int i = k-1; i >= 0; --i) {
                int S = 0;
                for (int j = 1; j <= k; ++j)
                    if (a[j][y] >= p[i]) S|=1<<(j-1);
                if (s[x][S]) { cout << p[i] << '\n'; break; }
            }
        }
    }
    return 0;
}