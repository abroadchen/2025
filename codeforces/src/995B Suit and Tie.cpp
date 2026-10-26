//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
读入原始 n，再 n *= 2，即实际序列长度为 2n。
用 a[1..2n] 存这 2n 个数
只有当 a[i] 非零（还没被标记配对掉）时才处理它
从 i+1 开始向后扫描：

若 a[j] 不等于 a[i] 且非零 → 这是一个"被夹在 a[i] 和它的配对之间"的元素，ans++。
若 a[j] 等于 a[i] → 找到了 a[i] 的配对，break 退出循环。
也就是：统计从 a[i] 到它的配对之间（不含两端）有多少其他数字
把找到的那个配对位置 a[j] 置为 0，表示这一对已经处理完（之后外层 if(a[i]) 会因为 a[i] 仍是原值，所以不会跳过 a[i] 本身，但 a[j] 被标 0 后不会再被当作"夹中间的数"记一次，也不会再被当作起点处理）
输出累计的 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; i++)
using namespace std;

int n;
int main() {
    fast;
    cin >> n; n *= 2;
    int a[n+1], i;
    rep(i,n) cin >> a[i];
    int ans = 0;
    rep(i,n) if (a[i]) {
        int j;
        for (j = i+1; ; j++) {
            if (a[j] != a[i] && a[j] != 0) ans++;
            else if (a[j] == a[i]) break;
        }
        a[j] = 0;
    }
    cout << ans << '\n';
    return 0;
}