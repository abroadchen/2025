//
// Created by Psy.C on 2026/10/21.
//
/**
j,k ∈ [0, n-1]，m1/m2 索引 i∈[0,3] 对应 4 幅图。
(j+k)%2==0（奇偶性与 (0,0) 相同）：
若该格是 1（与标准色不一致 → 需要翻转）计入 m2[i]；
若该格是 0（与标准色一致）计入 m1[i]。
(j+k)%2==1（奇偶性与 (0,0) 相反）：
若该格是 1（与标准色一致）计入 m1[i]；
若该格是 0（与标准色不一致 → 需翻转）计入 m2[i]。
可确证：m2[i] = 第 i 幅图"按 (0,0)=0 的标准棋盘"需要翻转（与标准不一致）的格子数；m1[i] = 第 i 幅图与标准一致的格子数，且 m1[i]+m2[i]=n²。
枚举从 4 幅中选 2 幅 (i,j) 作为"标准棋盘 A"的原型，另 2 幅 (k) 作为"标准棋盘 B"。
sum = Σ_{其余2幅} m2[k] + (m1[i]+m1[j])：
选中的 i,j 两幅用 m1（即"需保持与标准一致"的那部分）——语义为这 2 幅要翻转成与 (0,0)=0 的标准不同的另一种标准？这里存在方向性。
未选中的 2 幅用 m2（翻转成标准 A）。
可确证：枚举所有 C(4,2)=6 种选法，sum = (m1[i]+m1[j]) + Σ_{其余}m2[k]，取最小值
输出最小翻转次数 ans

m1 与 m2 的"标准棋盘"方向：从代码看，m2 对应"以 (0,0)=0 为标准的棋盘"需要翻转的格子，m1 对应一致格。而最终 sum 对选中的 2 幅用 m1、未选的 2 幅用 m2，意味着选中的 2 幅朝 (0,0)=1 的反向标准翻、未选 2 幅朝 (0,0)=0 的标准翻——即 4 幅分成两组，各自朝向相反的标准棋盘，求最小总翻转数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;

constexpr int N = 105;

int n, m1[4], m2[4];
char a[N][N];
int main() {
    fast;
    cin >> n;
    rep(i,4) rep(j,n) {
        cin >> a[j];
        rep(k,n) {
            if ((j+k)%2 == 0) {
                if (a[j][k] - '0' == 1) m2[i]++;
                else if (a[j][k] - '0' == 0) m1[i]++;
            } else if ((j+k)%2 == 1) {
                if (a[j][k] - '0' == 1) m1[i]++;
                else if (a[j][k] - '0' == 0) m2[i]++;
            }
        }
    }
    int ans = n*n*4;
    rep(i,3) for (int j = i+1; j < 4; j++) {
        int sum = 0;
        rep(k,4) if (k != i && k != j) sum += m2[k];
        sum += m1[i] + m1[j];
        ans = min(ans, sum);
    }
    cout << ans << '\n';
    return 0;
}