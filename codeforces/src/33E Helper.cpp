//
// Created by Psy.C on 2025/9/21.
//时间复杂度：O(n × totalFree) 空间复杂度：O(n × totalFree)

#include <iosfwd>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <array>
#include <cassert>
#include <algorithm>
#include <tuple>
using namespace std;

int time2Int(string s) {
    int hh = stoi(s.substr(0,2));
    int mm = stoi(s.substr(3));
    return hh * 60 + mm;// 转换为总分钟数
}

string int2Time(int x) {
    int hh = x / 60;
    int mm = x % 60;
    string s;
    s += '0' + hh / 10;// 十位小时
    s += '0' + hh % 10;// 个位小时
    s += ':';
    s += '0' + mm / 10;
    s += '0' + mm % 10;
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int m, n, k; cin >> m >> n >> k;// m: 人员数, n: 任务数, k: 天数
    vector<string> name(m);
    map<string, int> id;
    for (int i = 0; i < m; ++i) {
        cin >> name[i];
        id[name[i]] = i;// 建立姓名到索引的映射
    }
    vector<int> cost(m);
    for (int i = 0; i < m; ++i) cin >> cost[i];
    array<bool, 1440> free; free.fill(true);// 建立空闲时间数组（1440分钟=24小时）
    for (int i = 0; i < 4; ++i) {
        string s; cin >> s;
        int S = time2Int(s.substr(0,5));// 开始时间
        int T = time2Int(s.substr(6));// 结束时间
        for (int i = S; i <= T; ++i) free[i] = false;// 标记为忙碌
    }
    array<int, 1441> pre{};// 计算前缀和数组，用于快速查询区间空闲时间数
    for (int i = 0; i < 1440; ++i) pre[i + 1] = pre[i] + free[i];

    int freePerDay = pre[1440];// 每天空闲分钟数
    int totalFree = freePerDay * k;// k天总空闲分钟数
    vector<array<int, 4>> people;// 存储任务信息：{时间, 成本, 收益, 原始索引}

    for (int i = 0; i < n; ++i) {
        string name;
        int day;
        string time;
        int money;
        cin >> name >> day >> time >> money;

        if (!id.count(name)) continue;// 如果人员不在名单中则跳过
        int t = time2Int(time);// 将时间转换为统一的时间点
        t = (day - 1) * freePerDay + pre[t];// 转换为相对时间点
        people.push_back({t, cost[id[name]], money, i});
    }

    sort(people.begin(), people.end());// 按时间排序任务
    n = people.size();

    vector<int> point;// 建立所有可用时间点的列表
    for (int i = 0; i < k; ++i) {// 对于每一天
        for (int j = 0; j < 1440; ++j) {// 对于每一分钟
            if (free[j])
                point.push_back(i * 1440 + j);// 添加时间点
        }
    }
    // DP状态：dp[i][j]表示考虑前i个任务，使用j单位时间能获得的最大收益
    vector<vector<int>> dp(n + 1, vector<int>(totalFree + 1));
    for (int i = 0; i < n; ++i) {
        auto [t, cost, money, j] = people[i];
        dp[i + 1] = dp[i];// 复制不选当前任务的状态
        for (int j = t - cost; j >= 0; --j)// 选择当前任务的转移
            dp[i + 1][j + cost] = max(dp[i + 1][j + cost], dp[i][j] + money);
        for (int j = 1; j <= totalFree; ++j)// 状态压缩：维护单调性
            dp[i + 1][j] = max(dp[i + 1][j], dp[i + 1][j - 1]);
    }

    cout << dp[n][totalFree] << "\n";// 输出最大收益

    vector<tuple<int, int, string, int, string>> ans;// 重构具体方案
    int t = totalFree;
    for (int i = n - 1; i >= 0; --i) {
        auto [lim, cost, money, j] = people[i];
        while (t && dp[i + 1][t - 1] == dp[i + 1][t]) t--;// 找到实际使用的最晚时间点
        if (t <= lim && t >= cost && dp[i + 1][t] == dp[i][t - cost] + money) {// 判断是否选择了当前任务
            int end = point[t - 1];
            t -= cost;
            int start = point[t];
            ans.emplace_back(j + 1, start / 1440 + 1, int2Time(start % 1440),
                end / 1440 + 1, int2Time(end % 1440));
        } else {
            assert(dp[i + 1][t] == dp[i][t]);// 确保状态转移正确
        }
    }
    reverse(ans.begin(), ans.end());// 反转结果使其按时间顺序排列
    cout << ans.size() << "\n";

    for (auto [a, b, c, d, e] : ans)
        cout << a << " " << b << " " << c << " " << d << " " << e << "\n";

    return 0;
}