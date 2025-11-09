//
// Created by Psy.C on 2025/11/9.
//
/*
 *dsu(N)：并查集数组，用于存储每个节点的父节点
 *
*第一个while循环：找到节点a的根节点c
第二个while循环：将从a到根节点路径上的所有节点直接连接到根节点（路径压缩）
返回根节点
 *
 *读取节点数n和边数m，初始化答案ans为1
 *每个节点的父节点初始化为自己，即每个节点都是一个独立的集合
 *
*读取边的两个端点a和b
找到a和b所在的集合的根节点c和d
如果c≠d：说明a和b属于不同集合，将它们合并
如果c==d：说明a和b已经在同一集合中，形成环，ans乘以2并对mod取模
输出(ans-1+mod)%mod（加mod是为了处理负数情况）
 *
 *ans-1 = 2^k - 1 表示除去空集的组合数
 */
#include <iostream>
#include <vector>
using namespace std;

const int N = 5e5, mod = 1e9+9;
vector<int> dsu(N);

int f(int a) {
    int c = a;
    while (c != dsu[c]) c = dsu[c];
    int e = a, d;
    while (e != dsu[e]) {
        d = dsu[e];//保存e的父节点到临时变量d
        dsu[e] = c;//将e的父节点直接设置为根节点c
        e = d;//将e更新为原来的父节点，继续向上处理
    }
    return c;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, a, b, m, ans(1); cin >> n >> m;
    for (int i = 1; i <= n; ++i) dsu[i] = i;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        int c = f(a), d = f(b);
        if (c != d) dsu[c] = d;
        else {
            ans *= 2;
            ans %= mod;
        }
        cout << (ans - 1 + mod) % mod << '\n';
    }

    return 0;
}