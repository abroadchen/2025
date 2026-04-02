//
// Created by Psy.C on 2026/4/1.
//
/**
a[N]: 映射数组
b[N]: 输入值数组
d[N]: 计数数组
e[N]: e[i] = b[i]/d[i]
f[N]: 累积值数组
g[N]: 每个索引对应一个multiset
ans: 全局答案multiset
t[10]: 临时数组，用于存储需要更新的索引

第一部分：更新三级嵌套索引
从multiset g[a[a[a[x]]]] 中删除 f[a[a[x]]] 的值
这是三层嵌套索引：a[a[a[x]]]，代表对最深层嵌套的multiset进行操作
更新 f[a[a[x]]] 的值
减去 e[a[x]]（因为a[x]的关联项发生了变化）
加上 b[a[x]]/(d[a[x]]-1)（由于d[a[x]]减少了1）
将更新后的 f[a[a[x]]] 值重新插入到 g[a[a[a[x]]]] multiset中
第二部分：更新二级嵌套索引
从multiset g[a[a[x]]] 中删除 f[a[x]] 的值
更新 f[a[x]] 的值
f[a[x]] - e[x]: 减去x的贡献
-(e[a[x]]+b[a[x]]%d[a[x]]): 减去原来a[x]的额外贡献
b[a[x]]/(d[a[x]]-1) + b[a[x]]%(d[a[x]]-1): 加上新的a[x]贡献（因为d[a[x]]减少1）
将更新后的 f[a[x]] 值重新插入到 g[a[a[x]]] multiset中
第三部分：更新一级索引
从multiset g[a[x]] 中删除 f[x] 的值
将 f[x] 的值插入到 g[y] multiset中
因为a[x]现在变成了y，所以x的值应该归属到y的multiset中
第四部分：更新y的二级索引
从multiset g[a[a[y]]] 中删除 f[a[y]] 的值
更新 f[a[y]] 的值
f[a[y]] - e[y]: 减去原来的贡献
b[y]/(d[y]+1): 加上新的贡献（因为d[y]增加了1）
将更新后的 f[a[y]] 值重新插入到 g[a[a[y]]] multiset中
第五部分：更新y的值
从multiset g[a[y]] 中删除 f[y] 的值
更新 f[y] 的值
f[y] - (e[y] + b[y]%d[y]): 减去原来的贡献
b[y]/(d[y]+1) + b[y]%(d[y]+1): 加上新的贡献（因为d[y]增加1）
+ e[x]: 加上x的贡献（x现在变成y）
将更新后的 f[y] 值重新插入到 g[a[y]] multiset中

 */
#include <bits/stdc++.h>
#define ll long long
#define rep(i,n) for (i=1; i<=(n); ++i)
using namespace std;

inline ll rd() {
    int f = 0, ch = 0; ll x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

constexpr int N = 1e5+5;
ll a[N], b[N], d[N], e[N], f[N];
multiset<ll> g[N], ans;
int t[10];
int main() {
    int n = rd(), q = rd(), i;
    rep(i,n) b[i] = rd(), d[i] = 2;//读入b数组，初始化d数组为2
    rep(i,n) a[i] = rd(), d[a[i]]++;//读入a数组，增加d[a[i]]的计数
    rep(i,n) e[i] = b[i]/d[i];//计算e数组
    rep(i,n) f[a[i]] += e[i];//累加f[a[i]]
    rep(i,n) f[i] += e[i] + b[i]%d[i];//更新f数组
    rep(i,n) g[a[i]].insert(f[i]);//将f值插入对应的multiset
    rep(i,n) if (g[i].size()) {//如果g[i]不为空，将边界值插入ans multiset
        ans.insert(e[i] + *g[i].begin());
        ans.insert(e[i] + *--g[i].end());
    }
    while (q--) {
        int op = rd();
        if (op == 1) {
            int x = rd(), y = rd();//读入要修改的位置x和目标值y
            if (a[x] == y) continue;//当前值等于目标值，跳过
            //将受影响的7个索引存入t数组
            t[0] = x, t[1] = a[x], t[2] = a[a[x]], t[3] = a[a[a[x]]];
            t[4] = y, t[5] = a[y], t[6] = a[a[y]];
            sort(t, t + 7);
            for (i = 0; i < 7; i++) {
                if (t[i] == t[i+1]) continue;
                int x = t[i];
                if (g[x].size()) {
                    ans.erase(ans.find(e[x] + *g[x].begin()));//移除旧的边界值
                    ans.erase(ans.find(e[x] + *--g[x].end()));
                }
            }
            g[a[a[a[x]]]].erase(g[a[a[a[x]]]].find(f[a[a[x]]]));
            f[a[a[x]]] = f[a[a[x]]] - e[a[x]] + b[a[x]]/(d[a[x]]-1);
            g[a[a[a[x]]]].insert(f[a[a[x]]]);
            g[a[a[x]]].erase(g[a[a[x]]].find(f[a[x]]));
            f[a[x]] = f[a[x]] - e[x] - (e[a[x]]+b[a[x]]%d[a[x]]) +
                b[a[x]]/(d[a[x]]-1) + b[a[x]]%(d[a[x]]-1);
            g[a[a[x]]].insert(f[a[x]]);
            g[a[x]].erase(g[a[x]].find(f[x]));
            g[y].insert(f[x]);
            g[a[a[y]]].erase(g[a[a[y]]].find(f[a[y]]));
            f[a[y]] = f[a[y]] - e[y] + b[y]/(d[y]+1);
            g[a[a[y]]].insert(f[a[y]]);
            g[a[y]].erase(g[a[y]].find(f[y]));
            f[y] = f[y] - (e[y] + b[y]%d[y]) + b[y]/(d[y]+1) + b[y]%(d[y]+1) + e[x];
            g[a[y]].insert(f[y]);
            d[a[x]]--, d[y]++;//更新d数组：减少旧值计数，增加新值计数
            e[a[x]] = b[a[x]]/d[a[x]], e[y] = b[y]/d[y];//更新e数组：重新计算e[a[x]]和e[y]
            for (i = 0; i < 7; ++i) {
                int x = t[i];
                if (t[i] == t[i+1]) continue;
                if (g[x].size()) {
                    ans.insert(e[x] + *g[x].begin());
                    ans.insert(e[x] + *--g[x].end());
                }
            }
            a[x] = y;
        }
        if (op == 2) {
            int x = rd();
            printf("%lld\n", f[x] + e[a[x]]);
        }
        if (op == 3) printf("%lld %lld\n", *ans.begin(), *--ans.end());
    }
    return 0;
}