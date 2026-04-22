//
// Created by Psy.C on 2026/4/21.
//
/**
per.a[j][i^j] = t 表示从状态j转移到状态(i^j)的概率为t
经过n次转移后，ans.a[0][0]表示回到状态0的概率
1.0 - ans.a[0][0]表示不回到状态0的概率

矩阵乘法：O(N³) 但因为稀疏性实际更快
快速幂：O(log n)
总体：O(N³ log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 128;
struct node {
    double a[N][N]{};
    int n{}, m{};
    node() { memset(a, 0, sizeof(a)); }
    node operator*(const node& o) const {
        node r; r.n = n; r.m = o.m;
        for (int i = 0; i <= r.n; ++i)
            for (int j = 0; j <= r.m; ++j)
                if (a[i][j])//只处理非零元素
                    for (int k = 0; k <= m; ++k)
                        r.a[i][k] += a[i][j]*o.a[j][k];
        return r;
    }
} per, ans;

int k;
node ksm(int y) {
    node r; r.n = r.m = N-1;
    for (int i = 0; i <= r.n; ++i) r.a[i][i] = 1;//初始化为单位矩阵
    while (y) {
        if (y&1) r = r*per;//乘以当前矩阵
        per = per*per;//矩阵平方
        y >>= 1;
    }
    return r;
}

int x;
double t;
void init() {
    per.n = per.m = N-1;
    for (int i = 0; i <= x; ++i) {
        cin >> t;
        for (int j = 0; j < N; ++j)
            per.a[j][i^j] = t;//对于每个i，将t赋值到第j行、第(i^j)列
    }
}

int n;
int main() {
    fast;
    cin >> n >> x; init();
    ans = ksm(n);
    printf("%.10f\n", 1.-ans.a[0][0]);
    return 0;
}