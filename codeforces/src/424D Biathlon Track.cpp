//
// Created by Psy.C on 2026/2/4.
//
/**
* 预处理：O(n×m)
主循环：O(n²×m×log m)
总体：O(n²×m×log m)
 */
#include <iostream>
#include <set>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 333
#define rep(i,n) for (i = 1; i < n; ++i)
using namespace std;

int t, x11, x2, y11, y2;//最佳解的四个坐标
ll ans;//最接近目标值的计算结果
inline void sett(const ll x, const int i, const int j, const int a, const int b) {
    //当前结果x与目标t的差距是否小于已知最佳结果ans与t的差距
    if (!ans || abs(x - t) < abs(ans - t)) {//ans未初始化 当前结果更接近目标值t，则更新
        ans = x; x11 = i; x2 = j; y11 = a; y2 = b;
    }
}

int tp, tu, td;
inline int get(const int x, const int y) {//两个相邻元素的关系返回不同权重
    if (x == y) return tp;
    if (x > y) return tu;
    return td;
}


int main() {
    fast;
    int n, m; cin >> n >> m >> t >> tp >> tu >> td;//矩阵尺寸、目标值和三种权重
    int a[N][N]{}, i, j, k; ll pre[N][N][4]{};
    rep(i,n+1) rep(j,m+1) cin >> a[i][j];
    //当前位置的左方向前缀和 = 前一位置的左方向前缀和 + 相邻元素权重
    rep(i,n+1) for (j = 2; j < m+1; ++j) pre[i][j][0] = pre[i][j-1][0]+get(a[i][j], a[i][j-1]);//左
    rep(i,n+1) rep(j,m) pre[i][j][2] = pre[i][j-1][2] + get(a[i][j], a[i][j+1]);//右
    rep(j,m+1) for (i = 2; i < n+1; ++i) pre[i][j][1] = pre[i-1][j][1] + get(a[i][j], a[i-1][j]);//上
    rep(j,m+1) rep(i,n) pre[i][j][3] = pre[i-1][j][3] + get(a[i][j], a[i+1][j]);//下
    rep(i,n+1) for (j = i + 2; j < n + 1; ++j) {//选择两行i和j，其中j > i + 1（至少间隔一行）确保能形成有效的矩形
        set<pair<ll, int>> s;//前缀和值, 列索引
        rep(k,m+1) {
            if (k - 2 >= 1) {//k ≥ 3时执行，确保有足够的列形成矩形
                int c = k - 2;//左边界列索引
                ll x = -pre[i][c][0] - pre[j][c-1][2] + pre[j-1][c][3] - pre[i-1][c][3];
                s.insert({x, c});
            }
            if (!s.empty()) {//至少有两个列可用于形成矩形
                const ll res = pre[i][k][0] + pre[j][k-1][2] + pre[j][k][1] - pre[i][k][1], c = t - res;//目标值减去当前k的贡献
                auto tmp = s.lower_bound({c, 0});//≥c的元素
                if (tmp != s.end()) sett(res + tmp->first, i, j, tmp->second, k);
                if (tmp != s.begin()) {//不是第一个元素，检查前一个元素
                    --tmp;
                    sett(res + tmp->first, i, j, tmp->second, k);
                }
            }
        }
    }
    cout << x11 << ' ' << y11 << ' ' << x2 << ' ' << y2 << '\n';
    return 0;
}