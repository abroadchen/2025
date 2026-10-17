//
// Created by Psy.C on 2026/10/17.
//
/**
读入元素个数 n。
for... cin >> a[i];：读入 n 个数到 a[1..n]。
int f = 0;：标志位，0=还没找到，1=找到答案。
外层 for (int i = 1; i <= n; ++i)：对每个起点 i 试探。
int cnt = 1, id = i, x = i, y;：
cnt：跳转步数计数，初始 1（因为要看从 i 出发的第 1 步）。
id = i：记下起点（作为"环目标"）。
x = i：当前所处位置。
y：临时变量。
while (cnt <= 3 && x <= n)：只要步数 ≤3 且位置合法（没越界），继续走。
y = a[x]; x = y; cnt++;：跳转——把当前位置 x 赋值为 a[x]（即 x 指向 a[x]），步数 +1。也就是说沿着 i → a[i] → a[a[i]] → ... 这条链往下跳。
循环结束后（走满 3 步，或越界）：
if (x == id)：若跳了 3 步后回到了起点 i（形成了长度为 3 的环），则：
f = 1; cout << "YES\n"; break;：置标志、输出 YES、跳出外层循环。
若外层循环跑完 f 仍为 0，输出 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e6+10;

int n, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int f = 0;
    for (int i = 1; i <= n; ++i) {
        int cnt = 1, id = i, x = i, y;
        while (cnt <= 3 && x <= n) {
            y = a[x]; x = y; cnt++;
        }
        if (x == id) {
            f = 1;
            cout << "YES\n";
            break;
        }
    }
    if (f == 0) cout << "NO\n";
    return 0;
}