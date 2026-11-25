//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
a,b 分别记录上一段的左右端点；ans 记录累计答案
读入新的一段 [x,y]。
分两种情况计算"本段新增覆盖的整数点个数"：
情况 1：a == b（上一段是单点）
上一段是唯一点 a=b。新增的是本段 [x,y] 里从 a 到本段中某个位置的增量。
实际效果：本段若延伸到 a 之后，新增 min(x,y) - a（即 min(x-a, y-a)）个点；用 max(0,·) 保证不倒退
情况 2：上一段是正常区间 [a,b]（a<b）
本段 [x,y] 与上一段 [a,b] 的重叠之外的新增部分：

min(x,y)：本段的右端点；
max(a,b)：上一段的右端点 b；
min(x,y) − max(a,b) + 1 = 本段右端超出上一段右端的点数（整数）。
max(0,·) 保证本段完全被上一段覆盖时新增为 0。

更新 a = x, b = y，让下一轮用到本段作为"上一段"。

最后输出 ans + 1：总体多 1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, a, b, ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        if (a == b) ans += max(0,min(x-a,y-b));
        else ans += max(0,min(x,y)-max(a,b)+1);
        a = x, b = y;
    }
    cout << ans+1;
    return 0;
}