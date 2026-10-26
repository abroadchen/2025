//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
四种门：0=AND、1=NAND、2=OR、3=NOR。
返回两个输入 x,y 经过该门运算后的布尔结果。
注意 op^1：AND↔NAND（0/1 互补），OR↔NOR（2/3 互补），即"取反版门"
解析一行输入：第一个单词是门类型（and/nand/or/nor），第二个单词是表达式字符串 s2（形如 x_ab）。

判断门类型的关键：

s1[0]=='a'："and" → op=0。
s1[1]=='a'："nand" → op=1。
s1[0]=='o'："or" → op=2。
否则（"nor"）→ op=3。
解析两个输入 x, y：

s2 形如 x_pq，其中 p、q 是标识。代码用双重循环找到第一个 'x' 的位置赋给 x，再找到第二个 'x' 的位置赋给 y。
也就是说，把 s2 中两个变量的下标位置存进 x、y（两者是字符串中的位置索引，代表变量编号）
读入 m 个门定义到 a[]，k 个"目标/约束"门到 b[]
b[i].x、b[i].y 是约束门引用的两个门编号。取出这两个门各自的输入变量，放入 v。
（去重排序后得到本约束涉及的独立输入变量集合。）
lim = 2^(变量个数)，S 从 0 到 lim，遍历所有赋值组合。
get(a)：返回变量 a（通过二分找到在 v 中的下标）在赋值 S 下的布尔值
先算门 a[b[i].x] 的输出：cal(a[b[i].x].op, x1, x2)。
再算门 a[b[i].y] 的输出：cal(a[b[i].y].op, x3, x4)。
最后算约束门本身：cal(b[i].op, 输出1, 输出2)。
把这个布尔值填入 r1[i] 的对应 bit（用位掩码记录所有赋值下该约束门的真值表）。
含义：r1[i] 是约束门 b[i] 的真值表压缩（每一位 = 一种赋值下的输出）
把所有门换成互补门（op^1，AND→NAND 等），再算一遍。
r2[i] 是互补电路的真值表。
所以 r1[i] 是"原电路"该约束点的真值，r2[i] 是"全部取反后"的真值。二者用于判断约束门的"原 / 互补"匹配情况
r1[i] 是二进制掩码，==1 表示只有最低位（赋值全为 0 的情况）输出 1，其它赋值输出 0 → 该门是 AND 型（全 1 才 1）……其实具体要看变量个数。==1 说明真值表只有一种情况为 1。
这里的计数逻辑依赖题目定义：r==1 表示该约束在某种匹配下"能满足"，r==2 表示另一种情况
统计那些在取反电路下真值为 1 的约束门数量 tot。
若其中存在某门原电路 r1[i]==2，则 flg=1，ans = tot
同理统计 r1==1 的数量，并检查是否出现互补情况。
ans 取两次中较大者（对应"原/互补实现"两种匹配方案里能更多判定的门数）
若 ans 非 0，输出 k - ans（未能判定的门数，或需翻转个数）；否则输出 -1。
具体输出含义依赖原题：ans 是可确定匹配的门数，k-ans 是剩下无法确定的，输出它；无解输出 -1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i = 0; i < n; ++i)
using namespace std;

constexpr int N = 50;

bool cal(int op, bool x, bool y) {
    if (op == 0) return x&&y;
    if (op == 1) return !(x&&y);
    if (op == 2) return x||y;
    return !(x||y);
}

char s1[10], s2[N+5];
struct node {
    int op, x, y;
    void read() {
        cin >> s1 >> s2;
        if (s1[0] == 'a') op = 0;
        else if (s1[1] == 'a') op = 1;
        else if (s1[0] == 'o') op = 2;
        else op = 3;
        int l = strlen(s2);
        for (x = 0; x < l; ++x) if (s2[x] == 'x')
            for (y = x+1; y < l; ++y) if (s2[y] == 'x') return;
    }
} a[N], b[N];


int n, m, k, i, r1[N], r2[N], ans;
vector<int> v;
int main() {
    fast;
    cin >> n >> m >> k;
    rep(i,m) a[i].read();
    rep(i,k) b[i].read();
    rep(i,k) {
        v = {a[b[i].x].x, a[b[i].x].y, a[b[i].y].x, a[b[i].y].y};
        ranges::sort(v);
        v.resize(ranges::unique(v).begin() - v.begin());
        int S = 0, lim = 1<<v.size();
        auto get = [&](int a) -> bool {
            return S>>(ranges::lower_bound(v, a) - v.begin())&1;
        };
        for (; S < lim; ++S) {
            bool x1 = get(a[b[i].x].x), x2 = get(a[b[i].x].y), x3 = get(a[b[i].y].x), x4 = get(a[b[i].y].y);
            r1[i] |= 1<<cal(b[i].op, cal(a[b[i].x].op,x1,x2), cal(a[b[i].y].op,x3,x4));
            r2[i] |= 1<<cal(b[i].op^1, cal(a[b[i].x].op^1, x1,x2), cal(a[b[i].y].op^1, x3,x4));
        }
    }
    int tot = 0; bool flg = 0;
    rep(i,k) if (r2[i] == 1) { ++tot; flg |= r1[i] == 2; }
    if (flg) ans = tot;
    tot = 0; flg = 0;
    rep(i,k) if (r1[i] == 1) { ++tot; flg |= r2[i] == 2; }
    if (flg) ans = max(ans, tot);
    cout << (ans ? k-ans : -1) << '\n';
    return 0;
}