//
// Created by Psy.C on 2026/2/11.
//
/**num[i]：记录第i类元素的数量
cnt：辅助计数器
q[N]：临时数组
g[i]：存储第i类的所有y值

x = num[0] + mid：设定每类最多保留的元素数
第一段循环：从每类中取前max(-1, num[i]-x)个最小元素
检查总数：如果取出元素超过mid个，返回无穷大
第二段循环：将剩余元素放入数组q
排序和选取：排序q并取前mid-tot个最小元素
返回结果：返回总和

排序：O(n log n)
三分查找：O(log²n)（每次ok函数调用O(n)）
总体：O(n log n)
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
using namespace std;

int num[N], cnt, q[N];
vector<int> g[N];
int ok(const int mid) {
    const int x = num[0] + mid;
    int res = 0, tot = 0;
    for (int i = 1; i <= N-10; ++i)
        for (int j = 0; j <= max(-1, num[i]-x); ++j)
            tot++, res += g[i][j];
    if (tot > mid) return 1<<30;
    cnt = 0;
    for (int i = 1; i <= N-10; ++i)
        for (int j = max(0, num[i]-x+1); j <= num[i]-1; ++j)
            q[++cnt] = g[i][j];
    sort(q + 1, q + cnt + 1);
    for (int i = 1; i <= mid - tot; ++i) res += q[i];
    return res;
}

int n, ans=1<<30;

int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i <= n; ++i) {
        cin >> x >> y;
        if (x == 0 || y == 0) num[0]++;
        else g[x].push_back(y), num[x]++;//将y添加到g[x]中，并更新num[x]
    }
    //对每个类别中的元素进行排序
    for (int i = 1; i <= N-10; ++i) ranges::sort(g[i]);
    int flag = true;
    for (int i = 1; i <= n; ++i) if (num[i] >= num[0]) flag = false;//无法处理
    if (flag) return cout << "0\n", 0;
    int l = 1, r = n;
    while (l <= r) {
        const int m1 = l + (r - l) / 3; int f1 = ok(m1);
        const int m2 = r - (r - l) / 3;
        //比较两个三分点的函数值，缩小搜索范围
        if (int f2 = ok(m2); f1 <= f2) r = m2 - 1, ans = min(ans, f1);//维护全局最小值
        else l = m1 + 1, ans = min(ans, f2);
    }
    cout << ans << '\n';
    return 0;
}