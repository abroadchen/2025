//
// Created by Psy.C on 2026/10/12.
//
/**
15 = 0b00001111
51 = 0b00110011
85 = 0b01010101
这三个分别就是"只依赖 z 位 / 只依赖 y 位 / 只依赖 x 位"的真值表掩码（约化后的 x,y,z）。结合 ! 与 & 与 | 可组合出任意 8 位函数。
我们想对每个真值表掩码 i∈[0,255]，求一个字典序最小、长度尽量短的表达式字符串。

用 优先队列（priority_queue）+ 访问标记，类似 Dijkstra：优先级队列按"字典序最大"（因为 cmp 返回"s 是否比 t 更好"，而优先队列的 top 是"按 < 排序的最大者"），每取出一个状态，尝试用三个运算把它扩展成其他真值表，若得到更优表达式则更新并入队
判断 s 是否比 t 更好：长度更短则更好；长度相同则字典序更大更好
node：一个 DP 状态。o 是"运算层级/种类"（0=最终?，1=或表达式 |, 2=与表达式 &, 3=原子/取反 ! 的原语），x 是真值表掩码，s 是当前最优表达式。
operator< 用 cmp 定义优先级：越优（短/字典序大）的元素在优先队列里越靠前（因为默认 priority_queue 是大顶堆，a < b 表示 b 更优先，所以要让"更优"的成为 top，operator< 返回 cmp(s,o.s) 判断自己是否不如对方…需要仔细看）
inf=1e3，s[1..3][j] 初始是一长串 #，作为"未找到/无限长"的占位（'#' 字典序大、长度也长，cmp 认为它"不够好"，会被更短的替换）。

三种运算扩展：

t.o == 1（或表达式，|）‍：

先把该表达式套上括号升级为原子：若 s[3][t.x] 比 '(' + t1 + ')' 更长，则更新为 '('+t1+')'（因为括号在原语层级是需要的）。
枚举所有掩码 i，用 s[2][i]（一个与表达式）做 | 组合：comb(t1, t2, '|') 生成 s[1][t.x|i]（或表达式），若更优则更新并入队。
t.o == 2（与表达式，&）‍：

先升级为或层级？不对——s[2][..] 与 s[1][..]：与比或优先级高，所以直接把与表达式当或用（常见优先级 原子>与>或）。若 s[1][t.x] 比当前 t1 更差则更新。
枚举 i，用 s[3][i]（原子）做 &：comb(t1, t2, '&') 产生 s[2][t.x&i]。
t.o == 3（原子/取反）‍：

原子可直接当作与表达式用：更新 s[2][t.x]。
取反：'!'+t1 对应掩码 N-1-t.x（N-1=255，取反就是按位取反），更新 s[3][N-1-t.x]
三类表达式 s[1][i](或)、s[2][i](与)、s[3][i](原子/取反) 中，选出"不比另外两者差"的那一个作为该真值表的最终整体表达式 s[0][i]。（因为一个真值表既可能整体是或表达式，也可能是与表达式，也可能是单个原子，取最优者。）
每个测试是一个长度为 8 的 0/1 串（真值表），把它读成二进制数 x（x<<1 | bit，从左到右每位）；getchar 跳过分隔符/换行。
输出 s[0][x]，即该真值表对应的最小表达式
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 256, inf = 1e3;

bool cmp(const string& s, const string& t) {
    if (s.size() != t.size()) return s.size() > t.size();
    return s > t;
}

struct node {
    int o, x;
    string s;
    bool operator<(const node& o) const { return cmp(s, o.s); }
};

string comb(const string& s, const string& t, const char c) {
    string A = s + c + t, B = t + c + s;
    return A < B ? A : B;
}

string s[4][N];
priority_queue<node> q;
bool vis[4][N];
void init() {
    for (int i = 1; i <= 3; ++i)
        for (int j = 0; j < N; ++j) {
            int x = inf;
            while (x--) s[i][j] += '#';
        }
    s[3][15] = "x"; q.push({.o = 3, .x = 15, .s = "x"});
    s[3][51] = "y"; q.push({.o = 3, .x = 51, .s = "y"});
    s[3][85] = "z"; q.push({.o = 3, .x = 85, .s = "z"});
    while (!q.empty()) {
        auto t = q.top(); q.pop();
        if (vis[t.o][t.x]) continue;
        vis[t.o][t.x] = 1;
        string t1 = s[t.o][t.x];
        if (t.o == 1) {
            if (cmp(s[3][t.x], '('+t1+')'))
                s[3][t.x] = '('+t1+')', q.push({.o = 3, .x = t.x, .s = s[3][t.x]});
            for (int i = 0; i < N; ++i) {
                string t2 = s[2][i];
                if (cmp(s[1][t.x|i], comb(t1, t2, '|')))
                    s[1][t.x|i] = comb(t1, t2, '|'), q.push({.o = 1, .x = t.x|i, .s = s[1][t.x|i]});
            }
        } else if (t.o == 2) {
            if (cmp(s[1][t.x], t1))
                s[1][t.x] = t1, q.push({.o = 1, .x = t.x, .s = s[1][t.x]});
            for (int i = 0; i < N; ++i) {
                string t2 = s[3][i];
                if (cmp(s[2][t.x&i], comb(t1, t2, '&')))
                    s[2][t.x&i] = comb(t1, t2, '&'), q.push({.o = 2, .x = t.x&i, .s = s[2][t.x&i]});
            }
        } else {
            if (cmp(s[2][t.x], t1))
                s[2][t.x] = t1, q.push({.o = 2, .x = t.x, .s = s[2][t.x]});
            if (cmp(s[3][N-1-t.x], '!'+t1))
                s[3][N-1-t.x] = '!'+t1, q.push({.o = 3, .x = N-1-t.x, .s = s[3][N-1-t.x]});
        }
    }
    for (int i = 0; i < N; ++i) {
        if (!cmp(s[1][i], s[2][i]) && !cmp(s[1][i], s[3][i])) s[0][i] = s[1][i];
        if (!cmp(s[2][i], s[1][i]) && !cmp(s[2][i], s[3][i])) s[0][i] = s[2][i];
        if (!cmp(s[3][i], s[1][i]) && !cmp(s[3][i], s[2][i])) s[0][i] = s[3][i];
    }
}

int main() {
    init();
    int T; cin >> T;
    while (T--) {
        int x = 0;
        char c = getchar();
        while (!isdigit(c)) c = getchar();
        while (isdigit(c)) x = x<<1|c-'0', c = getchar();
        cout << s[0][x] << '\n';
    }
    return 0;
}