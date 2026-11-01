//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
用 mp 统计每个值出现次数。
只要某值出现满 4 次，ans 记录它。
若存在这样的值，直接输出四个它（正方形最优），跳过本轮
sort + unique 去重，n 更新为去重后的元素个数。
遍历去重后的每个值，只要它在原数组中出现 ≥2 次（mp>1），就放进 b[]。b[] 就是所有"能当矩形一边"的候选值（需要两条）。
因为 b[] 从去重后的有序数组产生，天然升序
枚举 b[] 中相邻的两项 (b[i-1], b[i])。
计算 w/h + h/w（这里 w 取小的、h 取大的）。
更新最小，记录这一对
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
#define inf (1e11-1)
#define db double
using namespace std;

constexpr int N = 1e6+10;

int T, n, ans, a[N], b[N], cnt, a1, a2;
map<int, int> mp;
db t;
int main() {
    fast;
    cin >> T;
    while(T--) {
        cin >> n; ans = 0; mp.clear();
        rep(i,n) {
            cin >> a[i]; mp[a[i]]++;
            if (mp[a[i]] == 4) ans = a[i];
        }
        if (ans != 0) {
            cout << ans << ' ' << ans << ' ' << ans << ' ' << ans << '\n';
            continue;
        }
        sort(a+1, a+1+n);
        n = unique(a+1, a+1+n) - a - 1;
        cnt = 0;
        rep(i,n) if (mp[a[i]] > 1) b[++cnt] = a[i];
        t = inf; a1 = 0, a2 = 0;
        for (int i = 2; i <= cnt; i++) {
            if ((db)b[i]/b[i-1]+(db)b[i-1]/b[i] < t) {
                t = (db)b[i]/b[i-1] + (db)b[i-1]/b[i];
                a1 = b[i-1], a2 = b[i];
            }
        }
        cout << a1 << ' ' << a1 << ' ' << a2 << ' ' << a2 << '\n';
    }
    return 0;
}