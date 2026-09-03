//
// Created by Psy.C on 2026/9/2.
//
/**
a[i]：位置 i 的操作。a[i].first 操作类型，a[i].second 入栈值。
st[id][...]：块内部构建出的"入栈序列"（把块内所有入栈操作按顺序存起来，同时块内出栈抵消），tp[id] 是栈顶指针。
dl[id]：块内"多余出栈"数量——即块内 0（出栈）操作多于入栈操作，多出来的这些出栈需要消除前面块的栈元素。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5, M = 400;

int dl[M+5], tp[M+5], n, st[M+5][M+5];
ii a[N+5];
inline void build(int id) {
    dl[id] = tp[id] = 0;
    for (int i = (id-1)*M+1; i <= min(id*M, n); ++i) {
        if (~a[i].first) {//first != -1，即该位置被设置了
            if (a[i].first) st[id][++tp[id]] = a[i].second;//first > 0：入栈操作
            else {//first == 0：出栈操作
                if (!tp[id]) dl[id]++;//块内栈空，多余出栈累加
                else tp[id]--;//否则抵消块内栈顶
            }
        }
    }
}

stack<ii> s;
int b[N+5];
inline int solve() {
    while (!s.empty()) s.pop();
    for (int i = 1; i <= b[n]; ++i) {//遍历所有块
        int dt = dl[i];
        //用本块的多余出栈 dl[i] 去弹出全局栈 s 顶部
        while (!s.empty() && dt) {
            if (s.top().second > dt) {//栈顶一块只被弹掉一部分
                auto t = s.top(); s.pop();
                t.second -= dt, dt = 0, s.push(t);
            } else {//整个栈顶块被弹光
                dt -= s.top().second, s.pop();
            }
        }
        if (tp[i]) s.emplace(i, tp[i]);
    }
    return s.empty() ? -1 : st[s.top().first][s.top().second];
}

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) b[i] = (i-1)/M+1, a[i] = {-1, 0};
    for (int i = 1, p; i <= n; ++i) {
        cin >> p >> a[p].first;//修改位置和操作类型
        if (a[p].first) cin >> a[p].second;//若是入栈(>0)再读入栈值
        build(b[p]);//只重建 p 所在的块
        cout << solve() << '\n';//询问整个序列的最终栈顶
    }
    return 0;
}