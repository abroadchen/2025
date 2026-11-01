//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
mid：n²/2（向下取整），表示第一种颜色（偶格）占了一半。
若 n 为奇数，mid++ 让 mid 变成 (n²+1)/2——因为奇数阶棋盘偶格比奇格多 1（中心格算偶格）。
编号：偶数格（(x+y)%2==0）占 1..mid，奇数格占 mid+1..n²
n 为偶时：

mid = n²/2（正好一半一半）。
偶格 (x+y)%2==0：编号 = n/2*(x-1) + 该行内的偏移。
奇格：在偶格基础上 + mid 偏移。
公式来源是对每一行，该行偶格数和奇格数等价于"每行有 n/2 个偶格 + n/2 个奇格"的蛇形排列，逐行累计
奇数阶时，偶格比奇格多一格（中心格），mid++ 处理。

每行的偶格/奇格分布不再恒定（奇数行/偶数行的偶格数不同），所以公式里用 (n/2+1) 和 n/2 分别乘以相应行数，再按 x 的奇偶累加该行之前的总格数，再算 y 的列偏移
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<typename T,typename... Args>
void read(T& t,Args&... args) {
    read(t); read(args...);
}


int n, q, x, y;
signed main() {
    fast;
    read(n, q);
    int mid = n*n/2, ans;
    if (n%2 != 0) {
        mid++;
        while (q--) {
            ans = 0; read(x,y);
            if ((x+y)%2 == 0) {
                if (x%2 == 0) ans = (n/2+1)*(x/2)+n/2*(x/2-1);
                else ans = (n/2+1)*(x/2)+n/2*(x/2);
                if (y%2 == 0) ans += y/2; else ans += y/2+1;
            } else {
                if (x%2 == 0) ans = (n/2+1)*(x/2)+n/2*(x/2-1);
                else ans = (n/2+1)*(x/2)+n/2*(x/2);
                ans += mid;
                if (y%2 == 0) ans += y/2; else ans += y/2;
            }
            cout << ans << '\n';
        }
    } else {
        while (q--) {
            ans = 0; read(x,y);
            if ((x+y)%2 == 0) {
                ans = n/2*(x-1);
                if (x%2 == 0) ans += y/2; else ans += y/2+1;
            } else {
                ans = mid; ans += n/2*(x-1);
                if (x%2 == 0) ans += y/2+1; else ans += y/2;
            }
            cout << ans << '\n';
        }
    }
    return 0;
}