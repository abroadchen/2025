//
// Created by Psy.C on 2026/9/18.
//
/**
sa[ ]：后缀自动机的节点数组，nxt[26] 是转移边，st 是该状态对应的最长串长度（maxlen），pre 是后缀链接（link/parent），rt 是该状态的 endpos 集合大小（被统计的计数）‍。
N<<1：自动机节点数不超过 2*串长，故开双倍空间。
lst / now / top / root / lson：构建时用的游标
新建状态 now，其最长长度 = 上一个状态 +1，rt 初始 1（代表这个新终态 endpos 计数）
沿后缀链接向上，给所有没有字符 x 转移的状态补上指向 now 的转移
若走到根还没有，则 now 的 pre 指向根
当 nxt[x] 指向的状态 lson 长度不匹配时，克隆出一个新节点 top，并重定向后继链接与转移边。这是保证 SAM 线性的关键
按 st（maxlen）做基数排序，得到拓扑序 p[1..top]（maxlen 大的在前）
沿后缀链接逆拓扑累加 rt：每个状态的 rt 是其所有后缀链接子状态 rt 之和——这得到每个状态对应的 endpos 集合大小（即该状态代表的所有子串在原串中出现的总次数相关量）
累加统计：对每个状态 i 贡献 rt^2 * (maxlen(i) - maxlen(pre(i)))
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 1e5+10;
struct node { int nxt[26], st, pre, rt; } sa[N<<1];

int lst, now(1), top(1), root(1), lson;
void ex(int x) {
    lst = now; now = ++top;
    sa[now].st = sa[lst].st+1; sa[now].rt = 1;
    for (; !sa[lst].nxt[x] && lst; lst = sa[lst].pre)
        sa[lst].nxt[x] = now;
    if (!lst) sa[now].pre = root;
    else {
        lson = sa[lst].nxt[x];
        if (sa[lson].st == sa[lst].st+1) sa[now].pre = lson;
        else {
            sa[++top] = sa[lson]; sa[top].rt = 0;
            sa[top].st = sa[lst].st+1;
            sa[lson].pre = sa[now].pre = top;
            for (; sa[lst].nxt[x] == lson && lst; lst = sa[lst].pre)
                sa[lst].nxt[x] = top;
        }
    }
}

int len, cnt[N], p[N<<1];
ll ans;
void get() {
    for (int i = 1; i <= len; ++i) cnt[i] = 0;
    for (int i = 1; i <= top; ++i) cnt[sa[i].st]++;
    for (int i = 1; i <= len; ++i) cnt[i] += cnt[i-1];
    for (int i = top; i >= 1; --i) p[cnt[sa[i].st]--] = i;
    for (int i = top; i >= 1; --i) sa[sa[p[i]].pre].rt += sa[p[i]].rt;
    for (int i = 1; i <= top; ++i)
        ans += 1ll*sa[i].rt*sa[i].rt*(sa[i].st-sa[sa[i].pre].st);
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

char str[N];
int main() {
    int q; rd(q);
    while (q--) {
        memset(sa, 0, sizeof(sa));
        top = root = now = 1; ans = 0;
        scanf("%s", str+1);
        len = strlen(str+1);
        for (int i = 1; i <= len; ++i) ex(str[i]-'a');
        get();
        printf("%lld\n", ans);
    }
    return 0;
}