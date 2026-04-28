//
// Created by Psy.C on 2026/4/28.
//
/**
v为目标节点，c为容量，n为下一条边的索引
H: 邻接表头指针数组
cntE: 边计数器
E: 边数组
d: 距离标号数组
gap: gap优化数组
cur: 当前弧数组
pre: 前驱节点数组
s,t: 源汇点
nv: 节点数
flow: 最大流
n: 输入的节点数
disc,sizc: 输入的约束条件
tree: 存储树形结构
cir: 存储环形结构
nolim: 标记无限制节点
used: 标记已使用节点
siz: 大小数组
nxt: 下一节点数组
has: 标记存在性
pos: 位置信息
添加正向边(u,v)容量c
添加反向边(v,u)容量0（残量网络）
从汇点t开始BFS，计算各点到t的距离
初始化距离数组d和gap数组
实现ISAP算法（Improved Shortest Augmenting Path）
寻找增广路径并更新流量
使用当前弧优化和gap优化
根据最大流结果重构解
根据流量为0的边构建环和树结构
输出最终结果
构建网络流模型
运行最大流算法
检查是否可行并输出
初始化数据结构
读入输入数据
尝试构造解决方案

 */
#include <bits/stdc++.h>
#define ii pair<int, int>
#define clr(a,x) memset (a, x, sizeof a)
using namespace std;
constexpr int MAXN = 1007, MAXE = 1e6+7, INF = 0x3f3f3f3f;

struct Edge { int v, c, n; } ;

int H[MAXN] , cntE ;
Edge E[MAXE] ;
int d[MAXN] , gap[MAXN] , cur[MAXN] , pre[MAXN] ;
int s , t , nv , flow ;
int n ;

int disc[MAXN] , sizc[MAXN] ;
int tree[MAXN][MAXN] ;
vector < int > cir[MAXN] ;
int nolim[MAXN] ;
int used[MAXN] ;
int siz[MAXN] ;
int nxt[MAXN] ;
int has[MAXN] ;
ii pos[MAXN] ;


void addedge ( int u , int v , int c ) {
    E[cntE] = Edge ( v , c , H[u] ) ;
    H[u] = cntE ++ ;
    E[cntE] = Edge ( u , 0 , H[v] ) ;
    H[v] = cntE ++ ;
}

void rev_bfs () {
    clr ( d , -1 ) ; clr ( gap , 0 ) ;
    queue < int > q ;
    for ( q.push ( t ) , gap[d[t] = 0] = 1 ; !q.empty () ; q.pop () ) {
        for ( int u = q.front () , i = H[u] ; ~i ; i = E[i].n ) {
            int v = E[i].v ;
            if ( d[v] == -1 ) {
                gap[d[v] = d[u] + 1] ++ ;
                q.push ( v ) ;
            }
        }
    }
}

int isap () {
    memcpy ( cur , H , sizeof cur ) ;
    flow = 0 ;
    rev_bfs () ;
    int u = pre[s] = s , i ;
    while ( d[s] < nv ) {
        if ( u == t ) {
            int f = INF ;
            for ( i = s ; i != t ; i = E[cur[i]].v ) {
                if ( f > E[cur[i]].c ) f = E[cur[u = i]].c ;
            }
            flow += f ;
            for ( i = s ; i != t ; i = E[cur[i]].v ) {
                E[cur[i]].c -= f ;
                E[cur[i] ^ 1].c += f ;
            }
        }
        for ( i = cur[u] ; ~i ; i = E[i].n ) if ( E[i].c && d[u] == d[E[i].v] + 1 ) break ;
        if ( ~i ) {
            cur[u] = i ;
            pre[E[i].v] = u ;
            u = E[i].v ;
        } else {
            if ( 0 == -- gap[d[u]] ) break ;
            int minv = nv ;
            for ( int i = H[u] ; ~i ; i = E[i].n ) {
                int v = E[i].v ;
                if ( E[i].c && minv > d[v] ) {
                    minv = d[v] ;
                    cur[u] = i ;
                }
            }
            d[u] = minv + 1 ;
            gap[d[u]] ++ ;
            u = pre[u] ;
        }
    }
    return flow ;
}

///读取字符串，如果是'?'返回-1，否则返回数字
int get () {
    char s[5] ;
    scanf ( "%s" , s ) ;
    if ( s[0] == '?' ) return -1 ;
    int x ;
    sscanf ( s , "%d" , &x ) ;
    return x ;
}

void print() {
    clr ( used , 0 ) ;
    for ( int i = H[s] ; ~i ; i = E[i].n ) if ( E[i].c == 0 ) {
        int u = E[i].v ;
        for ( int j = H[u] ; ~j ; j = E[j].n ) if ( E[j].c == 0 ) {
            int v = E[j].v ;
            if ( v <= n + n ) cir[v - n].push_back ( u ) ;
            else {
                int x = pos[v].first , y = pos[v].second ;
                tree[x][y] = u ;
            }
        }
    }
    for ( int i = 1 ; i <= n ; ++ i ) if ( has[i] ) {
        tree[i][0] = cir[i][0] ;
        for ( int j = 1 ; j <= siz[i] ; ++ j ) {
            used[tree[i][j]] = 1 ;
            nxt[tree[i][j]] = tree[i][j - 1] ;
        }
        for ( int j = 0 ; j < cir[i].size () ; ++ j ) {
            used[cir[i][j]] = 1 ;
        }
        int now = 0 ;
        for ( int j = 0 ; j < cir[i].size () ; ++ j ) {
            used[cir[i][j]] = 1 ;
            if ( j == now ) nxt[cir[i][j]] = cir[i][j + i - 1] , now += i ;
            else nxt[cir[i][j]] = cir[i][j - 1] ;
        }
    }
    for ( int i = 1 ; i <= n ; ++ i ) if ( !used[i] ) {
        if ( disc[i] == -1 ) {
            if ( sizc[i] == -1 ) nxt[i] = i ;
            else nxt[i] = cir[sizc[i]][0] ;
        } else {
            if ( sizc[i] == -1 ) {
                if ( disc[i] == 0 ) nxt[i] = i ;
                else {
                    for ( int j = 1 ; j <= n ; ++ j ) {
                        if ( tree[j][disc[i] - 1] ) {
                            nxt[i] = tree[j][disc[i] - 1] ;
                            break ;
                        }
                    }
                }
            } else nxt[i] = tree[sizc[i]][disc[i] - 1] ;
        }
    }
    for ( int i = 1 ; i <= n ; ++ i ) {
        printf ( "%d%c" , nxt[i] , i < n ? ' ' : '\n' ) ;
    }
}

int check () {
    cntE = 0 ;
    clr ( H , -1 );
    s = 0; t = n + n + n + 1; nv = t + 1;
    int L = 0 , R = 0 ;
    for ( int i = 1 ; i <= n ; ++ i ) if ( !nolim[i] ) {
        if ( disc[i] == -1 || sizc[i] == -1 ) {
            addedge ( s , i , 1 ) ;
            ++ L ;
        }
    }
    int tot = n + n ;
    for ( int i = 1 ; i <= n ; ++ i ) if ( has[i] ) {
        if ( cir[i].size () % i || cir[i].empty() ) {
            addedge ( n + i , t , i - cir[i].size () % i ) ;
            R += i - cir[i].size () % i ;
            if ( R > L ) return 0 ;
            for ( int j = 1 ; j <= n ; ++ j ) {
                if ( disc[j] == -1 && sizc[j] == -1 ) {
                    addedge ( j , n + i , 1 ) ;
                } else if ( disc[j] == -1 && sizc[j] == i ) {
                    addedge ( j , n + i , 1 ) ;
                } else if ( disc[j] == 0 && sizc[j] == -1 ) {
                    addedge ( j , n + i , 1 ) ;
                }
            }
        }
        for ( siz[i] = n ; siz[i] >= 1 ; -- siz[i] ) if ( tree[i][siz[i]] ) break ;
        for ( int j = 1 ; j <= siz[i] ; ++ j ) if ( !tree[i][j] ) {
            ++ tot ;
            ++ R ;
            if (R > L) return 0 ;
            pos[tot] = ii( i , j ) ;
            addedge ( tot , t , 1 ) ;
            for ( int k = 1 ; k <= n ; ++ k ) if (!nolim[k]) {
                if (disc[k] == -1 && sizc[k] == -1) {
                    addedge( k , tot , 1 ) ;
                } else if ( disc[k] == -1 && sizc[k] == i ) {
                    addedge( k , tot , 1 ) ;
                } else if ( disc[k] == j && sizc[k] == -1 ) {
                    addedge( k , tot , 1 ) ;
                }
            }
        }
    }
    isap();
    if (flow < R) return 0 ;
    print();
    return 1 ;
}

void solve () {
    clr(tree,0);
    for (int i = 1; i <= n; ++i) {
        cir[i].clear () ;
        has[i] = 0 ;
        nolim[i] = 0 ;
    }
    int maxv = 0 , nocir = 1 ;
    for (int i = 1; i <= n; ++i) {
        disc[i] = get(); sizc[i] = get();
        if (sizc[i] >= 0) has[sizc[i]] = 1 , nocir = 0 ;
        if (disc[i] >= 0 && sizc[i] >= 0) {
            maxv = max ( maxv , disc[i]);
            if (disc[i] == 0) cir[sizc[i]].push_back (i);
            else tree[sizc[i]][disc[i]] = i ;
        }
    }
    for ( int i = 1 ; i <= n ; ++ i ) {
        if ( disc[i] > maxv && sizc[i] == -1 ) {
            nolim[i] = 1 ;
        }
    }
    if (!nocir) {
        for (int i = 1; i <= n; ++i) if (has[i]) {
            for (int j = 1; j <= n ; ++j) if (nolim[j]) {
                tree[i][disc[j]] = j ;
            }
            if (check()) return ;
            for (int j = 1; j <= n; ++j) if (nolim[j]) {
                tree[i][disc[j]] = 0 ;
            }
        }
    } else {
        has[1] = 1 ;
        for (int j = 1 ; j <= n; ++j) if (nolim[j]) {
            tree[1][disc[j]] = j ;
        }
        if (check()) return ;
    }
    printf ("-1\n") ;
}

int main () {
    while (~scanf ("%d", &n)) solve() ;
    return 0 ;
}