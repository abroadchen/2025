//
// Created by Psy.C on 2025/12/20.
//
/*
*枚举所有可能的中心点(i,j)
坐标变换得到(x,y)
计算以(i,j)为中心、大小为k的菱形区域的值
通过累加多个矩形区域来计算菱形区域的和
更新最大值及对应位置
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 2007
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
template<class T, class V>
bool maxx(T& a, V b) { return a < b ? a = b, true : false; }//如果b大于a则更新a并返回true，否则返回false
ll b[N][N];//前缀和数组
ll get(const int x1, const int x2, const int y1, const int y2) {//矩形区域[x1,x2]×[y1,y2]的和
    return b[x2][y2] - b[x2][y1-1] - b[x1-1][y2] + b[x1-1][y1-1];
}

int main() {
    fast;
    int n, m, k; cin >> n >> m >> k;
    int a[N][N];
    rep(i,n) rep(j,m) {
        cin >> a[i][j];
        b[i+j][i-j+m] = a[i][j];//将原矩阵a映射到前缀和数组b中
    }
    rep(i,n+m) rep(j,n+m) b[i][j] += b[i-1][j] + b[i][j-1] - b[i-1][j-1];//构建二维前缀和数组
    ll ans = -inf, ret = 0;
    int idx = 0, idy = 0, x, y;
    for (int i = k; i <= n - k + 1; ++i) for (int j = k; j <= m - k + 1; ++j) {
        x = i + j, y = i - j + m; ret = 0;
        for (int z = 0; z < k; ++z) ret += get(x - z, x + z, y - z, y + z);
        if (maxx(ans, ret)) idx = i, idy = j;
    }
    cout << idx << ' ' << idy << '\n';
    return 0;
}