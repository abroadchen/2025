//
// Created by Psy.C on 2025/12/21.
//
/*
*n: 节点数，m: 边数
l[], r[]: 边的起点和终点数组
v[][]: 两点间最小电阻值
dt[][]: 两点间边的数量
x[]: 边的电阻值
f[][]: 线性方程组系数矩阵
sn[]: 各节点电势值
bh[][]: 各边电流值
 *
*根据基尔霍夫电流定律构建方程组
对于每个中间节点i（非首尾节点）：
f[i][i]: 自导纳（连接到节点i的边数）
f[i][j]: 互导纳（负的连接边数）
f[i][n-1]: 常数项（与节点0的关联）
*使用高斯消元法求解线性方程组
tot = n-2: 变量个数（除去首尾两个节点）
部分主元法避免除零错误
行变换化为上三角矩阵
*将矩阵化为简化行阶梯形式
提取解向量sn[]（各节点电势）
 *
 *设定起始节点电势为1
*计算使得所有电流不超过对应电阻值的比例因子
mn: 最大允许的比例因子
*根据欧姆定律计算各边电流：I = V/R × 比例因子
计算从节点0流出的总电流
 *输出总电流和各边电流（保留5位小数）
 */
#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 105
#define eps 1e-15
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    int l[N*N], r[N*N], v[N][N], dt[N][N];
    double x[N*N], f[N][N], sn[N], bh[N][N];
    for (int i = 0, a, b, c; i < m; ++i) {
        cin >> a >> b >> c; a--; b--;
        l[i] = a; r[i] = b; x[i] = c;
        if (v[a][b] == 0) v[a][b] = c;//维护两点间的最小电阻值
        else v[a][b] = min(v[a][b], c);
        dt[a][b]++; dt[b][a]++;//更新度数矩阵
    }
    //拉普拉斯矩阵
    for (int i = 1; i < n - 1; ++i) {//遍历中间节点（从节点1到节点n-2，因为节点0和n-1是特殊节点）
        for (int j = 0; j < n; ++j) if (dt[j][i]) {
            f[i][i] += dt[j][i], f[i][j] -= dt[j][i];// 系数矩阵对角线元素累加度数 非对角线元素减去度数
        }
        f[i][n-1] = -f[i][0];//第i个方程的右侧常数
    }
    const int tot = n - 2;//需要求解的变量个数
    for (int i = 1; i <= tot; ++i) {//遍历每个方程（从1到tot）
        int t = i;//寻找第i列中非零元素所在的行 从i开始向下寻找
        while (!static_cast<bool>(f[t][i]) && t <= tot) t++;//f[t][i]为0且t未超出范围，则继续寻找
        if (t > tot) continue;//如果找不到非零主元，则跳过当前列
        for (int j = i; j <= tot + 1; ++j) swap(f[i][j], f[t][j]);//交换第i行和第t行，将非零主元移到对角线上
        for (int j = 1; j <= tot; ++j) if (j != i) {//对其他行进行消元
            const double tt = f[j][i] / f[i][i];//消元系数
            for (int k = 1; k <= tot + 1; ++k) f[j][k] -= tt * f[i][k];//对该行的每个元素进行行变换
        }
    }
    //解的规范化
    for (int i = 1; i <= tot; ++i) {//遍历每个变量（从1到tot）
        if (f[i][i] == 0) continue;//如果对角线元素为0，跳过该行
        for (int j = 1; j <= tot + 1; ++j) {//将该行除以对角线元素，使对角线元素变为1
            if (j == i) continue;//跳过对角线元素本身
            f[i][j] /= f[i][i];
        }
        f[i][i] = 1;//显式设置对角线元素为1
        sn[i] = f[i][tot+1];//提取解向量：sn[i]等于增广矩阵最后一列的值
    }
    sn[0] = 1;//起始节点（节点0）的电势为1（参考电势）
    double mn = 1008610086;//最小比例因子
    for (int i = 0; i < m; ++i) {//遍历每条边
        if (abs(sn[l[i]] - sn[r[i]]) < eps) continue;//两端点电势差几乎为0
        if (sn[l[i]] > sn[r[i]]) mn = min(mn, x[i] / (sn[l[i]]-sn[r[i]]));//确保分母为正值
        else mn = min(mn, x[i] / (sn[r[i]]-sn[l[i]]));
    }
    double ans = 0;//总电流
    for (int i = 0; i < m; ++i) bh[l[i]][r[i]] = mn * (sn[l[i]]-sn[r[i]]);//每条边的电流
    for (int i = 0; i < m; ++i) {//遍历每条边计算总电流
        if (l[i] == 0) ans += bh[l[i]][r[i]];//边的起点是节点0，电流流入，加上该电流
        if (r[i] == 0) ans -= bh[l[i]][r[i]];//边的终点是节点0，电流流出，减去该电流
    }
    cout << fixed << setprecision(5) << ans << '\n';
    for (int i = 0; i < m; ++i) cout << fixed << setprecision(5) << bh[l[i]][r[i]] << '\n';
    return 0;
}