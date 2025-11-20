//
// Created by Psy.C on 2025/11/20.
//
/*
*n: 点的总数
m: 限制参数
a[N]: 存储所有点的数组
 *
*计算两个点的坐标和
计数逻辑：
如果点对和不等于目标点c，则计数器s加1
如果点对和小于等于c，左指针右移
如果点对和大于等于c，右指针左移
返回条件：
如果不符合条件的点对数不超过m，返回true
 */
#include <algorithm>
#include <cstdio>
#include <set>
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

typedef pair<int,int> ii;
const int N = 2e5;
int n, m;
ii a[N];

bool ok(ii c) {
    int s(0), i(0), j(n-1);
    while (i <= j && s <= m) {
        ii u = {a[i].first + a[j].first, a[i].second + a[j].second};
        if (u != c) s++;
        if (u <= c) i++;
        if (u >= c) j--;
    }
    return s <= m;
}

int main() {
    scanf("%d%d", &n, &m);
    rep(i,n) scanf("%d%d", &a[i].first, &a[i].second);
    sort(a, a+n);//按字典序排序
    if (n <= m) return puts("-1") & 0;
    set<ii> ans;
    rep(i,m+1) for (int j = n - m - 1 + i; j < n; ++j) {
        ii c = {a[i].first + a[j].first, a[i].second + a[j].second};
        if (!ans.count(c) && ok(c)) ans.insert(c);//如果该点未被处理过且满足条件，将其加入结果集合
    }
    printf("%d\n", ans.size());
    for (auto c : ans) printf("%.1f %.1f\n", c.first*0.5, c.second*0.5);//除以2得到实际坐标
    return 0;
}