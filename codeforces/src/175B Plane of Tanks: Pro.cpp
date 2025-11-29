//
// Created by Psy.C on 2025/11/29.
//
/*
*n: 玩家操作记录数量
score[N]: 记录每个分数段的人数
cnt[N]: 记录后缀和（分数高于某值的人数）
 *
*读入玩家姓名str和分数t
如果玩家第一次出现（find返回end()）：
记录该玩家的分数
对应分数段人数加1
如果玩家已存在且新分数更高：
新分数段人数加1
原分数段人数减1
更新玩家最高分
 *
 *cnt[i] 表示分数严格大于i的人数
 *
*获取玩家最高分t
计算比该玩家分数高的人数m = cnt[t]
根据百分位确定等级：
50%: noob (新手)
20%: random (随机玩家)
10%: average (平均水平)
1%: hardcore (硬核玩家)
≤1%: pro (专业玩家)
 *
 *
 *
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1005;
int n, score[N], cnt[N];
char str[15];//玩家姓名
map<string, int> mp;//姓名到最高分数的映射
map<string, int>::iterator it;

int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int t; cin >> str >> t;
        if (mp.find(str) == mp.end()) { mp[str] = t; score[t]++; }
        else if (mp[str] < t) {
            score[t]++; score[mp[str]]--; mp[str] = t;
        }
    }
    for (int i = 1000; i >= 0; --i) cnt[i] = cnt[i+1] + score[i+1];
    n = static_cast<int>(mp.size());
    cout << n << '\n';
    for (it = mp.begin(); it != mp.end(); ++it) {
        const int t = it->second;
        cout << it->first << ' ';
        const int m = cnt[t];
        if (100 * m > 50 * n) cout << "noob" << '\n';
        else if (100 * m > 20 * n) cout << "random" << '\n';
        else if (100 * m > 10 * n) cout << "average" << '\n';
        else if (100 * m > n) cout << "hardcore" << '\n';
        else cout << "pro" << '\n';
    }
    return 0;
}