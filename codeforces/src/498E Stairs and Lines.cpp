//
// Created by Psy.C on 2026/2/23.
//
///O(log n)
/**
j 和 k 是矩阵的行和列索引，同时也代表某种状态（每个位表示某种属性）
l 是中间状态，范围是 0 到 2^i - 1，表示第i层的所有可能状态
(j&(1<<i1)) 表示检查j的第i1位是否为1

当j和k的第i1位都为1时（意味着这两个状态在同一位置都有某种特征），需要检查中间层l是否有冲突
如果同一列相邻两个位置都"被占用"，那么中间层的配置会产生冲突
不同位置有不同的冲突规则：
i1 == 0（第一个位置）：如果l的对应位为1，则冲突
i1 == i（最后一个位置）：如果l的前一位为1，则冲突
中间位置：如果l的当前位和前一位都为1，则冲突

第0轮：只需要考虑2个状态（宽度2）
第1轮：需要考虑4个状态（宽度4）
第2轮：需要考虑8个状态（宽度8）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for (int i = 0; i < n; ++i)
using namespace std;
constexpr int N = 1300, M = 7, mod = 1e9+7;
struct node {
    ll a[N][N];
    int x, y;
} m0, p;

node mul(const node &a, const node &b) {
    node res{};
    rep(i,a.x) rep(j,b.y) {
        int t = 0;
        rep(k,a.y) t = (t+a.a[i][k]*b.a[k][j]%mod)%mod;
        res.a[i][j] = t;
    }
    res.x = a.x; res.y = b.y;//结果矩阵的大小是 a.x × b.y
    return res;
}

node ksm(node m, const int n) {
    node res{};
    memset(res.a, 0, sizeof(res.a));
    rep(i,m.x) res.a[i][i] = 1;
    res.x = res.y = m.x;
    for (int i = 1; i <= n; i<<=1) {
        if (i&n) res = mul(res, m);
        m = mul(m, m);
    }
    return res;
}

int a[M];
int main() {
    fast;
    for (int& i : a) cin >> i;
    ///m0矩阵为1×2的行向量 [0, 1]
    m0.x = 1; m0.y = 2; m0.a[0][0] = 0; m0.a[0][1] = 1;
    rep(i,M) {
        p.x = p.y = 1<<(i+1);//2^(i+1) × 2^(i+1)的转移矩阵p
        rep(j,p.y) rep(k,p.x) {
            int cnt = 0;
            rep(l,1<<i) {
                int flag = 1;
                if (i == 0 && j == 1 && k == 1) flag = 0;
                rep(i1,i+1) {
                    if ((j&(1<<i1)) && (k&(1<<i1))) {
                        if (i1 == 0 && (l&(1<<i1))) {
                            flag = 0;
                            break;
                        }
                        if (i1 == i && (l&(1<<(i1-1)))) {
                            flag = 0;
                            break;
                        }
                        if (i1 > 0 && i1 < i && (l&(1<<i1)) && (l&(1<<(i1-1)))) {
                            flag = 0;
                            break;
                        }
                    }
                }
                cnt += flag;
            }
            p.a[k][j] = cnt;
        }
        m0 = mul(m0, ksm(p, a[i]));
        const int k = 1<<(i+1);
        rep(j,m0.y) {
            m0.a[0][j+k] = m0.a[0][j];
            m0.a[0][j] = 0;
        }
        m0.y <<= 1;
    }
    cout << m0.a[0][m0.y-1] << '\n';
    return 0;
}