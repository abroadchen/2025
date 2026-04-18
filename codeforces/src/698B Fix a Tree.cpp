//
// Created by Psy.C on 2026/4/17.
//
/**
n: 节点数量
p[i]: 节点i指向的下一个节点
v: 存储形成环的节点

如果存在自环节点(rt != -1)，选择自环节点作为根
否则选择最后一个发现的环节点作为根

时间复杂度：O(nα(n))，其中α是阿克曼函数的反函数
空间复杂度：O(n)

阿克曼函数 A(m,n) 是一个快速增长的递归函数
A(0, n) = n + 1
A(m, 0) = A(m-1, 1)  (当 m > 0)
A(m, n) = A(m-1, A(m, n-1))  (当 m, n > 0)

α(n) = min{k | A(k, k) ≥ n}

n	                          α(n)
1 to 4	                        1
5 to 2040	                    2
2041 to ~2^2^2^...^2 (巨大数字)	3
实际应用中	                  ≤ 4

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
int fa[N];
int find(int x) {
    return fa[x] ? find(fa[x]) : x;
}
int n, p[N];
vector<int> v;
int main() {
    fast;
    cin >> n;
    int rt = -1;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        if (p[i] == i) rt = i;//节点i指向自己，是一个自环
        //节点i和它指向的节点p[i]已经在一个连通分量中，形成了环
        if (i == find(p[i])) v.push_back(i);
        else fa[i] = p[i];//建立并查集关系
    }
    int res = rt == -1 ? v.back() : rt;
    for (int i : v) p[i] = res;
    cout << v.size()-(rt!=-1) << '\n';//需要修改的边数
    for (int i = 1; i <= n; ++i) {
        if (i == 1) cout << p[i];
        else cout << ' ' << p[i];
    }
    cout << '\n';
    return 0;
}