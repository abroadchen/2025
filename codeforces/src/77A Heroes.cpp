//
// Created by Psy.C on 2025/11/5.
//
/*
*N = 7: 角色总数
heroes[]: 7个角色的名字数组
hero_idx: 角色名到索引的映射
liking[N][N]: 喜爱关系矩阵，初始化为0
a, b, c: 三个团队的经验值
subl[1<<N]: 子集的喜爱度总和数组
 *
*对于每个可能的子集（用位掩码表示）
计算该子集中所有角色相互的喜爱度之和
存储在subl[i]中
 *
*tz: 三个团队的人数分配方案
bd: 当前最佳经验值差异
bl: 当前最佳喜爱度总和
枚举所有可能的三人分配：
第一组：i表示的子集，人数为tz[0]
第二组：j表示的子集，人数为tz[1]
第三组：剩余角色组成的子集，人数为tz[2]
计算各组平均经验值：
e1 = a / tz[0], e2 = b / tz[1], e3 = c / tz[2]
计算经验值差异和喜爱度总和
更新最优解
 *
 *
*定义所有可能的分组方案（7个人分成3组的所有方式）
对每种分组模式，尝试所有排列
调用parti函数寻找最优解
输出最佳差异值和喜爱度
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

const int N = 7;

const string heroes[] = {
    "Anka", "Chapay", "Cleo",
    "Troll", "Dracul", "Snowy",
    "Hexadecimal"
};
map<string,int> hero_idx;
int liking[N][N] = {0}, a, b, c, subl[1<<N];

void solve() {
    for (int i = 0; i < 1 << N; ++i) {
        int t = 0;
        for (int j = 0; j < N; ++j) {
            if (!(i & (1 << j))) continue;
            for (int k = 0; k < N; ++k) {
                if (!(i & (1 << k))) continue;
                t += liking[j][k];
            }
        }
        subl[i] = t;
    }
}

void parti(const vector<int>& tz, int& bd, int& bl) {
    int m = (1 << N) - 1;
    for (int i = 0; i < 1 << N; ++i) {
        if (__builtin_popcount(i) != tz[0]) continue;
        int r = m & ~i;
        for (int j = 0; j < 1 << N; ++j) {
            if ((j & r) != j) continue;
            if (__builtin_popcount(j) != tz[1]) continue;
            int t = r & ~j;
            if (__builtin_popcount(t) != tz[2]) continue;
            int e1 = a / tz[0], e2 = b / tz[1], e3 = c / tz[2],
            minn = min({e1, e2, e3}),
            maxx = max({e1, e2, e3}),
            diff = maxx - minn,
            like = subl[i] + subl[j] + subl[t];
            if (diff < bd) {
                bd = diff;
                bl = like;
            } else if (diff == bd) {
                if (like > bl) bl = like;
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    for (int i = 0; i < N; ++i) hero_idx[heroes[i]] = i;
    int n; cin >> n; cin.ignore();
    for (int i = 0; i < n; ++i) {
        string p, l, q; cin >> p >> l >> q;
        int x = hero_idx[p], y = hero_idx[q];
        liking[x][y] = 1;
    }
    cin >> a >> b >> c;
    solve();

    vector<vector<int>> d = {
        {1, 1, 5}, {1, 2, 4},
        {1, 3, 3}, {2, 2, 3}
    };
    int bd = INT_MAX, bl = 0;
    for (auto& x : d) {
        vector<int> y = x;
        sort(y.begin(), y.end());
        do {
            parti(y, bd, bl);
        } while (next_permutation(y.begin(), y.end()));
    }
    cout << bd << ' ' << bl << endl;
    return 0;
}