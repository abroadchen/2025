//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
a[id] 记录每个编号元素被人为赋的绝对位置标号（不是逻辑下标，而是用来比较顺序的相对坐标）。
M 取 1e5 是为了让初始时能同时向左右扩展（l 从 M 开始向左减、r 从 M+1 向右加），避免负数下标
用一个动态扩展的坐标轴：l 不断左移、r 不断右移，给每个插入的元素分配一个单调的位置标号。
插入 L：新元素放在当前所有元素的最左边，占用标号 l，随后 l--（下一轮更左）。
插入 R：放到最右边，占用标号 r，随后 r++。
查询：求该元素到当前队列左端和右端的距离，取小者。
pos 关系：

当前队列左端标号 = l + 1（因为 l 已被减到边界外）
当前队列右端标号 = r - 1
元素 id 到左端距离 = a[id] - (l+1)？
但代码用的是 a[id] - l - 1 = a[id] - (l+1)，正确。
到右端距离 = (r-1) - a[id] = r - a[id] - 1，代码中 r - a[id] - 1 正确。
取 min 即答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+5, M = 1e5;


int q, id, a[N];
char c;
int main() {
    fast;
    cin >> q;
    int l = M, r = M+1;
    while (q--) {
        cin >> c >> id;
        if (c == 'L') a[id] = l--;
        else if (c == 'R') a[id] = r++;
        else cout << min(a[id]-l-1, r-a[id]-1) << '\n';
    }
    return 0;
}