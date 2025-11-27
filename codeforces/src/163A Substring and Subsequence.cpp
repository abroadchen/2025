//
// Created by Psy.C on 2025/11/27.
//
/*
*双重循环遍历两个字符串
如果字符相等：
f[i][j] = 1 + f[i-1][j-1]（如果i,j都大于0）
表示以s[i]和t[j]结尾的新匹配数加上之前的匹配数
结果对mod取模
*将当前状态传递给下一列
这是状态转移的一部分
*累加第i行最后一列的值到总计数中
结果对mod取模
 *
 *时间复杂度：O(n×m) 空间复杂度：O(n×m)
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;
constexpr ll mod = 1e9+7;

int main() {
    fast;
    string s, t; cin>>s>>t;
    const int n = static_cast<int>(s.size()),
    m = static_cast<int>(t.size());
    vector<vector<ll>> f(n, vector<ll>(m, 0));
    ll cnt = 0;
    for(int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i] == t[j]) {
                f[i][j] += 1 + ((i > 0 && j > 0) ? f[i-1][j-1] : 0);
                f[i][j] %= mod;
            }
            if (j + 1 < m) f[i][j+1] = f[i][j];
        }
        cnt += f[i][m-1];
        cnt %= mod;
    }
    cout << cnt << '\n';
    return 0;
}