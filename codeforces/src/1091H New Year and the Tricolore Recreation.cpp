//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
np：布尔筛数组（true=合数/被筛掉）。
ok：可行步长集合的"转移标记"bitset，ok[k]=1 表示"存在一种合法走法把局面转移到 SG 值为 k 的状态"。
h[101]：SG 记忆表。h[g] 是一个 bitset，h[g][i]=1 表示"长度 i 的 SG 值 = g"
质数表。
两层：
外层 i 2→N：若 np[i] 为 0（未被筛掉 → 是质数），推进质数表 pr；
否则 continue（合数跳过）。
内层：把所有 i 的倍数 j = 2i, 3i, ... 标记为合数 np.set(j)。
这就是经典埃氏筛/线性筛骨架，最终 pr 装满 ≤N 的所有质数
第一步：把所有质数本身放进取集合 ok（质数可作为一次走法拿走的长度）。
第二步：双重循环把两个质数的乘积 pr[i]*pr[j]（i≤j，允许相同，即 p² 也算）也放进 ok。
1ll*...>N 时 break：乘积超过上限就停（因为外层 i 增加乘积必然更大，可 break 剪枝）。
第三步 ok.reset(t)：把题目给的第四输入 t 这个长度对应的位清 0——表示 t 这个长度不能作为合法步长（题目特意排除某长度）。
t 是 main 里读的第二输入。
于是 ok 就是一个 bitset，ok[k]=1 ⟺ k 是合法可取的步长（质数或两质数之积，且 ≠ t）
h[g][i] 表示"长度 i 的 SG 值 = g"。当前若 h[sg[i]][i] 已有值（内存了），就把 sg[i] 递增，直到 h[sg[i]][i]==0 → 找到第一个未被使用的 g 作为该长度的新 SG 值（mex 逻辑）
ok << i：把"可行步长集合"整体左移 i 位 → 得到"长度 i 能转移到哪些 SG 状态"的标记。
h[sg[i]] |= (ok<<i)：把"由长度 i 可达的 SG 集合"归入 SG 值为 sg[i] 的桶里，供后续长度借用以快速跳 mex。
读入 n（区间个数）和 t（被禁步长）。
pre() 构造可行集合，get() 预计算 1..N 的 SG 表。
读入三个点 a、b、c（把它们看成数轴上三段，其中两段被用到：b-a 和 c-b）。
对每段长度取 SG 值并全部异或（Nim 和）。tot 就是所有独立子游戏的 SG 异或和
若 tot != 0：先手 Alice 必胜，输出 "Alice\nBob"（先输出胜者名 + 换行 + 败者名，即交互输出要求两行）。
若 tot == 0：后手 Bob 必胜，输出 "Bob\nAlice"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

constexpr int N = 2e5;

bitset<N+1> np, ok, h[101];
vector<int> pr;
void init() {
    for (int i = 2; i <= N; i++) {
        if (!np[i]) pr.push_back(i); else continue;
        for (int j = i<<1; j <= N; j += i) np.set(j);
    }
}

int t;
void pre() {
    for (int i : pr) ok.set(i);
    rep(i,pr.size()) for (int j = i; j < pr.size(); j++) {
        if (1ll*pr[i]*pr[j] > 1ll*N) break;
        ok.set(pr[i]*pr[j]);
    }
    ok.reset(t);
}

int sg[N+1];
void get() {
    for (int i = 1; i <= N; i++) {
        while (h[sg[i]][i]) sg[i]++;
        h[sg[i]] |= ok<<i;
    }
}

int main() {
    fast;
    init();
    int n, tot = 0; cin >> n >> t; pre(); get();
    while (n--) {
        int a, b, c; cin >> a >> b >> c;
        tot ^= sg[b-a]^sg[c-b];
    }
    cout << (tot ? "Alice\nBob" : "Bob\nAlice");
    return 0;
}