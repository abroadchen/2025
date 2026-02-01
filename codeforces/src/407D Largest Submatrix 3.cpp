//
// Created by Psy.C on 2026/2/1.
//
/**
* f[l][r]：在第i行，区间[l,r]的最优起始行号
pre[j][val]：第j列值为val时最后出现的行号
 *
*第一层：行号i
遍历每一行作为当前处理行
第二层：区间长度d
固定区间长度d，处理所有长度为d的区间
第三层：区间位置[l,r]
l：区间左端点
r：区间右端点，r = l + d - 1
 *
 *单个元素区间：更新为该元素最后出现的行号
 *区间两端值相同：整个区间有效，起始行为当前行i
*一般情况：取多种可能性的最大值
f[l][r]：保持原值
f[l][r-1]：不包含右端点的最优值
f[l+1][r]：不包含左端点的最优值
pre[r][a[i][l]]：右端列中左端值的最后出现行
pre[l][a[i][r]]：左端列中右端值的最后出现行
 *
*计算矩形面积：高度 × 宽度
高度：i - f[l][r]（从起始行到当前行）
宽度：r - l + 1（区间长度）
 *更新每一列各值的最后出现行号
 *
*时间复杂度：O(n × m²)
空间复杂度：O(m² + m × max_value)
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 402
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    int a[N][N];
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> a[i][j];
    int ans = 0, f[N][N], pre[N][N*N];
    for (int i = 1; i <= n; ++i) for (int d = 1; d <= m; ++d) {
        for (int l = 1, r = d; r <= m; ++l, ++r) {
            if (l == r) f[l][l] = max(f[l][l], pre[l][a[i][l]]);
            else if (a[i][l] == a[i][r]) f[l][r] = i;
            else f[l][r] = max({f[l][r], f[l][r-1], f[l+1][r],
                pre[r][a[i][l]], pre[l][a[i][r]]});
            ans = max(ans, (i-f[l][r])*(r-l+1));
        }
        for (int j = 1; j <= m; ++j) pre[j][a[i][j]] = i;
    }
    cout << ans << '\n';
    return 0;
}