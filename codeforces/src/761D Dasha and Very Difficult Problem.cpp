//
// Created by Psy.C on 2026/9/5.
//
/**
a：原始输入数组 a[i]。
num：第二组输入数组，用于决定处理顺序。
pos：记录节点在原数组中的位置，便于后续恢复顺序。
b：最终计算得到的结果值
读取数据规模 n 和合法区间 [l, r]

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

struct node {
    int a, num, pos, b;
    bool operator<(const node &o) const {
        return num < o.num;
    }
};
//按原始位置排序
bool cmp(node o1, node o2) { return o1.pos < o2.pos; }
int n, l, r;
vector<node> v;
int main() {
    fast;
    cin >> n >> l >> r;
    for (int i = 0; i < n; ++i) {
        node o{};
        cin >> o.a; o.pos = i;//读取 a[i] 并记录位置
        v.push_back(o);
    }
    for (int i = 0; i < n; ++i) cin >> v[i].num;
    sort(v.begin(), v.end());
    //初始化偏移量和计数器 为第一个元素分配 b 值
    int mx = 0, cnt = l - v[0].a; v[0].b = cnt + v[0].a;
    cnt++;
    for (int i = 1; i < n; ++i) {
        //尝试将当前元素放在紧挨着前一个元素的右侧
        v[i].b = cnt + v[i].a; cnt++;
        if (v[i].b > r) { cout << -1; return 0; }//超出右边界，直接判负
        if (v[i].b < l) mx = max(mx, l - v[i].b);//记录需要整体左移的最大距离
    }
    ranges::sort(v, cmp);
    for (int i = 0; i < n; ++i)
        if (v[i].b + mx > r) { cout << "-1\n"; return 0; }//整体左移后是否超出右边界
    for (int i = 0; i < n; ++i) cout << v[i].b + mx << ' ';
    return 0;
}