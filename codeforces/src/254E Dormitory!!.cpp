//
// Created by Psy.C on 2025/12/18.
//
/*
*l：左边界（起始时间）
r：右边界（结束时间）
f：所需资源
id：标识符
*dp[N][N]：动态规划表，dp[i][j]表示到第i天拥有j资源时能获得的最大价值
pre[N][N]：前驱状态记录，用于路径重构
p[N][N]：二维向量数组，记录每个状态选择的任务
*n：总天数
v：每天消耗的基础资源
a[N]：数组存储每天的资源上限，从索引1开始存储
 *任务总数m
 *第0天拥有0资源时价值为0
 *
*双重循环遍历所有可能的状态：
i：当前天数（0到n-1）
j：当前拥有的资源数（0到a[i]）
如果当前状态不可达（dp[i][j]=-1）则跳过
*处理不执行任何任务的情况：
num：第i+1天的资源数 = 当前资源 + 新增资源 - 消耗资源
如果资源非负，则更新状态：
取num和a[i+1]的较小值作为实际资源（不超过上限）
如果新状态更优，则更新dp值、前驱状态和选择列表
使用max函数确保dp值不降低
 *计算执行任务情况下的初始资源，如果为负则跳过
*st：临时存储当前选择的任务
tot：当前剩余资源
cnt：已选择的任务数
 *
*遍历所有任务：
检查任务k是否能在第(i+1)天执行（在[l,r]范围内）
如果当前资源不足执行任务k则跳出循环（因为任务已按资源需求排序）
*执行任务k：
扣除所需资源
增加任务计数
将任务ID加入选择列表
*更新状态：
fs：最终资源数（不超过当天上限）
如果新状态可以获得更大价值，则更新dp、前驱和选择列表
 *
*遍历第n天的所有可能资源状态
找到价值最大的状态，记录其资源数idx
*重构路径：
从最后一天开始向前追溯
将每天的资源状态存入ret向量
通过pre数组找到前一天的状态
 *反转ret向量，使其按时间顺序排列
 *
*输出每天的选择：
对于第i天，输出在状态(i,ret[i])下选择的任务
先输出任务数量，然后输出各个任务的ID
 */
#include <iostream>
#include <vector>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 405
#define ii pair<int, int>
using namespace std;

struct node {
    int l, r, f, id;
    bool operator<(const node rhs) const {
        return f < rhs.f;
    }
} fr[N];

int dp[N][N], pre[N][N];
vector<int> p[N][N];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    int n, v, m; cin >> n >> v;
    int a[N] = {};
    for (int i = 1; i <= n; ++i) cin >> a[i];
    memset(pre, -1, sizeof(pre));
    memset(dp, -1, sizeof(dp));
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> fr[i].l >> fr[i].r >> fr[i].f;
        fr[i].id = i + 1;
    }
    sort(fr, fr + m); dp[0][0] = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j <= a[i]; ++j) {
        if (dp[i][j] == -1) continue;
        int num = j + a[i+1] - v;
        if (num >= 0) {
            num = min(num, a[i+1]);
            if (dp[i+1][num] < dp[i][j]) {
                dp[i+1][num] = dp[i][j];
                pre[i+1][num] = j;
                p[i+1][num] = vector<int>();
            }
            dp[i+1][num] = max(dp[i+1][num], dp[i][j]);
        }
        const int res = j + a[i+1] - v;
        if (res < 0) continue;
        vector<int> st;
        int tot  = res, cnt = 0;
        for (int k = 0; k < m; ++k) {
            if (i + 1 < fr[k].l || i + 1 > fr[k].r) continue;
            if (tot < fr[k].f) break;
            tot -= fr[k].f;
            cnt++;
            st.push_back(fr[k].id);

            const int fs = min(tot, a[i+1]);
            if (dp[i+1][fs] < dp[i][j] + cnt) {
                dp[i+1][fs] = dp[i][j] + cnt;
                pre[i+1][fs] = j;
                p[i+1][fs] = st;
            }
        }
    }
    int ans = -1, idx = 0;
    for (int i = 0; i <= a[n]; ++i) if (dp[n][i] > ans) {
        ans = dp[n][i], idx = i;
    }
    cout << ans << '\n';
    vector<int> ret; int cur = idx;
    for (int i = n; i >= 0; --i) {
        ret.push_back(cur);
        if (i > 0) cur = pre[i][cur];
    }
    reverse(ret.begin(), ret.end());
    for (int i = 1; i <= n; ++i) {
        cout << p[i][ret[i]].size();
        for (const int j : p[i][ret[i]]) cout << ' ' << j;
        cout << '\n';
    }
    return 0;
}