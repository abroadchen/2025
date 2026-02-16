//
// Created by Psy.C on 2026/2/16.
//
/**
pre[i]: 存储前缀哈希值
pw[i]: 存储2的幂次（用于哈希计算）
pre[r]: s[1..r]的哈希
pre[l-1]*pw[r-l+1]: s[1..l-1]向左移位后变成s[1..l-1]在[l,r]位置的哈希

n: 字符串长度
dp[i][j]: 前i个字符，最后j个字符的某种状态值
cnt[i][j]: 前i个字符，最后j个字符的方案数
dp[0][0] = 0: 空字符串状态值为0
cnt[0][0] = 1: 空字符串方案数为1
pw[0] = 1: 2^0 = 1

从后往前计算LCP数组
如果s[i] == s[j]，则lcp[i][j] = lcp[i+1][j+1] + 1
否则lcp[i][j] = 0

时间复杂度: O(n²)
空间复杂度: O(n²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define per(i,n) for (int i=n; i>=1; --i)
using namespace std;

constexpr int N = 5010, mod = 1e9+7;

int pre[N], pw[N];
int get(const int l, const int r) {//获取字符串区间[l,r]的哈希值
    return ((pre[r] - 1ll*pre[l-1]*pw[r-l+1])%mod+mod)%mod;
}

string s;
int lcp[N][N];// s[i...]和s[j...]的最长公共前缀长度
int cmp(const int l1, const int r1, const int l2, const int r2) {
    if (r1 - l1 + 1 != r2 - l2 + 1)//长度不同，返回长度比较结果
        return r1 - l1 + 1 > r2 - l2 + 1 ? 1 : -1;
    return lcp[l1][l2] >= r1-l1+1 ? 0 ://公共前缀长度≥子串长度，则两串相等，返回0
        s[l1+lcp[l1][l2]] > s[l2+lcp[l1][l2]] ? 1 : -1;//比较第一个不同字符
}

int n, dp[N][N], cnt[N][N];
int main() {
    fast;
    cin >> s; n = s.size(); s = "&"+s;//添加特殊字符，使索引从1开始
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0, cnt[0][0] = 1, pw[0] = 1;
    rep(i,n) cnt[0][i] = 1, dp[0][i] = 0;
    rep(i,n) pw[i] = pw[i-1]*2%mod, pre[i] = (pre[i-1]*2+s[i]-'0')%mod;
    per(i,n) per(j,n) lcp[i][j] = s[i] == s[j] ? lcp[i+1][j+1] + 1 : 0;
    int ans = -1;
    rep(i,n) {
        rep(j,i) if (s[i-j+1] == '1') {//子串s[i-j+1..i]以'1'开头
            int k = j;//优化边界
            //前半部分>后半部分
            if (j+j <= i && cmp(i-j-j+1, i-j, i-j+1, i) == 1) k--;
            dp[i][j] = dp[i-j][k]+1, cnt[i][j] = cnt[i-j][k];
        }
        if (i == n) {//处理到最后一个字符时
            int flag = 0;
            rep(j,min(13, n)) if (cnt[i][j]) flag = 1;//前13个位置是否有方案
            if (flag) {//计算最小值
                ans = INT_MAX;
                rep(j,min(13, n))
                    ans = min(ans, dp[n][j] + get(n-j+1, n));
            } else {
                rep(j,n) if (cnt[i][j]) {//取第一个非零方案
                    ans = (dp[n][j] + get(n-j+1, n))%mod;
                    break;
                }
            }
        }
        rep(j,n) {
            dp[i][j] = min(dp[i][j], dp[i][j-1]);//前缀最小值
            cnt[i][j] = (cnt[i][j] + cnt[i][j-1])%mod;//方案数的前缀和
        }
    }
    cout << cnt[n][n] << '\n' << ans;//方案总数和最优答案
    return 0;
}