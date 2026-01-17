//
// Created by Psy.C on 2026/1/17.
//
/**
 * id(原始编号), val(价值), w(权重标记), nxt(下一个节点)
 *t用于分块存储DP状态
 */
#include <iostream>
#include <algorithm>
#include <bitset>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 70001
using namespace std;

struct node { int id, val, w, nxt; } a[N];

bitset<N> t2, t[N/10];
int get(const int x, const int y) {//从1到x能否凑出价值y
    if (y < 0) return 0;
    t2 = t[x/10];//对应块的DP状态
    for (int i = x/10*10+1; i <= x; ++i)//不在完整块中的元素
        t2 |= t2<<a[i].val;//状态转移：考虑添加物品i
    return t2[y];//是否能凑出价值y
}

int main() {
    fast;
    int n, s; cin >> n >> s;//物品数量n和背包容量s
    for (int i = 1; i <= n; ++i) {//读取价值并记录原始ID
        cin >> a[i].val, a[i].id = i;
    }
    sort(a + 1, a + n + 1, [](const node a, const node b) {
        return a.val < b.val;
    });
    //t1[0]=true表示能凑出价值0，t[0]存储初始状态
    bitset<N> t1; t1[0] = true; t[0] = t1;
    for (int i = 1; i < n; ++i) {
        t1 |= t1<<a[i].val;
        if (i % 10 == 0) t[i/10] = t1;//每10个物品作为一个块，存储DP状态
    }
    const int tar = s - a[n].val;//目标价值：总容量减去最大价值物品
    int nxt[N]; memset(nxt, -1, sizeof(nxt));
    if (get(n - 1, tar)) {//前n-1个物品能凑出tar价值
        int now = s - a[n].val;//当前剩余目标价值
        for (int i = n - 1; i; --i) if (now >= a[i].val && get(i - 1, now - a[i].val)) {
            now -= a[i].val;//更新剩余目标价值
            a[i].w = 1;//标记该物品被选中
        }
        int p = n;//指向链表末尾
        for (int i = n - 1; i; --i) if (!a[i].w) {//遍历未被选中的物品
            a[p].nxt = a[i].id;//建立链接关系
            p = i;//更新p指向当前物品
        }
        sort(a + 1, a + n + 1, [](const node a, const node b) {
            return a.id < b.id;
        });
        for (int i = 1; i <= n; ++i) {
            //如果有后继：输出权重(当前价值-后继价值)，1(表示有后继)，后继ID
            if (a[i].nxt) cout << a[i].val - a[a[i].nxt].val << " 1 " << a[i].nxt << '\n';
            else cout << a[i].val << " 0\n";//如果无后继：输出当前价值，0(表示无后继)
        }
    } else cout << "-1";//无解
    return 0;
}