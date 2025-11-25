//
// Created by Psy.C on 2025/11/24.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0); \
    cin.tie(nullptr); cout.tie(nullptr)
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

typedef long long ll;
constexpr int N = 4005, mod = 998244353;
int f[2][N][N];

void add(int& x, const int y) { x = (x + y) % mod; }
int mul(const int a, const int b) { return static_cast<int>(1ll * a * b) % mod; }

int main() {
    fast;
    int n, k; cin >> n >> k; f[0][0][0] = 1;
    rep(i,n) {
        rep(c,i/k+1) rep(x,k) f[i + 1 & 1][x][c] = 0;
        rep(c,i/k+1) {
            vector<int> g(k + 1);
            rep(x,k) {
                if (x < k - 1) {
                    const int val = mul(f[i & 1][x][c], k - x);
                    add(f[i + 1 & 1][x + 1][c], val);
                } else add(f[i + 1 & 1][0][c + 1],
                    f[i & 1][x][c]);
                add(g[x], f[i & 1][x][c]);
            }
            for (int x = k - 1; x; --x) add(f[i + 1 & 1][x][c],
                g[x]), add(g[x - 1], g[x]);
        }
    }
    int ans = 0;
    rep(x,k) rep(c,n/k+1) {
        const int t = mul(f[n & 1][x][c], c);
        add(ans, t);
    }
    cout << ans;
    return 0;
}