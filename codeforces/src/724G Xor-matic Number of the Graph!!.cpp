//
// Created by Psy.C on 2026/4/24.
//
/**
to[]: 边的目标节点
val[]: 边的权重
head[]: 邻接表头指针
u[x]: 记录访问顺序
f[x]: 从根到节点x的路径异或值
g[i][0/1]: 统计第i位上0/1的出现次数
c[cnt]: 存储基环中的异或值
对未访问节点：计算路径异或值并继续DFS
对已访问节点：形成环，计算环的异或值（f[x]^f[to[i]]^val[i]）
构建线性基，将环的异或值化简为最简形式
保留线性无关的基向量
cnt 为线性基的秩

pow: 2^i的值
n2: 2^cnt (mod mod)，表示线性基能生成的不同异或值数量
n1: 2^(cnt-1) (mod mod)，当基中包含第i位时的系数
如果线性基中存在第i位为1的向量：
所有节点对都可以产生该位的贡献
贡献为 C(num,2) * n1 * 2^i
否则：
只有不同位数的节点对才会产生贡献
贡献为 g[i][0]*g[i][1] * n2 * 2^i

情况1: x == 1 (线性基中存在第i位为1的向量)
任意两个节点间的路径都可以通过添加某些环来改变第i位
所有 C(num,2) 个节点对都会产生第i位的贡献
每个节点对有 n1 种方案使第i位为1
情况2: x == 0 (线性基中不存在第i位为1的向量)
路径的第i位不能被改变
只有当两个节点的路径异或值第i位不同时才有贡献
有 g[i][0]*g[i][1] 个不同位的节点对
每个节点对有 n2 种不同的环组合方式

DFS遍历: O(n+m)
高斯消元: O(cnt60) = O(m60)
总体: O((n+m)*60)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+7, mod = 1e9+7;

int to[N<<2], nxt[N<<2], head[N<<2], tot;
ll val[N<<2];
void add(int x, int y, ll z) {
    to[++tot] = y; val[tot] = z; nxt[tot] = head[x]; head[x] = tot;
}

int u[N], num, g[60][2], cnt;
ll f[N], c[N<<1];
void dfs(int fa, int x) {//DFS遍历连通块
    u[x] = ++num;//标记访问顺序
    for (int i = 0; i < 60; ++i)
        g[i][f[x]>>i&1]++;//统计当前路径异或值的每一位
    for (int i = head[x]; i; i = nxt[i]) {
        if (!u[to[i]]) {//如果相邻节点未被访问
            f[to[i]] = f[x]^val[i];//计算到相邻节点的路径异或值
            dfs(x, to[i]);//递归访问
        } else if (u[to[i]] > u[x])//相邻节点已被访问（形成环）
            c[++cnt] = f[x]^f[to[i]]^val[i];
    }
}

///得到一个线性无关的基底集合，能生成原集合的所有异或结果
void gauss() {//构建线性基
    int j = 1;//当前处理的线性基位置
    for (int i = 59, k; i >= 0; --i) {//从高位到低位处理
        for (k = j; k <= cnt && !(c[k]>>i&1); ++k) {}//寻找第i位为1的元素
        if (k > cnt) continue;//没找到，继续下一位
        swap(c[j], c[k]);//将找到的元素移到当前处理位置
        for (k = 1; k <= cnt; ++k)
            if (k != j && c[k]>>i&1) c[k] ^= c[j];//异或消除第i位
        j++;//移动到下一个线性基位置
    }
    cnt = j - 1;//更新线性基的大小
}

int ans;
void get() {//计算贡献
    ///n2: 线性基能生成的异或值数量  n1: 包含当前位的异或值数量
    int pow = 1, n1, n2 = (1ll<<cnt)%mod;
    if (cnt) n1 = (1ll<<(cnt-1))%mod;
    for (int i = 0; i < 60; ++i) {//逐位处理
        int x = 0;
        for (int j = 1; !x && j <= cnt; ++j)
            x = c[j]>>i&1;//检查线性基中是否存在第i位为1的向量
        if (x) ans = (ans+1ll*num*(num-1)/2%mod*n1%mod*pow)%mod;//所有节点对都能产生第i位的贡献
        else ans = (ans+1ll*g[i][0]*g[i][1]%mod*n2%mod*pow)%mod;//只有路径异或值第i位不同的节点对才有贡献
        pow = pow*2%mod;
    }
}

int n, m;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int x, y; ll z; cin >> x >> y >> z;
        add(x, y, z); add(y, x, z);
    }
    for (int i = 1; i <= n; ++i)
        if (!u[i]) {//对每个未访问的连通块处理
            memset(g, 0, sizeof(g));//重置统计数组
            num = cnt = 0;//重置计数器
            dfs(0, i); gauss(); get();
        }
    cout << ans << '\n';
    return 0;
}