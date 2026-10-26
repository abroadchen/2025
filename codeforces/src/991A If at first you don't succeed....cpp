//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
单个集合不能超过全集 m（a>m / b>m / c>m 均表示某集超出全集 → 无解）。
交集 c 不可能大于其中任一集合（c>a、c>b → 交集大于单集，无解）。
任一成立 → 输出 -1
a + b - c：根据容斥原理，这是 两个集合 a、b 的元素总数（去掉交集 c 后）‍，即 |A ∪ B| = a + b - c（两集合并集大小）。
若这个值 >= m，说明两个集合的去重后总数已经达到或超过总容量 m，那再加进第三个集合 c 就会溢出 → 无法满足 → 输出 -1
当两个大条件都不成立时，输出 m - (a+b-c)。
这正是 总容量 m 减去两集合并集大小，即"剩余可用空间"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int a, b, c, m;
int main() {
    fast;
    cin >> a >> b >> c >> m;
    if (a > m || b > m || c > m || c > a || c > b) cout << "-1\n";
    else if (a + b - c >= m) cout << "-1\n";
    else cout << m-(a+b-c) << '\n';
    return 0;
}