//
// Created by Psy.C on 2025/12/27.
//
/*
* q：某个范围参数
a, b：约束条件的上下界
x[N]：输入数组
dp[N]：动态规划数组
 *
*i：当前处理的位置
l, r：当前搜索范围的左右边界
A, B：二次函数的系数（用于求最值点）
cyr：二次函数Ax^2 + Bx的最值点（导数为0的点）
 *
 *如果是第一个元素或者最值点在约束范围内，直接返回最值点
*如果最值点小于下界，递归到左边并加a
否则递归到右边并加b
这里是在调整约束范围并更新二次函数系数
 *
*如果x[i]在约束范围内，直接使用
否则使用dfs函数找到最优值
*res：从dp[n]开始反向构造答案
y[N]：存储最终结果数组
ans：总的目标函数值
*从后往前构造y数组
计算目标函数值
根据约束条件反向推导前一个值
 *
*1. i-1
含义：递归到前一个位置
作用：从位置i转移到位置i-1
2. l-a, r-a
含义：将搜索范围平移
原因：由于约束条件是 y[i] - y[i-1] >= a，即 y[i-1] <= y[i] - a
当前最优值是y[i]，那么y[i-1]的上界就是y[i] - a
所以原范围[l, r]变为[l-a, r-a]
3. A+1
含义：二次项系数增加1
数学背景：原始目标函数包含 (y[i] - x[i])² 项
当我们用 y[i] = y[i-1] + a 替换y[i]时，目标函数变为： (y[i-1] + a - x[i])² + ... = (y[i-1] - (x[i] - a))² + ...
递归时，每一层都会增加一个 (y[j] - 某值)² 项，所以A系数递增
4. B-2*x[i-1]+2*a*A
含义：线性项系数的更新
数学推导：当我们把y[i]替换为y[i-1]+a时，目标函数中的项会变化
原来有 A*y[i]² + B*y[i]，现在y[i] = y[i-1] + a
代入后得到：A*(y[i-1]+a)² + B*(y[i-1]+a)
展开：A*y[i-1]² + 2*A*a*y[i-1] + A*a² + B*y[i-1] + B*a
合并同类项：A*y[i-1]² + (2*A*a + B)*y[i-1] + 常数项
所以新的线性系数是 B + 2*A*a
但这里的公式是 B-2*x[i-1]+2*a*A，这表明在该问题的特定情况下，B项还包含了 -2*x[i-1] 的部分
 */
#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ld long double
#define N 6005
using namespace std;

constexpr ld eps = 1e-8;
bool lt(const ld x, const ld y) { return x + eps < y; }
bool gt(const ld x, const ld y) { return x > y + eps; }
bool le(const ld x, const ld y) { return x < y + eps; }

int q, a, b, x[N];
ld dp[N];
ld dfs(const int i, ld l, ld r, const ld A, const ld B) {
    if (lt(l, 1)) l = 1;
    if (lt(q, r)) r = q;
    ld cyr = -B / (2 * A);
    if (lt(r, cyr)) cyr = r;//将最值点限制在区间[l, r]内
    if (lt(cyr, l)) cyr = l;
    if (i == 1 || (le(dp[i-1]+a, cyr) && le(cyr, dp[i-1]+b))) return cyr;
    if (gt(dp[i-1]+a, cyr)) return dfs(i-1,l-a,r-a,A+1,B-2*x[i-1]+2*a*A)+a;
    return dfs(i-1,l-b,r-b,A+1,B-2*x[i-1]+2*b*A)+b;
}


int main() {
    fast;
    int n; cin >> n >> q >> a >> b;
    for (int i = 1; i <= n; ++i) cin >> x[i]; dp[1] = x[1];
    for (int i = 2; i <= n; ++i) {
        if (le(dp[i-1]+a, x[i]) && le(x[i], dp[i-1]+b)) dp[i] = x[i];
        else if (gt(dp[i-1]+a, x[i])) dp[i] = dfs(i,1,q,1,-2*x[i]);
        else dp[i] = dfs(i,1,q,1,-2*x[i]);
    }
    ld res = dp[n], y[N], ans = 0;
    cout << fixed << setprecision(8);
    for (int i = n; i >= 1; --i) {
        y[i] = res;
        ans += (res - x[i]) * (res - x[i]);
        if (gt(dp[i-1]+a, res)) res = res - a;
        else if (gt(res, dp[i-1]+b)) res = res - b;
        else res = dp[i-1];
    }
    for (int i = 1; i <= n; ++i) cout << y[i] << ' ';
    cout << '\n';
    cout << ans << '\n';
    return 0;
}