//
// Created by Psy.C on 2026/9/8.
//
/**
pos[t][j]：第 t 类字符的第 j 个在原串中的位置（t=0:_，1:V，2:K）。
cnt[t]：第 t 类字符的个数。
sum[t][i][j]：前缀和，表示"第 t 类字符中，前 j 个里，位置在原串第 i 位之后（> i）的个数"。即第 t 类第 j 个字符若放到位置 i 之后会产生多少个跨类逆序对。
init() 对三类各建一张二维前缀和表，用于后面 O(1) 查询"把某类某字符放在某位置时需要跨过多少个不同类的字符"。
（pos[t][j] > i 为 true 得 1：表示第 t 类第 j 个字符在原串中位于位置 i 之后，即当我们要把它排到位置 i 右侧时，它与已在 i 之前的其他类字符会构成逆序/交换代价。）
dp[_][v][k][type]：已经取走了前 _ 个字符 _、前 v 个字符 V、前 k 个字符 K，并且最后放置的一类字符是 type 时，所需的最小交换次数

把第 _+1 个字符 _（在原串位置 nxt）放到末尾：新代价 = 原代价 + 「与已放置的前 v 个 V」形成的逆序对数 + 「与前 k 个 K」形成的逆序对数，即 sum[1][nxt][v] + sum[2][nxt][k]。
更新 dp[_+1][v][k][0]（末位类型为 _）
把第 v+1 个字符 V（位置 nxt）放到末尾：代价累加与已放 _(前 _ 个)和 K(前 k 个)的逆序对：sum[0][nxt][_] + sum[2][nxt][k]。
更新 dp[_][v+1][k][1]
把第 k+1 个字符 K（位置 nxt）放到末尾：代价累加 sum[0][nxt][_] + sum[1][nxt][v]
最后一个分支要求在放 K 之前，最后一个放置的字符类型 type != 1（即不是 V），否则不放

读入 n 和字符串。把既不是 K 也不是 V 的字符统一改写为 _（三类字符：_、V、K）。
id(c) 映射字符 → 类别编号；pos[add][++cnt[add]] = i 记录每类字符各自在原串中的位置。
初始化 dp 全为 inf，起点 dp[0][0][0][0]=0，调 init() 建前缀和、func() 做 DP。
最终答案：dp[cnt[0]][cnt[1]][cnt[2]][type] 在三种末位类型中取最小——即把所有字符全部放置完成所需的最小相邻交换次数
 */
#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;++i)
using namespace std;
constexpr int N = 80, inf = 0x3f3f3f3f;
int n, cnt[3], sum[3][N][N], pos[3][N];
void init() {
    rep(i, 1, n) {
        rep(j, 1, cnt[0]) {
            sum[0][i][j] = sum[0][i][j - 1] + (pos[0][j] > i);
        }
    }
    rep(i, 1, n) {
        rep(j, 1, cnt[1]) {
            sum[1][i][j] = sum[1][i][j - 1] + (pos[1][j] > i);
        }
    }
    rep(i, 1, n) {
        rep(j, 1, cnt[2]) {
            sum[2][i][j] = sum[2][i][j - 1] + (pos[2][j] > i);
        }
    }
}

int dp[N][N][N][3];
void func() {
    rep(_, 0, cnt[0]) {
        rep(v, 0, cnt[1]) {
            rep(k, 0, cnt[2]) {
                rep(type, 0, 2) {
                    if(dp[_][v][k][type] >= inf) continue;
                    if(_ < cnt[0]) {
                        int nxt = pos[0][_ + 1];
                        dp[_ + 1][v][k][0] = min(dp[_ + 1][v][k][0], dp[_][v][k][type] + sum[1][nxt][v] + sum[2][nxt][k]);
                    }
                    if(v < cnt[1]) {
                        int nxt = pos[1][v + 1];
                        dp[_][v + 1][k][1] = min(dp[_][v + 1][k][1], dp[_][v][k][type] + sum[0][nxt][_] + sum[2][nxt][k]);
                    }
                    if(k < cnt[2] && type != 1) {
                        int nxt = pos[2][k + 1];
                        dp[_][v][k + 1][2] = min(dp[_][v][k + 1][2], dp[_][v][k][type] + sum[0][nxt][_] + sum[1][nxt][v]);
                    }
                }
            }
        }
    }
}

int id(char c) {
    if (c == '_') return 0;
    if (c == 'V') return 1;
    if (c == 'K') return 2;
}

char s[N];
int main() {
    cin >> n; scanf("%s", s+1);
    rep(i, 1, n) if(s[i] != 'K' && s[i] != 'V') s[i] = '_';
    rep(i, 1, n) {
        int add = id(s[i]);
        pos[add][++cnt[add]] = i;
    }
    memset(dp, 0x3f, sizeof dp); dp[0][0][0][0] = 0; init(); func();
    int ans = INT_MAX;
    for (int type = 0; type < 3; ++type)
        ans = min(ans, dp[cnt[0]][cnt[1]][cnt[2]][type]);
    cout << ans;
    return 0;
}