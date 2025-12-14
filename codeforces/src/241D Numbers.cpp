//
// Created by Psy.C on 2025/12/14.
//
/*
*num函数：
计算数字x的位数对应的权重
例如：x=5返回10，x=12返回100，x=123返回1000
用于后续拼接数字时的模运算计算
 *
*f[x][i][j][k]: DP状态，表示考虑前x个数，异或和为i，拼接数字模p为j，k表示是否已经选过数
ys[N]: 记录原来数组中的索引位置
ans[N]: 存储答案序列
tot: 答案序列长度
p: 题目给定的除数
w[60]: 存储每个数字对应的位权
b[N]: 存储小于32的数字
 *
*DFS回溯函数：
从最终状态回溯构造方案
x: 当前考虑第几个数
y: 当前异或和
z: 当前拼接数字模p的值
c: 是否已选过数的状态
如果前一状态可达，则递归调用
否则说明当前数必须选择，记录到答案中
 *
*筛选出小于32的数字存储到b数组中
记录这些数字在原数组中的位置
计算每个数字对应的位权
 *
*初始状态：不选任何数，异或和为0，模p为0
对于每个数字，有两种选择：选或不选
选：异或和变为i^t，拼接后模p变为(j*w[t]+t)%p
不选：状态保持不变
注意只有选了数字后状态才标记为[1]
 *
*查找是否存在满足条件的方案（异或和为0，模p为0，且选过数字）
如果存在，调用DFS回溯构造具体方案并输出
否则输出"No"
 *
 *时间复杂度约为O(n × 32 × p)，适用于小规模数据
 *
*如果前一状态异或和为 prev_y
选择 b[x] 后，当前异或和为 y = prev_y^b[x]
那么前一状态的异或和就是 prev_y = y^b[x]
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=0;i<n;++i)
#define N 50050
#define M 32
using namespace std;

int num(int x) {
    int ret = 10;
    while (x >= 10) x /= 10, ret *= 10;
    return ret;
}

bool f[35][35][N][2];
int ys[N], ans[N], tot, p, w[60], b[N];
void dfs(const int x, const int y, const int z, const int c) {
    if (!x) return;
    if (f[x-1][y][z][c]) { dfs(x-1, y, z, c); return; }
    ans[++tot] = ys[x];
    rep(i,p) {
        if ((i*w[b[x]]+b[x])%p == z) {
            if (f[x-1][y^b[x]][i][0]) { dfs(x-1, y^b[x], i, 0); return; }
            if (f[x-1][y^b[x]][i][1]) { dfs(x-1, y^b[x], i, 1); return; }
        }
    }
}

int main() {
    fast;
    int n, a[N], tp = 0; cin >> n >> p;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) if (a[i] < M) {
        b[++tp] = a[i]; ys[tp] = i;
    }
    rep(i,M+1) w[i] = num(i);
    f[0][0][0][0] = true;
    rep(x,tp) {
        const int t = b[x+1];
        rep(i,M+1) rep(j,p) {
            if (f[x][i][j][1]) {
                f[x+1][i^t][(j*w[t]+t)%p][1] = true;
                f[x+1][i][j][1] = true;//不选择当前数字，但之前选过	状态保持[1]
            }
            if (f[x][i][j][0]) {
                f[x+1][i^t][(j*w[t]+t)%p][1] = true;//选择第(x+1)个数字
                f[x+1][i][j][0] = true;//不选择当前数字，之前也没选过	状态保持[0]
            }
        }
    }
    for (int i = 1; i <= tp; ++i) if (f[i][0][0][1]) {
        cout << "Yes\n";
        dfs(i, 0, 0, 1);
        cout << tot << '\n';
        for (int j = tot; j >= 1; --j) cout << ans[j] <<
            (j == 1 ? '\n' : ' ');
        return 0;
    }
    cout << "No\n";
    return 0;
}