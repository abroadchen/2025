//
// Created by Psy.C on 2026/9/22.
//
/**
从下标 3 开始向后扫（跳过 a[0]、a[1]、a[2] 本身），只要 a[i] 仍等于第三小值 a[2]，cnt 就加 1；一旦不等就 break（数组已排序，后面只会更大）。
结束时 cnt = "除 a[0]、a[1]、a[2] 外，还有多少个元素也等于 a[2]"
情形①：a[1] < a[2]（最小值之间严格分开，a[2] 是其"新一档"的最小值）
此时等于 a[2] 的元素总共是 cnt（后面的）+ 1（a[2] 本身）= cnt+1 个，直接输出这个数量，并 continue 进入下一组数据。
对应题意大概是"选出 1 个即等于该档值的方案数"。
情形②：a[1] == a[2] && a[0] < a[1]（a[0] 单独一档，a[1]==a[2] 为相同的一档）
先 cnt += 2：把 a[1]、a[2] 算进来，"等于 a[2]" 的元素总数 m = cnt。
用 C(m,2) = m*(m-1)/2 计算从这 m 个相同元素中任意选 2 个的方案数。用 1ll* 防止乘法溢出 int。
说明该情形对应"要选出 2 个元素"的计数。
情形③：a[1] == a[0] && a[1] == a[2]（最小的三个全相等）
cnt += 3：把 a[0]、a[1]、a[2] 也计入，"等于该最小值"的总数 m = cnt。
用 C(m,3) = m*(m-1)*(m-2)/6 计算从这 m 个中任意选 3 个的方案数。
说明该情形对应"要选出 3 个元素"的计数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+1e2;
int a[N];
int main() {
    fast;
    int n;
    while (cin >> n) {
        for (int i = 0; i <= n-1; ++i) cin >> a[i];
        sort(a, a+n);
        int cnt = 0;
        for (int i = 3; i <= n-1; ++i) {
            if (a[i] == a[2]) ++cnt;
            else break;
        }
        if (a[1] < a[2]) { cout << cnt+1 << '\n'; continue; }
        if (a[1] == a[2] && a[0] < a[1]) {
            cnt += 2;
            ll res = 1ll*cnt*(cnt-1)/2;
            cout << res << '\n';
        }
        if (a[1] == a[0] && a[1] == a[2]) {
            cnt += 3;
            ll res = 1ll*cnt*(cnt-1)*(cnt-2)/6;
            cout << res << '\n';
        }
    }
    return 0;
}