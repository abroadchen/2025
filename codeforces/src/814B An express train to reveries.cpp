//
// Created by Psy.C on 2026/9/21.
//
/**
在相同位置，c[i] 只能等于 a[i]（因为 a[i]==b[i]，二者同值），这些位置固定。
在不同位置（最多 2 个），需要为它们分配值，使 1..n 不漏不重（排列）。
用 c 数组统计已出现过的数
对两个不同位置，优先各自用 a[i]；冲突时改用 b[i]；若两个选项都被占用，则回退前面那个不同位置已做的选择（把它从 a 改成 b 或从 b 改成 a），腾出空间，再填充当前位置
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, a[N], b[N], cnt, ans[N], c[N];
int main() {
    fast;
    n = rd();
    for (int i = 1; i <= n; ++i) a[i] = rd();
    for (int i = 1; i <= n; ++i) {
        b[i] = rd();
        cnt += a[i] != b[i];
    }
    if (cnt == 1) {//只有 1 处不同
        for (int i = 1; i <= n; ++i)//固定位置照抄
            if (a[i] == b[i]) ans[i] = a[i], c[a[i]]++;
        for (int i = 1; i <= n; ++i)//找到那1个不同位置，填入还没出现过的那个数
            if (a[i] != b[i]) {
                for (int j = 1; j <= n; ++j)
                    if (!c[j]) { ans[i] = j; break; }
            }
    } else if (cnt == 2) {
        for (int i = 1; i <= n; ++i)
            if (a[i] == b[i]) ans[i] = a[i], c[a[i]]++;
        for (int i = 1; i <= n; ++i) {
            if (a[i] != b[i]) {
                if (!c[a[i]]) { ans[i] = a[i]; c[a[i]]++; }//a[i] 还没用，用 a[i]
                else {
                    if (!c[b[i]]) { ans[i] = b[i]; c[b[i]]++; }//a[i] 用了，用 b[i]
                    else {//两个都用过了？回退前面的某个决策
                        for (int j = i-1; j >= 1; --j) {
                            if (a[j] != b[j]) {
                                if (ans[j] == a[j]) { c[a[j]]--; ans[j] = b[j]; }//之前选a，改选b
                                else ans[j] = a[j], c[b[j]]--;//之前选b，改选a
                                break;
                            }
                        }
                        //再尝试填 i
                        if (!c[b[i]]) { ans[i] = b[i]; c[b[i]]++; }
                        else if (!c[a[i]]) { ans[i] = a[i]; c[a[i]]++; }
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}