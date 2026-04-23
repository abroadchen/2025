//
// Created by Psy.C on 2026/4/23.
//
/**
cnt[41]：记录每种类型出现的次数
n[41]：记录每种类型的位置信息

检查类型t在位置x是否与之前的选择冲突
遍历所有已选择的类型i：
如果类型i已选择(cnt[i] != 0)且(n[i]-x) % gcd(i,t) != 0，则冲突
n[i]-x表示位置差，gcd(i,t)表示类型i和t的公约数
如果无冲突，更新n[t] = x和cnt[t]++
返回是否可以安全选择

T[N]：每个序列的长度
a[N]：存储每个序列
b：map，键为数字，值为(序列号, 位置)的向量

读入n个序列和m个查询
读入每个序列，同时构建map b：
对于数字x，记录它出现在序列i的第j个位置
对每个查询i（即数字i）
重置计数器
使用滑动窗口技术
l：窗口左端点，r：窗口右端点
b[i][r].first - b[i][l].first == r-l：检查序列号是否连续
这确保我们处理的是连续的序列
在窗口中依次检查每个位置：
调用check函数验证是否可以添加
如果不能添加则停止扩展
更新最大窗口大小
减少左端点类型的计数
O(m × k)，其中k是数字i出现的总次数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+7;

int cnt[41], n[41];
bool check(int t, int x) {
    for (int i = 1; i <= 40; ++i)
        if (cnt[i] && (n[i]-x)%__gcd(i, t))
            return false;
    n[t] = x; cnt[t]++;
    return true;
}

int T[N];
vector<int> a[N];
map<int, vector<ii>> b;
int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> T[i];
        for (int j = 1, x; j <= T[i]; ++j) {
            cin >> x;
            a[i].push_back(x);
            b[x].emplace_back(i, j);
        }
    }
    for (int i = 1, l, r, ans; i <= m; ++i) {
        ans = 0;
        memset(cnt, 0, sizeof(cnt));
        for (l = 0, r = 0; l < b[i].size(); ++l) {
            for (; r < b[i].size() && b[i][r].first - b[i][l].first == r-l; ++r)
                if (!check(T[b[i][r].first], b[i][r].second)) break;
            ans = max(ans, r - l);
            cnt[T[b[i][l].first]]--;
        }
        cout << ans << '\n';
    }
    return 0;
}