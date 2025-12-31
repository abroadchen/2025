/**
 *
*C[N][N]：组合数表，C[i][j]表示从i个元素中选j个的组合数
A[N][N][N][N]：预计算的系数数组
 *C(i,j) = C(i-1,j) + C(i-1,j-1)，边界条件C[i][0]=1
 *A[a][b][c][d] = C[a][c] * C[b][d] % mod
 *循环读入n个元素，如果元素值为50则X加1，否则Y加1
 *
第一个状态转移：从dp[i-1][x][y]转移到dp[i][x-a][y-b]，
选择a个50和b个100，满足a或b至少一个非0且总值不超过k
 *如果到达目标状态(0,0)，输出步数和方案数并结束程序
 *第二个状态转移：从dp[i][x][y]转移到dp[i+1][x+a][y+b]，增加a个50和b个100
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define ll long long
#define N 55
#define mod 1000000007
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

int main() {
    fast;
    ll C[N][N], A[N][N][N][N], dp[N<<2][N][N];
    rep(i,N) for (int j = C[i][0] = 1; j <= i; ++j) C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
    rep(a,N) rep(b,N) rep(c,a+1) rep(d,b+1) A[a][b][c][d] = C[a][c] * C[b][d] % mod;
    int n, k, X = 0, Y = 0, t; cin >> n >> k;
    rep(i,n) cin >> t, ++(t == 50 ? X : Y); dp[0][X][Y] = 1;
    for (int i = 1; i <= (n<<2)+1; i += 2) {
        rep(x,X+1) rep(y,Y+1) if (dp[i-1][x][y]) {
            rep(a,x+1) rep(b,y+1) if ((a|b) && a * 50 + b * 100 <= k) {
                (dp[i][x-a][y-b] += A[x][y][a][b] * dp[i-1][x][y]) %= mod;
            }
        }
        if (dp[i][0][0]) return cout << i << '\n' << dp[i][0][0] << '\n', 0;
        rep(x,X+1) rep(y,Y+1) if (dp[i][x][y]) {
            rep(a,X-x+1) rep(b,Y-y+1) if ((a|b) && a * 50 + b * 100 <= k) {
                (dp[i+1][x+a][y+b] += A[X-x][Y-y][a][b] * dp[i][x][y]) %= mod;
            }
        }
    }
    cout << "-1\n0\n";
    return 0;
}