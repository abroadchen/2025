//
// Created by Psy.C on 2026/4/25.
//
/**
num：数值
id：标识符
add：增加值
重载小于运算符，按照以下规则排序：
数值大的排在前面（降序）
如果数值相等，id小的排在前面（升序）

比较两个节点在增加add值前后的相对顺序变化
复制原始节点x, y和待修改节点tx, ty
将add值加到待修改节点上
如果原来x < y，但加上add后ty < tx（顺序反转），返回1
如果原来y < x，但加上add后tx < ty（顺序反转），返回1
如果出现x < y < tx < ty或y < x < ty < tx这样的四点顺序变化，返回2
如果出现ty < x < y < tx或tx < y < x < ty这样的四点顺序变化，返回2
如果没有发生上述任何一种顺序变化，返回0

两层循环遍历所有节点对
计算每对节点的顺序变化情况并累加到ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 107;

struct node {
    int num, id, add;
    bool operator<(const node &o) const {
        return num > o.num || (num == o.num && id < o.id);
    }
} a[N];

int ok(int i, int j) {
    node x = a[i], y = a[j], tx = x, ty = y;
    tx.num = x.num + x.add, ty.num = y.num + y.add;
    if (x < y && ty < tx) return 1;
    if (y < x && tx < ty) return 1;
    if (x < y && y < tx && tx < ty) return 2;
    if (y < x && x < ty && ty < tx) return 2;
    if (x < y && ty < x && tx < ty) return 2;
    if (y < x && tx < y && ty < tx) return 2;
    return 0;
}

int ans, n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].num >> a[i].add;
        a[i].id = i;
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i)
        for (int j = i+1; j <= n; ++j)
            ans += ok(i, j);
    cout << ans << '\n';
    return 0;
}