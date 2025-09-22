//
// Created by Psy.C on 2025/9/22.
//

#include <cstdio>
#include <vector>
#include <algorithm>
#define inf 1000000007
using namespace std;
// n:行数, m:列数, k:已占用点数, x[],y[]:已占用点的坐标
int n, m, k, x[15], y[15];
pair<int, int> res, p[15];// res:结果坐标, p[]:区间数组

bool ok(int o) {// o:当前检查的半径
    for (int i = 1; i <= n; ++i) {// 遍历每一行
        for (int j = 1; j <= k; ++j) {// 遍历每一个已占用点
            int q = abs(x[j] - i);// 计算当前行与已占用点的行距离
            // 计算在当前行上被覆盖的列区间
            if (q <= o) p[j] = make_pair(y[j] - o + q, y[j] + o - q);
            else p[j] = make_pair(inf, -inf);
        }
        sort(p + 1, p + 1 + k);// 按区间左端点排序
        int t = 0;// 初始化已覆盖的最右列
        for (int j = 1; j <= k; ++j) {// 遍历所有区间
            if (p[j].first == inf) break;
            if (p[j].first > t + 1) {// 如果当前区间与已覆盖区域有空隙
                res = make_pair(i, t + 1);// 记录第一个未被覆盖的位置
                return 1;// 返回true，表示当前半径可行
            }
            t = max(t, p[j].second);// 更新已覆盖的最右列
        }
        if (t < m) {// 如果最后一段未覆盖到第m列
            res = make_pair(i, m);// 记录位置
            return 1;
        }
    }
    return 0;
}

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    res = make_pair(1, 1);// 初始化结果为(1,1)
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; ++i) scanf("%d%d", &x[i], &y[i]);
    int l = 0, r = n + m, ans = 0;
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        if (ok(mid)) {
            ans = mid;
            l = mid;// 缩小左边界
        } else {
            r = mid;// 否则缩小右边界
        }
    }
    while (ok(ans + 1)) ans++;// 继续检查更大的半径是否可行
    ok(ans);// 用最终半径再运行一次ok函数，获取具体位置
    printf("%d %d\n", res.first, res.second);

    return 0;
}