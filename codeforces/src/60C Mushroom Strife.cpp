//
// Created by Psy.C on 2025/10/27.
//
/*
*m: 边的数量
v, u: 边的两个端点
g: gcd值
l: lcm值
*定义边的结构体：
to: 连接的另一个节点
gcd: 两个节点值的最大公约数
lcm: 两个节点值的最小公倍数
构造函数初始化这些成员
 *邻接表表示图，to[i]存储与节点i相连的所有边
 *
 */
#include <algorithm>
#include <ios>
#include <iostream>
#include <vector>
#define rep(i,n) for(int (i)=1;(i)<=(int)(n);++(i))
using namespace std;
typedef long long ll;
const int N = 105;
int n, m, v, u, g, l;

struct Edge {
    int to;
    ll gcd, lcm;
    Edge(int u, int g, int l) : to(u), gcd(g), lcm(l) {}
};
vector<Edge> to[N];
ll a[N];//存储每个节点的值


bool dfs(int v) {//验证和填充节点值
    for (auto x : to[v]) {//遍历与当前节点v相连的所有边
        if (a[x.to]) {//如果相邻节点已经有值
            if (__gcd(a[v], a[x.to]) != x.gcd) return 0;//当前节点与相邻节点的实际gcd是否等于给定的gcd值
            if (a[v] * a[x.to] != x.lcm * x.gcd) return 0;//两节点值的乘积是否等于gcd*lcm
            continue;//继续检查下一条边
        }//如果相邻节点还没有值
        a[x.to] = x.lcm * x.gcd / a[v];//如果gcd(a,b)lcm(a,b) = ab，则b = gcd*lcm/a
        if (a[x.to] <= 0 || a[x.to] > 1000000) return 0;
        if (__gcd(a[v], a[x.to]) != x.gcd) return 0;
        if (a[v] * a[x.to] != x.lcm * x.gcd) return 0;
        if (!dfs(x.to)) return 0;//递归检查新设置值的节点，如果失败则返回false
    }
    return 1;
}

void clear(int v) {//回溯时清除已设置的值
    a[v] = 0;//将当前节点值清零
    for (auto x : to[v]) if (a[x.to]) clear(x.to);//递归清除所有已设置值的相邻节点
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;//读入节点数和边数
    while (m--) {//循环读入m条边的信息
        cin >> v >> u >> g >> l;
        to[v].push_back(Edge(u, g, l));//在邻接表中添加无向边
        to[u].push_back(Edge(v, g, l));
    }
    rep(i,n) {//对每个节点进行处理
        if (a[i]) continue;//如果节点已有值则跳过
        rep(j,1000000) {
            a[i] = j;//设置节点i的值
            if (!dfs(i)) clear(i);//如果DFS验证失败，则清除此次赋值
            else break;//否则跳出循环，确定该节点的值
        }
        if (!a[i]) { cout << "NO"; return 0; }//如果没有找到合适的值
    }
    cout << "YES\n";
    rep(i,n) cout << a[i] << " ";//输出每个节点的值
    return 0;
}