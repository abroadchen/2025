//
// Created by Psy.C on 2025/12/12.
//
/*
*n：第一个序列的长度
m：第二个序列的长度
a[N]：存储合并后的序列数据
 *参数st表示起始状态（0或1），vis是结果数组
*cnt：计数器，记录已放置的元素个数
l：左指针，指向第一个序列的当前位置（从1开始）
r：右指针，指向第二个序列的当前位置（从n+1开始）
 *
*
定义两个数组v1和v2用于存储两种策略的结果
调用ok函数，起始状态为0，结果存储在v1中
定义向量r1用于存储第一种策略的切换点
*遍历v1数组，找出相邻元素值不同的位置（即需要切换状态的位置）
将这些位置存储在r1中
*调用ok函数，起始状态为1，结果存储在v2中
找出第二种策略的切换点并存储在r2中
*比较两种策略的切换次数，选择切换次数较少的策略
使用memcpy复制选中的结果到res数组
将对应的切换点列表赋值给ans
 *输出最终的排列顺序
 *输出切换点的数量和具体的切换位置
 */
#include <iostream>
#include <cstring>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 500005
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;


int n, m, a[N];
void ok(int st, int vis[]) {
    memset(vis,0,sizeof(int) * N);
    int cnt = 0, l = 1, r = n + 1;
    while (l <= n || r <= n + m) {//当还有未处理的元素时继续循环
        while (l <= n && a[l] == st) vis[++cnt] = l++;//当第一个序列还有元素且当前元素等于st时，将其放入结果数组
        while (r <= n + m && a[r] == st) vis[++cnt] = r++;
        st = 1 - st;//切换状态（0变1，1变0）
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    cin>>n; rep(i,n) cin>>a[i];
    cin>>m; for (int i = n + 1; i <= n + m; ++i) cin>>a[i];
    int v1[N], v2[N]; ok(0, v1); vector<int> r1;
    for (int i = 1; i <= n + m; ++i) if (a[v1[i]] != a[v1[i+1]]) {
        r1.push_back(i);
    }
    ok(1, v2); vector<int> r2;
    for (int i = 1; i <= n + m; ++i) if (a[v2[i]] != a[v2[i+1]]) {
        r2.push_back(i);
    }
    vector<int> ans; int res[N];
    if (r2.size() <= r1.size()) { memcpy(res, v2, sizeof v2); ans = r2; }
    else { memcpy(res, v1, sizeof v1); ans = r1; }
    for (int i = 1; i <= n + m; ++i) cout << res[i] << ' ' << '\n';
    cout << ans.size() << '\n';
    for (const int an : ans) cout << an << ' ' << '\n';
    return 0;
}