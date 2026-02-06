//
// Created by Psy.C on 2026/2/6.
//
/**
 *
*tot：记录不同周期长度的数量
ans[N]：存储所有可能的周期长度
dp[N]：动态规划数组，记录每个周期出现的次数
 *从字符串末尾开始，沿着next数组向上遍历，收集所有可能的周期长度
 *
*从后向前遍历，计算每个周期实际出现的次数
dp[i]++：每个周期本身至少出现一次
dp[nxt[i]] += dp[i]：将当前周期的贡献传递给其更短的周期
//较长的周期必然包含较短的周期作为子结构
 *
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

int nxt[N];//最长相等前后缀长度
char s[N];
void get(const int m) {
    int i = 2, j = nxt[1] = 0;
    while (i <= m) {
        while (j && s[i] != s[j+1]) j = nxt[j];
        if (s[i] == s[j+1]) j++;
        nxt[i++] = j;
    }
}


int main() {
    fast;
    string str; cin >> str; strcpy(s + 1, str.data());
    const int n = static_cast<int>(strlen(s + 1)); get(n);
    int tot = 0, ans[N]{}, dp[N]{};
    for (int i = n; i > 0; i = nxt[i]) ans[++tot] = i;
    for (int i = n; i > 0; --i) {
        dp[i]++;
        dp[nxt[i]] += dp[i];//长度为 nxt[i] 的周期在整个字符串中出现的次数
    }
    cout << tot << '\n';
    for (int i = tot; i > 0; --i)
        cout << ans[i] << ' ' << dp[ans[i]] << '\n';
    return 0;
}