//
// Created by Psy.C on 2026/10/8.
//
/**
a[i] 存候选对称轴的方向向量 (x,y)、极角 k，以及它对应的两个点编号 px,py。
operator== 判断两个方向向量是否共线（叉积为 0），用于把同角度的候选方向归到一组。
计算全部点的质心 (mx,my)。
用双重循环把"关于质心对称的两个点"标记消去 d，剩余的点存入 X,Y，个数为 t。
若 t<2 输出 -1（本题特判无解情形）
对剩余点两两取中点，求"中点 → 质心"的方向作为候选对称轴方向（atan2 得到极角 k）。
因为方向取反等价，统一归一化（dx<0 取反、单轴为 0 时取绝对值），再按极角排序
把所有同极角的候选方向归为一段 [lst, i]。
若这一段的中点数量 ≥ t/2（能覆盖足够多的点对），尝试用这些点对去配对剩余点（p 标记未覆盖），剩余孤立点 k 必须 ≤ t&1（即最多 1 个、且当 t 为奇数时该点要落在轴上）。
check 验证孤立点是否落在当前对称轴上
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-8
using namespace std;
constexpr int N = 2e3+5;

struct node { double x, y, k; int px, py; } a[N*N];
bool cmp(const node& A, const node& B) { return A.k < B.k; }
bool operator==(const node& A, const node& B) { return A.x*B.y == A.y*B.x; }

double mx, my;
int X[N], Y[N];
//判断点 X[x],Y[x] 相对于质心的向量是否与对称轴方向共线（叉积≈0），是则说明该点在轴上
bool check(int x, double b1, double b2) {
    double dx = my - Y[x], dy = -mx + X[x];
    return fabs(dy*b1 - b2*dx) < eps;
}

int x[N], y[N], d[N], t, cnt, lst, p[N], k, pos, ans;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> x[i] >> y[i], mx += x[i], my += y[i];
    mx/=n, my/=n;
    for (int i = 1; i < n; ++i) {
        if (!d[i]) {
            for (int j = i+1; j <= n; ++j)
                if (!d[j] && fabs(x[i]+x[j]-2*mx) < eps && fabs(y[i]+y[j]-2*my) < eps) {
                    d[i] = d[j] = 1; break;
                }
        }
    }
    for (int i = 1; i <= n; ++i)
        if (!d[i]) X[++t] = x[i], Y[t] = y[i];
    if (t < 2) return cout << "-1\n", 0;
    for (int i = 1; i < t; ++i)
        for (int j = i+1; j <= t; ++j) {
            double dx = my-(Y[i]+Y[j])/2.0, dy = -mx+(X[i]+X[j])/2.0;
            if (dx < 0) dx = -dx, dy = -dy;
            if (dx == 0) dy = fabs(dy);
            if (dy == 0) dx = fabs(dx);
            a[++cnt].x = dx, a[cnt].y = dy; a[cnt].px = i, a[cnt].py = j;
            a[cnt].k = atan2(dy, dx);
        }
    sort(a+1, a+cnt+1, cmp);
    lst = 1;
    for (int i = 1; i <= cnt; ++i) {
        if (i == cnt || a[i] != a[i+1]) {//一组同角度方向结束
            if (i-lst+1 >= t/2) {//该方向的中点对数足够覆盖 t/2
                for (int j = 1; j <= t; ++j) p[j] = 1;
                for (; lst <= i; ++lst)
                    if (p[a[lst].px] && p[a[lst].py])
                        p[a[lst].px] = p[a[lst].py] = 0;//用这些中点两两覆盖点
                k = 0;
                for (int j = 1; j <= t; ++j)
                    if (p[j]) k++, pos = j;//剩余未覆盖的孤立点
                if (k > (t&1)) continue;//孤立点过多则不可行
                if (!k || check(pos, a[i].x, a[i].y)) ans++;//覆盖完或单点落在轴上 → 可行
            }
            lst = i+1;
        }
    }
    cout << ans << '\n';
    return 0;
}