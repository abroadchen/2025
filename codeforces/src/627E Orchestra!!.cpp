//
// Created by Psy.C on 2026/3/28.
//
/**
计算以位置x为起点，向右延伸到R[x]，左边有效边界为l[x]的矩形面积
返回值为：左边界位置 × (右边界位置 - 当前位置)
l[x]是x左边的元素，R[x]是x右边的元素
n行数，m列数，cnt数据点数，K阈值
v[j]列j的计数，L[N]左邻接，sz[N]大小
vc[i]第i行的数据，p临时数组
tot当前总数，res最终结果
将坐标(x,y)按行组织存储到vc[x]中

累积第1行到第i行的所有数据点，统计每列的出现次数

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3005;

int l[N], R[N];
int get(int x) { return l[x]*(R[x] - x); }

int n, m, cnt, K, v[N], L[N], sz[N];
vector<int> vc[N], p;
ll tot, res;
int main() {
    fast;
    cin >> n >> m >> cnt >> K;
    for (int i = 1, x, y; i <= cnt; ++i) {
        cin >> x >> y;
        vc[x].push_back(y);
    }
    for (int i = 1; i <= n; ++i) {
        memset(v, 0, sizeof(v));
        for (int j = 1; j <= i; ++j)
            for (auto x : vc[j])
                v[x]++;
        p.clear(); p.push_back(0);//添加左哨兵
        for (int j = 1; j <= m; ++j)
            if (v[j]) p.push_back(j);//只添加有数据的列
        p.push_back(m+1);//添加右哨兵
        R[0] = p[1]; tot = 0;//设置左哨兵的右邻居
        for (int j = 1; j + 1 < p.size(); ++j) {
            int x = p[j];
            L[x] = p[j-1], R[x] = p[j+1];//建立双向链表
            l[x] = l[p[j-1]];//继承左邻居的左边界
            sz[x] = sz[p[j-1]] + v[x];//累积大小
            while (sz[x] - v[l[x]] >= K) {//如果去除最左边元素后仍满足条件
                sz[x] -= v[l[x]];//减少计数
                l[x] = R[l[x]];//移动左边界
            }
            tot += get(x);//累加当前贡献
        }
        for (int j = 1; j <= i; ++j) {
            res += tot;//累加当前结果
            for (auto x : vc[j]) {//遍历第j行的每个数据点
                if (--v[x] == 0) {//如果该列计数变为0
                    //从链表中删除该列
                    tot -= get(L[x]); tot -= get(x);//移除贡献
                    R[L[x]] = R[x], L[R[x]] = L[x];//从链表移除
                    tot += get(L[x]);//重新计算邻居贡献

                    //更新右边所有列的参数
                    for (int k = R[x]; k <= m && l[k] <= x; k = R[k]) {
                        sz[k]--;
                        tot -= get(k);
                        while (l[k] && sz[k] < K)//如果不满足阈值要求
                            l[k] = L[l[k]], sz[k] += v[l[k]];//调整左边界
                        tot += get(k);
                    }
                } else {//如果该列仍有计数
                    //只需更新右边受影响列的参数
                    for (int k = x; k <= m && l[k] <= x; k = R[k]) {
                        sz[k]--;
                        tot -= get(k);
                        while (l[k] && sz[k] < K)
                            l[k] = L[l[k]], sz[k] += v[l[k]];
                        tot += get(k);
                    }
                }
            }
        }
    }
    cout << res;
    return 0;
}