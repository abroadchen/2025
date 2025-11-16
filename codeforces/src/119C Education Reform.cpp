//
// Created by Psy.C on 2025/11/16.
//
/*
*n: 目标序列长度
m: 状态种类数
k: 操作参数
c[100]: 每种状态的优先级/成本
mem[N][N][M]: DP记忆化数组
a[N], b[N]: 每种状态的数值范围
nxt[N][N][M]: 记录转移的下一个状态
nxta[N][N][M]: 记录转移的下一个数值
 *
 *dp(i, cnt, x)表示从状态i开始构造长度为cnt的序列，当前值为x时的最大得分
*如果x超出状态i的范围，返回-2（无效状态）
如果只需要构造1个元素，返回当前值x
*计算相对于下界的偏移量ans
如果该状态已计算过，直接返回记忆化结果
*枚举所有优先级更高的状态j（c[j] > c[i]）
尝试两种操作：
加法操作：转移到状态j，数值变为x+k
乘法操作：转移到状态j，数值变为x*k
记录能得到最大值的转移路径
*如果能找到有效转移，则加上当前值x
记忆化存储并返回结果
 *
*枚举所有可能的起始状态和起始值
寻找能得到最大得分的方案
 *
*按照记录的转移路径输出构造方案
从起始状态开始，逐步追踪到结束
 *
 *O(m × (max_range) × n × m) 其中max_range是数值范围
 */
#include <cstring>
#include <iostream>
using namespace std;

typedef long long ll;
const int N = 60, M = 110;
int n, m, k, c[100];
ll mem[N][N][M], a[N], b[N],
nxt[N][N][M], nxta[N][N][M];

ll dp(int i, int cnt, ll x) {
    if (x < a[i] || x > b[i]) return -2;
    if (cnt == 1) return x;
    int ans = x - a[i];
    if (mem[i][cnt][ans] != -1) return mem[i][cnt][ans];
    ll mx(-2), t;
    for (int j = 0; j < m; ++j) {
        if (c[j] > c[i]) {
            t = dp(j, cnt - 1, x + k);
            if (t > mx) {
                mx = t;
                nxt[i][cnt][ans] = j;
                nxta[i][cnt][ans] = x + k;
            }
            t = dp(j, cnt - 1, x * k);
            if (t > mx) {
                mx = t;
                nxt[i][cnt][ans] = j;
                nxta[i][cnt][ans] = x * k;
            }
        }
    }
    if (mx != -2) mx += x;
    return mem[i][cnt][ans] = mx;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    memset(mem, -1, sizeof(mem));
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) cin >> a[i] >> b[i] >> c[i];
    ll mx(-2), mxi, mxa;
    for (int i = 0; i < m; ++i) {
        for (ll f = a[i]; f <= b[i]; ++f) {
            ll t = dp(i, n, f);
            if (t > mx) { mx = t; mxi = i; mxa = f; }
        }
    }
    if (mx == -2) { cout << "NO";  return 0; }
    cout << "YES" << '\n';
    for (int i = n; i; --i) {
        cout << mxi + 1 << ' ' << mxa << '\n';
        ll ti = nxt[mxi][i][mxa - a[mxi]],
        ta = nxta[mxi][i][mxa - a[mxi]];
        mxi = ti;
        mxa = ta;
    }
    return 0;
}