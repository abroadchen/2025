//
// Created by Psy.C on 2025/12/7.
//
/*
*n：区间组数
m：坐标范围（固定为100010）
ans：结果计数器
node结构体实现树状数组：
c[N]：树状数组存储
clr()：清零函数
lb()：计算最低位1的值（lowbit函数）
update()：单点更新
sum()：前缀和查询
 *
*f()函数比较区间集合的差异：
如果o集合大小≤1，直接返回
清空两个树状数组
将l集合中的点插入第一个树状数组
将r集合中的点插入第二个树状数组
 *
*从o集合的第一个点开始
对于每对相邻点L和R
如果区间(L,R)非空
分别查询两个树状数组在该区间内的点数u和v
如果点数不同，说明区间集合在该区间内有差异，结果加1
更新L为当前的R
 *
*init()函数读取并排序一个点集：
清空向量v
读取点数q和q个坐标点
对点集排序
 *
*处理第3到第n组：
读取第i组点集作为r
如果是最后一组，保存到t
调用f()比较l和r相对于o的差异
更新l和o
 *
*比较t1与之前的结果
进行最后一次三元比较
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100505
using namespace std;

int n, m, ans;

struct node {
    int c[N];
    void clr() { memset(c, 0, sizeof(c)); }
    static int lb(const int x) { return x & (-x); }
    void update(int i, const int x) {
        while (i <= m) { c[i] += x; i += lb(i); }
    }
    int sum(const int x) const {
        int res = 0;
        for (int i = x; i >= 1; i -= lb(i)) res += c[i];
        return res;
    }
} tr[2];
vector<int> l, r, o;
void f() {
    if (o.size() <= 1) return;
    tr[0].clr(); tr[1].clr();
    for (const int i : l) tr[0].update(i, 1);
    for (const int i : r) tr[1].update(i, 1);
    int L = o[0];
    for (int i = 1; i < o.size(); ++i) {
        const int R = o[i];
        if (L + 1 <= R - 1) {
            const int u = tr[0].sum(R - 1) - tr[0].sum(L),
            v = tr[1].sum(R - 1) - tr[1].sum(L);
            ans += u != v;
        }
        L = R;
    }
}

vector<int> v;
void init() {
    v.clear();
    int q, x; cin >> q;
    while (q--) { cin >> x; v.push_back(x); }
    sort(v.begin(), v.end());
}

vector<int> t1, t2, t;
int main() {
    fast;
    cin>>n; m = 100010; ans = 0;
    l.clear(); r.clear();  t1.clear(); t2.clear(); t.clear();
    init(); l = t1 = v;
    init(); t2 = o = v;
    for (int i = 3; i <= n; ++i) {
        init(); r = v;
        if (i == n) t = v;
        f();
        l = o, o = r;
    }
    r = t1; f();
    l = t, o = t1, r = t2; f();
    cout << ans << '\n';
    return 0;
}