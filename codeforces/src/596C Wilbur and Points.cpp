//
// Created by Psy.C on 2026/3/20.
//
/**
x, y：坐标
val：y-x的值
id：原始索引
rec：记录匹配关系
n1[N], n2[N]：两个节点数组
按val值排序，val相同时按x排序，x相同时按y排序
读取n个目标值
按val排序，val相同时按id排序
检查排序后的val值是否完全匹配
n2[i].rec = n1[i].id：记录n2[i]应该匹配到n1的哪个位置
如果val匹配成功，恢复原始顺序
检查匹配后是否满足单调性要求：
对于相邻的两个目标值，匹配到的点必须满足：
新点的x > 旧点的x，或
新点的y > 旧点的y
如果所有条件都满足，输出YES和匹配后的坐标
否则输出NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
struct node { int x, y, val, id, rec; } n1[N], n2[N];
bool cmp(const node &a, const node &b) { return a.id < b.id; }
int n;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> n1[i].x >> n1[i].y;
        n1[i].val = n1[i].y - n1[i].x;
        n1[i].id = i;
    }
    sort(n1, n1 + n, [](const node &a, const node &b) {
        if (a.val != b.val) return a.val < b.val;
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    for (int i = 0; i < n; ++i) { cin >> n2[i].val; n2[i].id = i; }
    sort(n2, n2 + n, [](const node &a, const node &b) {
        if (a.val != b.val) return a.val < b.val;
        return a.id < b.id;
    });
    bool flag = true;
    for (int i = 0; i < n; ++i) {
        if (n1[i].val != n2[i].val) { flag = false; break; }
        n2[i].rec = n1[i].id;
    }
    if (flag) {
        sort(n2, n2 + n, cmp);
        sort(n1, n1 + n, cmp);
        for (int i = 1; i < n; ++i) {
            if (!(n1[n2[i].rec].x > n1[n2[i-1].rec].x ||
                n1[n2[i].rec].y > n1[n2[i-1].rec].y)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            cout << "YES\n";
            for (int i = 0; i < n; ++i)
                cout << n1[n2[i].rec].x << ' ' << n1[n2[i].rec].y << '\n';
        } else cout << "NO\n";
    } else cout << "NO\n";
    return 0;
}