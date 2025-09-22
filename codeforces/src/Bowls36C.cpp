//
// Created by Psy.C on 2025/9/22.
//

#include <cstdio>
#include <iomanip>
#include <iosfwd>
#include <iostream>
#include <vector>
using namespace std;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n; cin >> n;// 读取圆台个数n
    double ans = 0;
    vector<double> h(n), r(n), R(n);// 声明三个向量存储高度、上底半径、下底半径
    for (int i = 0; i < n; ++i) cin >> h[i] >> r[i] >> R[i];

    vector<double> dp(n);// dp[i]表示以第i个圆台为最上面的圆台时能达到的最大高度
    for (int i = 0; i < n; ++i) {// 遍历每个圆台作为当前最上面的圆台
        for (int j = 0; j < i; ++j) {// 检查之前的所有圆台
            double x = 0;// 初始化叠加高度为0
            if (r[i] >= R[j]) x = h[j];// 如果上面圆台的上底半径≥下面圆台的下底半径，完全覆盖
            else {// 计算部分覆盖时的叠加高度
                x = max({0., (r[i] - r[j]) / (R[j] - r[j]) * h[j],
                min((R[i] - r[j]) / (R[j] - r[j]) * h[j] - h[i],
                    h[j] - (R[j] - r[i]) / (R[i] - r[i]) * h[i])});
            }
            dp[i] = max(dp[i], dp[j] + x);
        }
        ans = max(ans, dp[i] + h[i]);// 更新全局最大高度
    }

    cout << fixed << setprecision(10);// 设置输出格式为固定小数点后10位
    cout << ans << "\n";


    return 0;
}