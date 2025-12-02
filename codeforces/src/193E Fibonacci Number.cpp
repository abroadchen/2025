//
// Created by Psy.C on 2025/12/2.
//
/*
*N = 14: 答案数组大小
M = 2: 矩阵维度
 *
*A: 斐波那契转移矩阵 [[1,1],[1,0]]
st: 初始状态矩阵 [[1,0],[0,0]]
 *
*p: 当前位数的权值（10, 100, 1000...）
prod: 累积周期
 *
*枚举周期内的偏移量j
对于前一位的所有解x，检查prod*j+x是否满足当前位数要求
如果满足条件则加入当前位数的解集
继续直到找到周期结束条件
 *更新累积周期，如果没有找到解则输出-1
 *
*[F(n)  ]   [F(n-1) + F(n-2)]
 [F(n-1)] = [F(n-1)         ]
 *
*[F(n)  ]   [1 1] [F(n-1)]
 [F(n-1)] = [1 0] [F(n-2)]
 *
 *A^n × st = [[1,1],[1,0]]^n × [[1,0],[0,0]] = [[F(n+1),0],[F(n),0]]
 *t.arr[0][0] 就是 F(n+1)
 *
*当 j = 0 时，指数为 1 + prod * 0 = 1
A^1 = A（转移矩阵本身）
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for(ll i=0;i<n;++i)
using namespace std;

constexpr int N = 14, M = 2;
constexpr __int128 mod = 1e14;
vector<ll> ans[N];//不同位数下的可能答案

class Matrix {
public:
    __int128 arr[M][M];
    Matrix operator*(const Matrix& o) const {
        Matrix res{};
        rep(i,M) rep(j,M) {
            rep(k,M) res.arr[i][j] += arr[i][k] * o.arr[k][j];
            res.arr[i][j] %= mod;
        }
        return res;
    }
    Matrix operator%(const ll o) const {
        Matrix res{};
        rep(i,M) rep(j,M) res.arr[i][j] = arr[i][j] % o;//对矩阵每个元素取模
        return res;
    }
    bool operator==(const Matrix& o) const {
        rep(i,M) rep(j,M) if (arr[i][j] != o.arr[i][j]) return false;
        return true;//逐元素比较矩阵是否相等
    }
    bool operator!=(const Matrix& o) const {
        return !(*this == o);
    }
};
Matrix E = {
    1, 0,
    0, 1
};

Matrix quickPow(const Matrix& a, const ll x) {//计算矩阵a的x次幂
    if (x == 0) return E;//0次幂为单位矩阵，1次幂为自身
    if (x == 1) return a;
    const Matrix t = quickPow(a, x>>1);//先计算a^(x/2)，平方后如果x为奇数再乘以a
    Matrix res = t * t;
    if (x & 1) res = res * a;
    return res;
}
constexpr Matrix A = {1, 1, 1, 0},
st{1, 0, 0, 0};

int main() {
    fast;
    ll f; cin >> f;//目标值
    if (f == 0) { cout << 0 << '\n'; return 0; }
    if (f == 1) { cout << 1 << '\n'; return 0; }
    ll p = 10, prod = 1;
    ans[0].push_back(0);//0是斐波那契数列第0项
    for (int i = 1; i < N; ++i, p *= 10) {
        int j = 0; bool flag = true;
        do {
            for (const ll x : ans[i - 1]) {//遍历前一个位数的所有解
                const Matrix t = quickPow(A, prod * j + x) * st % (p * 10);
                if (t.arr[0][0] % p == f % p) {//这个数的末尾几位是否等于目标值 f 的末尾几位
                    ans[i].push_back(j * prod + x);
                    flag = false;
                }
            }
        } while (quickPow(A, 1 + prod * (++j)) * st % p != A * st);
        prod *= j;
        if (flag) { cout << -1 << '\n'; return 0; }
    }
    cout << ans[N - 1][0] + 1 << '\n';//索引从1开始
    return 0;
}