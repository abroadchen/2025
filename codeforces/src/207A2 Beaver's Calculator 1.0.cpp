//
// Created by Psy.C on 2025/12/5.
//
/*
*k[3]: 存储两个序列的长度k1和k2
d[3][N]: 记录每个序列的递减点位置
cnt[N]: 记录每个序列中递减点的数量
cur[N]: 当前处理到的位置指针
 *a[3][N]: 存储两个生成的序列
 *
*根据前一项计算当前项：a[1][i] = (a[1][i-1]*x + y) % m
如果当前项小于前一项，说明出现了递减，记录这个位置到d[1]数组中，并增加计数器cnt[1]
 *
 *
*外层循环遍历所有递减段
中层循环处理每个序列
内层循环将当前段的所有元素加入优先队列（使用负值实现升序输出）
最后将优先队列中的元素依次输出
 *
 */
#include <iostream>
#include <algorithm>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 200005
using namespace std;

constexpr int inf = 2e5;
int n, k[3], d[3][N], cnt[N], cur[N];
ll a[3][N], x, y, m;
priority_queue<pair<ll, int>> q;//按第一个元素降序排列

int main() {
    fast;
    cin>>n;
    cin >> k[1] >> a[1][1] >> x >> y >> m;//第一个序列的长度k1、首项a[1][1]
    for (int i = 2; i <= k[1]; ++i) {
        a[1][i] = (a[1][i-1]*x + y) % m;
        if (a[1][i] < a[1][i-1]) d[1][++cnt[1]] = i - 1;
    }
    cin >> k[2] >> a[2][1] >> x >> y >> m;
    for (int i = 2; i <= k[2]; ++i) {
        a[2][i] = (a[2][i-1]*x + y) % m;
        if (a[2][i] < a[2][i-1]) d[2][++cnt[2]] = i - 1;
    }
    d[1][++cnt[1]] = k[1]; d[2][++cnt[2]] = k[2];//将每个序列的最后一个位置也加入到递减点数组中，确保完整性
    cout << max(cnt[1], cnt[2]) - 1 << '\n';
    if (k[1] + k[2] > inf) return 0;
    for (int i = 1; i <= n; ++i) cur[i] = 1;
    for (int i = 1; i <= max(cnt[1], cnt[2]); ++i) {
        for (int j = 1; j <= n; ++j) {
            if (cnt[j] < i) continue;
            for (; cur[j] <= d[j][i]; ++cur[j]) {
                pair<ll, int> ans;
                ans.first = -a[j][cur[j]];
                ans.second = j;
                q.push(ans);
            }
        }
        while (!q.empty()) {
            cout << -q.top().first << ' ' << q.top().second << '\n';
            q.pop();
        }
    }
    return 0;
}