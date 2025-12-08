//
// Created by Psy.C on 2025/12/7.
//
/*
*n, m：网格的行数和列数
s：总面积参数
r：用于计算的临时变量
ans：存储最终结果的长整型变量
 *
*计算在n×m网格中可以放置h×w大小矩形的位置数量
(n - h + 1)是垂直方向可放置位置数
(m - w + 1)是水平方向可放置位置数
 *
*外层循环：高度i从1开始，每次增加2（只考虑奇数高度）
内层循环：宽度j从1开始，每次增加2（只考虑奇数宽度）
条件(r = s - i * j) >= 0：确保当前i×j矩形的面积不超过总面积s
*当矩形面积恰好等于s时（r == 0）：
((i+1)*(j+1)/2-1)：计算i×j矩形中可以放置的特定模式数量
f(i,j)：计算该矩形在网格中可放置的位置数
将两者的乘积累加到答案中
*当还有剩余面积时（r > 0）：
内层循环遍历k从1到j-1的奇数值
条件r % (2 * k) == 0：检查剩余面积是否能被2*k整除
条件i + r / k <= n：确保扩展后的高度不超过网格高度
如果条件满足，将2 * f(i + r / k, j)累加到答案中（乘以2是因为两种对称情况）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n, m, s, r;
ll ans;

ll f(const int h, const int w) { return (n - h + 1) * (m - w + 1); }

int main() {
    fast;
    cin>>n>>m>>s; ans = 0;
    for (int i = 1; i <= n; i += 2) {
        for (int j = 1; j <= m && (r = s - i * j) >= 0; j += 2) {
            if (r == 0) ans += ((i+1)*(j+1)/2-1)*f(i,j);
            else {
                for (int k = 1; k < j; k += 2)
                    if (r % (2 * k) == 0 && i + r / k <= n)
                        ans += 2 * f(i + r / k, j);
            }
        }
    }
    cout << ans << '\n';
    return 0;
}