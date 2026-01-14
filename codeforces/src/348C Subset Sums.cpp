//
// Created by Psy.C on 2026/1/14.
//
/**
 * n个元素，m个集合，q个查询
 * b[M+5]：存储大块的编号数组
 *cnt = 0：大块计数器
 *sa[N+5][M+5]：预计算的小块与大块的交叉关系
 *a[N+5]：存储n个元素的值
 *ans[N+5]：每个集合的当前总和
 *ad[N+5]：大块的懒惰标记（增量）
 *s[N+5]：每个集合包含的元素
 *vis[M+5]：大块的成员位图
 */
#include <iostream>
#include <vector>
#include <bitset>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100000
#define M 316
using namespace std;


int main() {
    fast;
    int n, m, q, b[M+5], cnt = 0, sa[N+5][M+5]; cin >> n >> m >> q;
    ll a[N+5], ans[N+5], ad[N+5];
    vector<int> s[N+5];
    bitset<N+5> vis[M+5];
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, len; i <= m; ++i) {
        cin >> len;//第i个集合的大小
        for (int j = 1, x; j <= len; ++j) {//读入集合中的元素
            cin >> x; s[i].push_back(x);//将元素x加入集合i
            ans[i] += a[x];//累加集合i的初始总和
        }
        if (len >= M) {//集合大小大于等于分块大小M
            b[++cnt] = i;//将集合i标记为大块
            for (const int j : s[i]) vis[cnt][j] = true;//在位图中标记大块的成员
        }
    }
    for (int i = 1; i <= m; ++i) for (const int j : s[i]) {//遍历集合i中的每个元素
        for (int k = 1; k <= cnt; ++k) if (vis[k][j]) {//遍历所有大块 元素j属于大块k
            sa[i][k]++;//增加集合i与大块k的交叉计数
        }
    }
    while (q--) {
        char opt; cin >> opt;
        if (opt == '?') {
            int x; cin >> x;//读取查询的集合编号
            if (s[x].size() < M) {//如果集合x是小块
                ll res = 0;
                for (const int j : s[x]) res += a[j];//暴力累加元素值
                for (int j = 1; j <= cnt; ++j) res += 1ll * ad[b[j]] * sa[x][j];//加上大块增量的影响
                cout << res << '\n';//输出小块的总和
            } else cout << ans[x] << '\n';//如果是大块，直接输出预存结果
        } else {//更新操作
            int x, y; cin >> x >> y;//读取集合编号和增量
            if (s[x].size() < M) {
                for (const int j : s[x]) a[j] += y;//直接更新元素值
                for (int j = 1; j <= cnt; ++j) ans[b[j]] += 1ll * y * sa[x][j];//更新受影响的大块
            } else {
                for (int j = 1; j <= cnt; ++j) ans[b[j]] += 1ll * y * sa[x][j];
                ad[x] += y;//更新大块的懒惰标记
            }
        }
    }
    return 0;
}