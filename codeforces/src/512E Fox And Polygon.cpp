//
// Created by Psy.C on 2026/2/27.
//
/**
n：节点数
a[N], b[N], c[N], d[N]：存储边的端点
ans1[N], ans2[N], ans3[N], ans4[N]：存储结果
k, kk：结果计数器
st[N], st2[N]：集合数组，存储每个节点的相邻节点
it：set迭代器

st[a[i]]包含a[i]的所有相邻节点
从节点2到n依次处理
对于每个节点i，不断取出最大的相邻节点now
删除这条边
找到下一个最大相邻节点nxt（如果没有则设为i+1）
将nxt加入节点1的相邻列表
记录边：i→now
记录边：1→nxt

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e4+1;

int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, a[N], b[N], c[N], d[N], ans1[N], ans2[N], k, ans3[N], ans4[N], kk;
set<int> st[N], st2[N];
set<int>::iterator it;
int main() {
    fast;
    n = read();
    for (int i = 1; i <= n-3; ++i) {
        a[i] = read(); b[i] = read();
        if (a[i] > b[i]) swap(a[i], b[i]);
        st[a[i]].insert(b[i]);
    }
    for (int i = 1; i <= n-3; ++i) {
        c[i] = read(); d[i] = read();
        if (c[i] > d[i]) swap(c[i], d[i]);
        st2[c[i]].insert(d[i]);
    }
    for (int i = 2; i <= n; ++i) {
        while (!st[i].empty()) {
            it = st[i].end(); --it;
            int now = *it, nxt;
            st[i].erase(now);
            if (st[i].empty()) nxt = i + 1;
            else {
                it = st[i].end(); --it;
                nxt = *it;
            }
            st[1].insert(nxt);
            ans1[++k] = i; ans2[k] = now;
        }
    }
    for (int i = 2; i <= n; ++i) {
        while (!st2[i].empty()) {
            it = st2[i].end(); --it;
            int now = *it, nxt;
            st2[i].erase(now);
            if (st2[i].empty()) nxt = i + 1;
            else {
                it = st2[i].end(); --it;
                nxt = *it;
            }
            st2[1].insert(nxt);
            ans3[++kk] = 1; ans4[kk] = nxt;
        }
    }
    cout << k + kk << '\n';
    for (int i = 1; i <= k; ++i) cout << ans1[i] << ' ' << ans2[i] << '\n';
    for (int i = kk; i >= 1; --i) cout << ans3[i] << ' ' << ans4[i] << '\n';
    return 0;
}