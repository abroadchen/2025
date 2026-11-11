//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
随机取两点 x,y，遍历询问 ? i x y。
语义（满 k 叉树）：? i x y 的 "Yes" 表示 节点 i 在 x 到 y 的路径上（或某特定关系）。
若存在某个 i 回答 Yes，说明 x 不是"叶子/根候选"，换一组重试；若对所有 i 都是 No，则 x 是通过考验的候选（返回 x）
对所有 i 问 ? x i y，统计答 Yes 的次数。
即计算 x 到 y 路径上有多少个点（含端点）
用满 k 叉树节点总数 1 + k + k² + ... 不断累加，直到超过 n，以此得到树的高度 h（层数）。
（说明：满 k 叉树节点数 = (k^h -1)/(k-1) 之类，这里用累加循环求层数。）
遍历路径中点 i（在 x→y 上），若 calc(x,i)==calc(i,y)==h（到两端都相距恰好 h 步），则 i 就是要求的节点（根），返回。
找不到返回 0
不断随机找两个候选 x,y，要求 calc(x,y)==2h-1（即 x、y 分别在根两侧的叶子，路径经过根且总长 2h-1）。
在路径上定位根并输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i = 1; i <= n; ++i)
using namespace std;

void out(int x, int y, int z) { cout << "? " << x << ' ' << y << ' ' << z << endl; }

int n;
string s;
int get() {
    while (1) {
        int x = rand()%n + 1, y;
        while ((y = rand()%n + 1))
            if (y != x) break;
        int f = 0, i;
        rep(i,n) {
            if (i == x || i == y) continue;
            out(i,x, y);
            cin >> s;
            if (s == "Yes") { f = 1; break; }
        }
        if (f == 0) return x;
    }
}
int calc(int x, int y) {
    int cnt = 0, i;
    rep(i,n) {
        out(x, i, y);
        cin >> s;
        if (s == "Yes") ++cnt;
    }
    return cnt;
}

int h;
int getrt(int x, int y) {
    int i;
    rep(i,n) {
        out(x, i, y);
        cin >> s;
        if (s == "Yes") {
            int l = calc(x,i), r = calc(i,y);
            if (l == r && l == h) return i;
        }
    }
    return 0;
}

int k;
int main() {
    fast;
    srand(1e9+7); cin >> n >> k;
    for (int i = 0, t = 1; i <= n; t *= k, i += t, ++h) {}
    int x = get();//随机找第一个候选根
    while (1) {
        int y = get();//再随机找一个候选根
        if (x == y) continue;
        if (calc(x, y) != 2*h - 1) continue;//路径长度必须恰好 2h-1（经过根的那条）
        int tmp = getrt(x, y);//在它们路径上找根
        if (tmp == 0) continue;
        return cout << "! " << tmp << endl, 0;
    }
    return 0;
}