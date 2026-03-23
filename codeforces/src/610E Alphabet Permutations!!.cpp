//
// Created by Psy.C on 2026/3/23.
//
/**
k：字符集大小
s[N]：输入字符串
l, r：节点表示的区间范围
ch[2]：左右子节点指针
lv, rv：区间左端点和右端点的字符
cnt[M][M]：记录每种字符对出现次数的矩阵
sv：懒惰标记，用于区间更新

向上更新函数：合并左右子树的信息，包括字符对统计和跨边界字符对
构造函数：递归构建线段树，叶子节点存储原始字符
区间覆盖操作：将整个区间设置为字符x
懒惰标记下传
区间修改操作：使用懒惰传播优化

操作1：区间修改，将[l,r]区间设置为指定字符
操作2：模式匹配查询，统计目标字符串在当前串中匹配的数量

时间复杂度：
修改操作：O(log n)
查询操作：O(k²)
总体：O(m(log n + k²))
空间复杂度：
O(n log n)，用于存储线段树结构

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5, M = 10+5;

int k;
char s[N];
struct node {
    int l, r;
    node* ch[2];
    int lv, rv, cnt[M][M], sv;
    void push_up() {
        lv = ch[0]->lv, rv = ch[1]->rv;
        for (int i = 0; i < k; ++i)
            for (int j = 0; j < k; ++j)
                cnt[i][j] = ch[0]->cnt[i][j] + ch[1]->cnt[i][j];
        cnt[ch[0]->rv][ch[1]->lv]++;
    }
    node(int l, int r) : l(l), r(r), sv(-1) {
        if (l < r) {
            int mid = l + (r - l) / 2;
            ch[0] = new node(l, mid);
            ch[1] = new node(mid+1, r);
            push_up();
        } else {
            lv = rv = s[r] - 'a';
            memset(cnt, 0, sizeof cnt);
        }
    }
    void push(int x) {
        sv = x; lv = rv = x;
        memset(cnt, 0, sizeof cnt);
        cnt[x][x] = r - l;
    }
    void pushdown() {
        if (sv >= 0) {
            ch[0]->push(sv); ch[1]->push(sv);
            sv = -1;
        }
    }
    void modify(int L, int R, int x) {
        if (L <= l && R >= r) push(x);
        else {
            pushdown();
            if (L <= ch[0]->r) ch[0]->modify(L, R, x);
            if (R >= ch[1]->l) ch[1]->modify(L, R, x);
            push_up();
        }
    }
} *rt;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
inline char rdc() {
    char c = getchar();
    while (isspace(c)) c = getchar();
    return c;
}

int n, m;
char t[M];
int main() {
    fast;
    n = rd(); m = rd(); k = rd(); scanf("%s", s + 1);
    rt = new node(1, n);
    while (m--) {
        int op = rd();
        if (op == 1) {
            int l = rd(), r = rd();
            rt->modify(l, r, rdc() - 'a');
        } else {
            scanf("%s", t);
            int ans = 1;
            for (int i = 0; i < k; ++i)
                for (int j = 0; j <= i; ++j)
                    ans += rt->cnt[t[i]-'a'][t[j]-'a'];
            cout << ans << '\n';
        }
    }
    return 0;
}