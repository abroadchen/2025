//
// Created by Psy.C on 2026/9/25.
//
/**
n 个矩形，每个用 pair 存长宽。
a, b 是画布的长、宽
读入 n、画布尺寸、以及每个矩形的尺寸
check(w, h)：判断一个宽为 w、高为 h 的包围矩形能否放进画布 a×b（即 w<=a && h<=b）
rotate：交换两个数（用来把矩形旋转 90°）
两层循环枚举每一对矩形 (i, j)。
内层 for k<4：只旋转第一个矩形 (xi,yi) 4 次（0°/90°其实只有2种本质状态，这里用4次冗余，但无副作用）。
对每一种摆放方式：
ok == false 对应竖直堆叠：两个矩形上下叠放，总高度 = yi + yj，宽度取两者宽的较大值 max(xi,xj)。能放进画布则更新答案（面积和 = xi*yi + xj*yj）。
ok == true 对应水平并排：两个矩形左右排，总宽度 = xi + xj，高度取较大值 max(yi,yj)。
记录所有可行摆放中的最大面积和。
注意：这里枚举的是"选哪两个矩形、第一块怎么旋转"，旋转第二个矩形的情况通过交换 i、j 的组合被覆盖到。
依次尝试 4 种情况：
画布原方向 + 矩形竖直堆叠；
画布原方向 + 矩形水平并排；
画布翻转（rotate(a,b) 交换画布长宽）+ 竖直堆叠；
画布翻转 + 水平并排。
取 4 次结果的最大值输出。
rotate(a,b) 交换画布长宽，本质是覆盖了"画布横竖摆放"的对称情况，避免遗漏。所有方案都不行时就保持 ans=0。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 107;
int n, a, b;
ii p[N];
int main() {
    fast;
    cin >> n >> a >> b;
    for (int i = 1; i <= n; ++i) cin >> p[i].first >> p[i].second;
    bool ok = false;
    auto check = [&](int i, int j) -> bool {
        return i <= a && j <= b;
    };
    auto rotate = [&](int& i, int& j) -> void {
        swap(i, j);
    };
    auto solve = [&]() -> int {
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = i+1; j <= n; ++j) {
                int xi = p[i].first, yi = p[i].second, xj = p[j].first, yj = p[j].second;
                for (int k = 0; k < 4; ++k) {
                    if (!ok) {
                        if (check(max(xi, xj), yi+yj))
                            ans = max(ans, xi*yi + xj*yj);
                    } else {
                        if (check(xi+xj, max(yi, yj)))
                            ans = max(ans, xi*yi + xj*yj);
                    }
                    rotate(xi, yi);
                }
            }
        }
        return ans;
    };
    int ans = 0;
    ok = false;
    ans = max(ans, solve());
    ok = true;
    ans = max(ans, solve());
    rotate(a, b);
    ok = false;
    ans = max(ans, solve());
    ok = true;
    ans = max(ans, solve());
    cout << ans << '\n';
    return 0;
}