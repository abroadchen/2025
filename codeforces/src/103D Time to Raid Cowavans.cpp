//
// Created by Psy.C on 2025/11/12.
//
/*
 *q[M]：二维向量数组，用于存储按步长分组的查询，q[i]存储所有步长为i的查询
 *
*处理p个查询，每个查询包含起点a和步长b：
如果步长b小于阈值M，则将查询{起点, 查询编号}加入q[b]向量中
如果步长b大于等于M，则直接计算结果：从位置a开始，每隔b个位置取一个元素求和，存储到ans[i]中
 *
*对于所有步长i（从1到M-1）：
如果没有步长为i的查询，则跳过
从后向前计算dp数组：
如果i+j不超过n，则dp[j] = w[j] + dp[i+j]（当前值加上下一步的dp值）
否则dp[j] = w[j]（边界情况）
处理所有步长为i的查询：查询结果等于dp[起点]
 *
 *
*小步长：O(M×N)预处理 + O(1)每次查询
大步长：O(N/M)每次查询
总体复杂度得到很好的平衡
 */
#include <vector>
#include <iostream>
using namespace std;

typedef long long ll;
const int N = 3e5+10, M = 550;
int n;
ll w[N], ans[N], dp[N];
vector<pair<ll, ll> > q[M];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    int p; cin >> p;
    for (int i = 0, a, b; i < p; ++i) {
        cin >> a >> b;
        if (b < M) q[b].push_back({a, i});
        else {
            ll sum(0);
            for (int j = a; j <= n; j += b) sum += w[j];
            ans[i] = sum;
        }
    }
    for (int i = 1; i < M; ++i) {
        if (q[i].empty()) continue;
        for (int j = n; j >= 1; --j) {
            if (i + j <= n) dp[j] = w[j] + dp[i + j];
            else dp[j] = w[j];
        }
        for (pair<ll, ll> p : q[i]) ans[p.second] = dp[p.first];
    }
    for (int i = 0; i < p; ++i) cout << ans[i] << "\n";
    return 0;
}