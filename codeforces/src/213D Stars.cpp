//
// Created by Psy.C on 2025/12/6.
//
/*
*使用复数pt表示二维点坐标
pi = acos(-1)：圆周率
sd：计算得到的边长参数
ag：计算得到的角度参数
p[N]：存储所有点的坐标
ans[]：存储绘制顺序
len：当前点的数量
cnt：绘制指令计数
*36./180*pi：36度转换为弧度
cos(36°)*10*2：基于正五边形的几何计算
2 * asin(5/sd)：计算特定角度
 *
*递归生成图形：
num[tp].p[0] = tp：记录当前图形索引
p[len] = {real(s) + sd, imag(s)}：生成第一个点（向右平移sd距离）
记录点索引并更新计数器
 *递归处理下一个层级，从新生成的点开始。
 *生成第二个点：从参考点按角度ag和距离sd生成
 *继续生成第三、四个点，使用角度ag/2进行偏移
 *添加返回指令
 *
 *输出所有点的坐标
 *输出每个图形的点连接顺序（索引加1）
 *输出绘制指令序列
 *时间复杂度：O(5^n)，空间复杂度：O(5^n)
 */
#include <iostream>
#include <complex>
#include <iomanip>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pt complex<double>
using namespace std;

constexpr int N = 1000, M = 200;
const double pi = acos(-1.), sd = cos(36./180*pi)*10*2, ag = 2 * asin(5/sd);
int n, ans[N<<1], len, cnt;
pt p[N];

struct node { int p[5]; } num[M];
void dfs(const int tp, const pt& s) {
    if (tp == n) return;
    num[tp].p[0] = tp;
    p[len] = {real(s) + sd, imag(s)};
    num[tp].p[1] = len;
    ans[cnt++] = len++;
    dfs(tp + 1, p[len - 1]);
    p[len] = {
        real(p[tp+1]) - cos(ag) * sd,
        imag(p[tp+1]) - sin(ag) * sd
    };
    num[tp].p[2] = len;
    ans[cnt++] = len++;
    p[len] = {
        real(p[len-1]) + sin(ag/2) * sd,
        imag(p[len-1]) + cos(ag/2) * sd
    };
    num[tp].p[3] = len;
    ans[cnt++] = len++;
    p[len] = {
        real(p[len-1]) + sin(ag/2) * sd,
        imag(p[len-1]) - cos(ag/2) * sd
    };
    num[tp].p[4] = len;
    ans[cnt++] = len++;
    ans[cnt++] = tp;
}

int main() {
    fast;
    ans[0] = 0; p[0] = {0, 0};
    while (cin >> n) {
        cnt = len = 1;
        dfs(0, p[0]);
        cout << len << '\n';
        for (int i = 0; i < len; ++i) cout << fixed << setprecision(11) <<
            real(p[i]) << ' ' << setprecision(11) << imag(p[i]) << '\n';
        for (int i = 0; i < n; ++i) {
            const int *t = num[i].p;
            for (int& j : num[i].p) j++;
            cout << t[0] << ' ' << t[3] << ' ' << t[1] << ' ' <<
                t[4] << ' ' << t[2] << '\n';
        }
        for (int i = 0; i < cnt; ++i) cout << ans[i] + 1 << ' ';
        cout << '\n';
    }
    return 0;
}