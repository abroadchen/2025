//
// Created by Psy.C on 2025/11/12.
//
/*
*n,m：网格行列数
s：颜色种类数
X,Y：起始坐标
a[][]：第一张图的颜色矩阵
c[]：每种颜色的计数
b[][]：第二张图的颜色矩阵
p[][]：螺旋矩阵（用于排序）
mp：颜色值到编号的映射
 *
 *排序：按照相对于(X,Y)位置在螺旋矩阵中的顺序
 *数组q，用于BFS
 *v，用于存储每种颜色的所有节点
 *
*读入第一张图：
对于每个位置(i,j)的颜色值k
如果k已经在映射中，则使用现有编号；否则创建新编号
更新颜色计数c[]
*读入第二张图：
对于每个位置(i,j)的颜色值k（如果不是-1）
建立颜色映射
将该位置作为节点添加到对应颜色的向量中
 *
*读入起始坐标(X,Y)
初始化螺旋矩阵中心点为1
*构建螺旋矩阵：
从中心向外螺旋填充数字
每一圈按右→下→左→上的顺序填充
 *
*初始化答案为0
将起始位置加入队列
*BFS过程：
l是队列头指针，r是队列尾指针
k是当前位置的颜色编号
u是下一个位置的颜色编号
条件判断：颜色有效且不同且存在该颜色节点
合并颜色计数，累加答案
更新当前位置
按螺旋顺序排序该颜色的所有节点
将这些节点加入队列
 */
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 305, M = 2e5+5, K = N - 5;
int n, m, s, X, Y, a[N][N], c[M], b[N][N], p[605][605];
map<int, int> mp;

struct Node {
    int x, y, c;
    Node(int _x=0, int _y=0, int _c=0) : x(_x), y(_y), c(_c) {}
    bool operator<(const Node& b) const {
        return p[x-X+K][y-Y+K] < p[b.x-X+K][b.y-Y+K];
    }
} q[M];
vector<Node> v[M];

int main() {
    scanf("%d%d", &n, &m); mp[0] = s = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1, k; j <= m; ++j) {
            scanf("%d", &k);
            a[i][j] = (mp[k] ? mp[k] : mp[k]=++s);
            c[a[i][j]]++;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1, k; j <= m; ++j) {
            scanf("%d", &k);
            if (k > -1) {
                b[i][j] = (mp[k] ? mp[k] : mp[k]=++s);
                v[a[i][j]].push_back(Node(i,j,b[i][j]));
            }
        }
    }
    scanf("%d%d", &X, &Y); p[K][K] = 1;
    for (int i = 2, x = K - 1, y = K - 1, k = 1;
        i <= 600; i += 2, x--, y--) {
        for (int j = 0; j < i; ++j) p[x][++y] = ++k;
        for (int j = 0; j < i; ++j) p[++x][y] = ++k;
        for (int j = 0; j < i; ++j) p[x][--y] = ++k;
        for (int j = 0; j < i; ++j) p[--x][y] = ++k;
        }
    ll ans(0); q[1] = Node(X, Y, b[X][Y]);
    for (int l = 1, r = 1, k = a[X][Y], u; l <= r; ++l, k = u) {
        if (k > 1 && (u = q[l].c) != k && c[k]) {
            c[u] += c[k];
            ans += c[k];
            c[k] = 0;
            X = q[l].x, Y = q[l].y;
            sort(v[k].begin(), v[k].end());
            for (const Node& i : v[k]) q[++r] = i;
            v[k].clear();
        }
    }
    printf("%lld\n", ans);
    return 0;
}
