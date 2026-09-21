//
// Created by Psy.C on 2026/9/21.
//
/**
f[i][0] = 第 i 行最左 '1' 的 1-based 位置
f[i][1] = 第 i 行最右 '1' 到右端的距离
若整行全为 '0'（ok==0），则该行无 '1'，置 f[.][0]=f[.][1]=1，并标记 no[i]=1（该行没有障碍/可以忽略）
最末行若无 '1'，左边位置设为 1

第 1 行（底层）：
停在右侧：从起始到右侧…… len-1。
停在左侧：f[1][0]*2 - 2
从第 i-1 行到第 i 行，机器人要走一整段列移动 + 上升。
dp[i][0]（最终停在 i 行左侧）：
从 i-1 行左侧上来：dp[i-1][0] + f[i][0]*2 - 1（左侧上来，走到 i 行左侧，经过 f[i][0] 再回来，花 2*f-1 步）。
或从 i-1 行右侧上来：dp[i-1][1] + len（从右侧走到 i 行左侧需 len 步）。
dp[i][1] 同理对称（用 f[i][1] 和"从左侧过来 +len"）。
这是一个双端点 DP：上一行停在哪端，决定这一行从哪端走，行走总长是横穿本行 + 纵向上升。

找到最上方有障碍的行 k（跳过上面全空的行）。
答案：从 k-1 行到 k 行后，停在 k 行左/右侧的最小值 = min(dp[k-1][0] + f[k][0], dp[k-1][1] + f[k][1])。
若 k==1（只有一行就完成了），单独处理 ans = f[1][0] - 1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 20, inf = 2e5+5;

int n, m, len, f[N][2], no[N], dp[N][2];
int main() {
    fast;
    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++) {
            string s; cin >> s; len = s.length();
            int j;
            int ok = 0;
            for (j = 1; j < len - 1; j++) if (s[j] == '1') { f[n + 1 - i][1] = len - j; break; }
            for (j = len - 1; j > 0; j--)if (s[j] == '1') { f[n + 1 - i][0] = j + 1; break; }
            for (j = 0; j < len; j++) { if (s[j] == '1') ok = 1; }
            if (ok == 0)f[n + 1 - i][0] = 1, f[n + 1 - i][1] = 1, no[n + 1 - i] = 1;
        }
        if (no[1]) f[1][0] = 1;
        dp[1][1] = len - 1; dp[1][0] = f[1][0] * 2 - 2;
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j <= 1; j++)dp[i][j] = inf;
            dp[i][0] = min(max(0, dp[i - 1][0] + f[i][0] * 2 - 1), dp[i - 1][1] + len);
            dp[i][1] = min(max(0, dp[i - 1][1] + f[i][1] * 2 - 1), dp[i - 1][0] + len);
        }

        int k = n;
        while (no[k])k--;

        int ans = min(dp[k - 1][0] + f[k][0], dp[k - 1][1] + f[k][1]);
        if (k == 1) {
            f[1][0]--; ans = f[1][0];
        }
        cout << ans << endl;
    }
    return 0;
}