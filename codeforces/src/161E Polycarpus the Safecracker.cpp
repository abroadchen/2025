//
// Created by Psy.C on 2025/11/27.
//
/*
 *dp[len][prefix]：存储具有len位数且前缀为prefix的质数
*a[][]：存储当前数字矩阵
l：输入数字的长度
 *
*cur表示当前处理到第几位
计算当前行的前缀数字x
 *如果处理到最后一位，返回以x为前缀的1位质数个数
*遍历所有可能的质数t（具有l-cur位数且前缀为x）
将t的各位数字填入矩阵的对称位置
递归处理下一位，累加结果
 *
*埃拉托斯特尼筛法生成质数表
标记所有合数
*预处理：将每个质数按不同长度的前缀分类存储
i = 1234
t = 1234 / 10 = 123
循环过程：
j=1: dp[1][123].push_back(1234) // 4位数，前1位是123
t = 123 / 10 = 12
j=2: dp[2][12].push_back(1234) // 4位数，前2位是12
t = 12 / 10 = 1
j=3: dp[3][1].push_back(1234) // 4位数，前3位是1
t = 1 / 10 = 0
j=4: dp[4][0].push_back(1234) // 4位数，前4位是0（实际是1234）
 *
*读取n个测试用例
将输入字符串填入矩阵的第一行和第一列
调用DFS计算方案数并输出
 *
*预处理：O(N log log N)
每次查询：取决于符合条件的质数个数
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=2;i<n;++i)
#define sz(x) (static_cast<int>((x).size()))
using namespace std;

constexpr int N = 1e5, M = 5;
constexpr double inf = 100000.5;
bool vis[N+10];//标记合数
vector<int> dp[M][N+10];
int a[M+1][M+1], l;

int dfs(const int cur) {
    int x = 0, i = 0, sum = 0;
    for (i = 0; i < cur; ++i) x = x * 10 + a[cur][i];
    if (i == l - 1) return sz(dp[1][x]);
    for (i = 0; i < sz(dp[l - cur][x]); ++i) {
        int t = dp[l - cur][x][i];
        for (int j = l - 1; j >= cur; --j) {
            a[j][cur] = a[cur][j] = t % 10;
            t /= 10;
        }
        sum += dfs(cur + 1);
    }
    return sum;
}

int main() {
    fast;
    const int m = static_cast<int>(sqrt(inf));
    rep(i,m+1) if (!vis[i]) {
        for (int j = i * i; j <= N; j += i) vis[j] = true;
    }
    rep(i,N) if (!vis[i]) {
        int t = i;
        t /= 10;
        for (int j = 1; j <= M - 1; ++j) {
            dp[j][t].push_back(i);
            t /= 10;
        }
    }
    int n; cin >> n; char str[M+2];
    for (int j = 1; j <= n; ++j) {
        cin >> str; l = static_cast<int>(strlen(str));
        for (int i = 0; str[i] != '\0'; ++i) {
            a[0][i] = a[i][0] = str[i] - '0';
        }
        cout << dfs(1) << '\n';
    }
    return 0;
}