//
// Created by Psy.C on 2026/1/27.
//
/**
* 1.为了方便取模，把x、y轴都改成从0开始，最后加1即可。设（sx[t], sy[t]）为t时刻的位置，（dx[t], dy[t]）为从t-1到t时间段的速度（偏移量），根据题意，可得：

dx[t] = dx[t-1] + sx[t-1] +1 + sy[t-1]+1 + t-1

dy[t] = dy[t-1] + sx[t-1] +1 + sy[t-1]+1 + t-1

sx[t] = sx[t-1] +  dx[t-1] + sx[t-1] +1 + sy[t-1]+1 + t-1

sy[t] = sy[t-1] +  dy[t-1] + sx[t-1] +1 + sy[t-1]+1 + t-1

2.根据上述递推式，构造矩阵求解即可
 *
 *
 *
*n: 模数
sx, sy: 起始坐标
dx, dy: 方向向量
t: 时间步数
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 6
using namespace std;


struct node {
    ll mat[N][N];
    void init() {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                mat[i][j] = i == j;//单位矩阵（对角线为1，其余为0）
    }
};

int mod;
node mul(const node &x, const node &y) {//矩阵乘法函数
    node ret{};
    memset(ret.mat, 0, sizeof(ret.mat));//矩阵所有元素置为0
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                ret.mat[i][j] += (1ll * x.mat[i][k] * y.mat[k][j]%mod+mod)%mod,
                    ret.mat[i][j] %= mod;
    return ret;
}

node pw(node x, ll y) {//矩阵快速幂函数
    node s{}; s.init();
    while (y) {
        if (y&1) s = mul(s, x);
        x = mul(x, x);
        y >>= 1;
    }
    return s;
}

//递推关系的转移矩阵
node tmp = {
    1, 0, 1, 1, 1, 2,
    0, 1, 1, 1, 1, 2,
    1, 0, 2, 1, 1, 2,
    0, 1, 1, 2, 1, 2,
    0, 0, 0, 0, 1, 1,
    0, 0, 0, 0, 0, 1
};


int main() {
    fast;
    ll n, sx, sy, dx, dy, t; cin >> n >> sx >> sy >> dx >> dy >> t;
    mod = static_cast<int>(n);
    auto s = tmp; s = pw(s, t); sx--; sy--;//将坐标从1基转换为0基
    const ll a[6] = {dx, dy, sx, sy, 0, 1};//初始状态向量
    sx = sy = 0;//重置 sx 和 sy 为0
    for (int i = 0; i < N; ++i) {
        sx += (1ll * s.mat[2][i] * a[i] % mod + mod) % mod, sx %= mod;//转换矩阵的第2行
        sy += (1ll * s.mat[3][i] * a[i] % mod + mod) % mod, sy %= mod;
    }
    cout << sx + 1 << ' ' << sy + 1 << '\n';//从0基转换回1基并输出
    return 0;
}