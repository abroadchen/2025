//
// Created by Psy.C on 2026/2/26.
//
/**
a[i].id=i：将第i个节点的id设为i
a[a[i].id=i].siz：由于id被设置为i，所以这实际上等同于a[i].siz
所以这个循环是输入每个节点的siz值

判断最大值和最小值的差是否大于k
嵌套循环为每个节点的答案数组赋值
对于每个节点i，将其ans数组的前siz个元素赋值为j%k+1
这样确保每个元素的值都在1到k之间
按照id重新排序，恢复原始顺序

外层循环遍历每个节点
sort(a[i].ans + 1, a[i].ans + a[i].siz + 1)：对当前节点的ans数组排序
内层循环输出当前节点的ans数组中的所有元素
每个节点的答案输出后换行

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101;
struct node {
    int siz, id, ans[N];
} a[N];

int n, k;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[a[i].id=i].siz;
    sort(a + 1, a + n + 1, [](const node &x, const node &y) {
        return x.siz < y.siz;
    });
    if (a[n].siz - a[1].siz > k) return cout << "NO\n", 0;
    cout << "YES\n";
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= a[i].siz; ++j)
            a[i].ans[j] = j%k+1;
    sort(a + 1, a + n + 1, [](const node &x, const node &y) {
        return x.id < y.id;
    });
    for (int i = 1; i <= n; ++i) {
        sort(a[i].ans + 1, a[i].ans + a[i].siz + 1);
        for (int j = 1; j <= a[i].siz; ++j)
            cout << a[i].ans[j] << ' ';
        cout << '\n';
    }
    return 0;
}