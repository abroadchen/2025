//
// Created by Psy.C on 2026/4/23.
//
/**
n：数组长度
m：颜色种类数
a[N]：输入数组
ans：每种颜色的理想数量
pos[N]：标记位置是否被占用
d[N]：记录每种颜色缺少的数量
res：总的需要调整的数量

对每种颜色i从1到m：
num = 0：统计当前颜色i的现有数量
遍历数组，找到颜色i的前ans个位置：
如果a[j] == i，增加计数并将位置j标记为已占用
找到ans个后就停止（即使后面还有该颜色）
如果现有数量小于理想数量：
d[i] = ans - num：记录缺少的数量
res += d[i]：累计总的缺失数量

重新分配缺少的颜色：
j = 1：从数组开头开始
对每种颜色i：
对于缺少的每个实例k：
while (pos[j]) j++：找到下一个未被占用的位置
a[j++] = i：将颜色i填入该位置
输出需要调整的数量
输出调整后的数组
O(n*m)，空间复杂度O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2007;
int n, m, a[N], ans, pos[N], d[N], res;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ans = n/m;
    cout << ans << ' ';
    for (int i = 1; i <= m; ++i) {
        int num = 0;
        for (int j = 1; j <= n; ++j) {
            if (a[j] == i) {
                num++;
                pos[j] = 1;
            }
            if (num == ans) break;
        }
        if (num < ans) {
            d[i] = ans - num;
            res += d[i];
        }
    }
    int j = 1;
    for (int i = 1; i <= m; ++i)
        for (int k = 0; k < d[i]; ++k) {
            while (pos[j]) j++;
            a[j++] = i;
        }
    cout << res << '\n';
    for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
    return 0;
}