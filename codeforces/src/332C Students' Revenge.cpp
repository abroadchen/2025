//
// Created by Psy.C on 2026/1/10.
//
/**
 * n（元素总数）、p（需要选择的总数）、k（某种限制）
* 首先按 y 值升序排列
如果 y 值相等，按 x 值降序排列
 *
 *greater<> 表示最小堆（最小值优先）
 *mx（最大值）、ans（答案索引）、sum（当前和，初始化为0）
 *
*从排序后的数组末尾开始，取后 k 个元素
将它们加入优先队列（按 x 值，idx 作为第二元素）
累加 x 值到 sum
*ans 初始化为 n-k（当前选择的起始位置）
mx 初始化为当前 sum（当前最大和）
*从 n-k-1 到 p-k 倒序遍历
如果当前元素的 x 值大于队列顶部（最小值）
替换最小值：
从 sum 中减去旧最小值
弹出队列顶部
插入新元素
将新值加到 sum
如果新的和更大，更新最大值和答案索引
 *
 *t = p - k：计算偏移量
 *输出前 p-k 个元素的原始索引（+1 是因为题目可能使用1基索引）
*从 ans 位置到末尾重新排序，按 x 值降序
输出接下来的 k 个元素的原始索引
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;

struct state {
    int idx{}, x{}, y{};
    state() = default;
    state(const int a, const int b, const int c) : idx(a), x(b), y(c) {}
};


int main() {
    fast;
    int n, p, k; cin >> n >> p >> k;
    vector<state> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].x >> v[i].y;
        v[i].idx = i;
    }
    ranges::sort(v, [](const state &a, const state &b) {
        if (a.y < b.y) return 1;
        if (a.y > b.y) return 0;
        if (a.x > b.x) return 1;
        return 0;
    });
    priority_queue<ii, vector<ii>, greater<>> q;
    ll mx, ans, sum = 0;
    for (int i = n - 1; i >= n - k; --i) {
        q.emplace(v[i].x, v[i].idx);
        sum += v[i].x;
    }
    ans = n - k, mx = sum;
    for (int i = n - k - 1; i >= p - k; --i) if (v[i].x > q.top().first) {
        sum -= q.top().first; q.pop();
        q.emplace(v[i].x, v[i].idx);
        sum += v[i].x;
        if (sum > mx) { mx = sum; ans = i; }
    }
    const int t = p - k;
    for (int i = static_cast<int>(ans) - t; i <= ans - 1; ++i) cout << v[i].idx + 1 << ' ';
    sort(v.begin() + ans, v.end(), [](const state &a, const state &b) {
        return a.x > b.x;
    });
    while (k--) cout << v[ans++].idx + 1 << ' ';
    return 0;
}