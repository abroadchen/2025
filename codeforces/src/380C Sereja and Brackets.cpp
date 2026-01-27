//
// Created by Psy.C on 2026/1/26.
//
/**
* l, r: 区间左右边界
lv: 左括号 '(' 的数量（未匹配的）
rv: 右括号 ')' 的数量（未匹配的）
sum: 匹配的括号对数
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000005
using namespace std;

struct node {
    int l, r, lv, rv, sum;
    node operator+(const node a) const {//合并两个区间
        node h{};//创建新节点
        h.sum = sum + a.sum; h.lv = lv + a.lv; h.rv = rv + a.rv;// 初步合并
        const int n1 = min(lv, a.rv);//可匹配的数量
        h.sum += n1 << 1; h.lv -= n1; h.rv -= n1;//更新匹配对数和剩余括号
        return h;
    }
} st[3*N];//线段树数组

char str[N];//括号字符串的字符数组
node build(const int l, const int r, const int id) {
    if (l == r) {
        if (str[l] == '(') {
            st[id].lv = 1; st[id].rv = 0; st[id].sum = 0;//1个左括号
        } else {
            st[id].lv = 0; st[id].rv = 1; st[id].sum = 0;//设置为1个右括号
        }
        st[id].l = l; st[id].r = r;//设置区间边界
    } else {
        const int mid = (l + r) >> 1;
        // 递归构建并合并
        st[id] = build(l, mid, id<<1) + build(mid+1, r, id<<1|1);
        st[id].l = l; st[id].r = r;
    }
    return st[id];//返回构建的节点
}

node query(const int l, const int r, const int id) {
    if (l == st[id].l && r == st[id].r) return st[id];//区间完全匹配 返回当前节点
    const int mid = (st[id].l + st[id].r) >> 1;
    //查询区间跨越中点
    if (l <= mid && r > mid) return query(l, mid, id<<1) + query(mid+1, r, id<<1|1);
    if (l <= mid && r <= mid) return query(l, r, id<<1);//完全在左半部分
    return query(l, r, id<<1|1);
}

int main() {
    fast; string s; cin >> s;
    strcpy(str + 1, s.data());
    const int n = static_cast<int>(strlen(str + 1));
    build(1, n, 1);
    int m, l, r; cin >> m;
    while (m--) {
        cin >> l >> r;
        cout << query(l, r, 1).sum << '\n';
    }
    return 0;
}