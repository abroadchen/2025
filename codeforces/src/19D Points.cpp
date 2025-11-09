//
// Created by Psy.C on 2025/9/18.
//
/*
 *
*T: 操作数量
opt[maxn]: 操作类型数组（1=add, 2=remove, 3=find）
x[maxn], y[maxn]: 每个操作的参数
b[maxn]: 用于离散化的数组
cnt: 离散化后不同x值的数量
zd[maxn<<2]: 线段树数组，存储每个区间内的最大y值
s[25]: 读取操作类型字符串
st[maxn]: 每个离散化x值对应的set，存储y值
 *
 *
 *
 *
 */

#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;

const int maxn = 2e5 + 5;
int T, opt[maxn], x[maxn], y[maxn], b[maxn], cnt, zd[maxn<<2];
char s[25];
set<int> st[maxn];

//向上传递函数：更新父节点为两个子节点的最大值
void pushup(int rt) {
    zd[rt] = max(zd[rt << 1], zd[rt << 1 | 1]);
}

//单点更新：将位置k的值更新为max(原值, v)
void update(int k, int v, int l, int r, int rt) {
    if (l == r) {
        zd[rt] = max(zd[rt], v);
        return;
    }

    int mid = (l + r) >> 1;
    if (k <= mid) update(k, v, l, mid, rt << 1);
    else update(k, v, mid + 1, r, rt << 1 | 1);
    pushup(rt);
}


//单点修改：将位置k的值直接改为v
void change(int k, int v, int l, int r, int rt) {
    if (l == r) {
        zd[rt] = v;
        return;
    }

    int mid = (l + r) >> 1;
    if (k <= mid) change(k, v, l, mid, rt << 1);
    else change(k, v, mid + 1, r, rt << 1 | 1);
    pushup(rt);
}

//查找函数：找到位置≥pos且对应set中存在>y值的最小x（离散化后的索引）
int find(int pos, int v, int l, int r, int rt) {
    if (pos > cnt) return 0;
    if (zd[rt] <= v) return 0;
    if (l == r) return l;

    int mid = (l + r) >> 1;
    if (pos > mid) return find(pos, v, mid + 1, r, rt << 1 | 1);
    else {
        int res = 0;
        res = find(pos, v, l, mid, rt << 1);
        if (res < pos) res = find(pos, v, mid + 1, r, rt << 1 | 1);
        return res;
    }
}


int main() {
    scanf("%d",&T);
    for (int i = 1; i <= T; ++i) {
        scanf("%s", s + 1);
        if (s[1] == 'a') opt[i] = 1;
        else if (s[1] == 'r') opt[i] = 2;
        else opt[i] = 3;

        scanf("%d%d", &x[i], &y[i]);
        b[++cnt] = x[i];
    }
    sort(b + 1, b + 1 + cnt);
    cnt = unique(b + 1, b + 1 + cnt) - (b + 1);

    for (int i = 1; i <= T; ++i) {
        int t = lower_bound(b + 1, b + 1 + cnt, x[i]) - b;

        if (opt[i] == 1) {
            st[t].insert(y[i]);
            update(t, y[i], 1, cnt, 1);
        } else if (opt[i] == 2) {
            set<int>::iterator it;
            it = st[t].lower_bound(y[i]);
            st[t].erase(*it);
            if (!st[t].size()) change(t, 0, 1, cnt, 1);
            else change(t, *st[t].end(), 1, cnt, 1);
        } else {
            int res = find(t + 1, y[i], 1, cnt, 1);
            if (res == 0) puts("-1");
            else {
                set<int>::iterator it;
                it = st[res].upper_bound(y[i]);
                printf("%d %d\n", b[res], *it);
            }
        }
    }
    return 0;
}