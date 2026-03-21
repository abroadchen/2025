//
// Created by Psy.C on 2026/3/21.
//
/**
邻接表存储树结构
tr[][]: Trie节点数组，支持26个小写字母
init(): 重置Trie结构
每个节点最多被轻边访问O(log n)次
总时间复杂度：O(n log n)

++tot
预先将tot增加1，分配一个新的Trie节点ID
tot是从1开始的节点编号计数器
2. s[son[x]]-'a'+1
son[x]：x节点的重儿子
s[son[x]]：重儿子节点的字符
s[son[x]]-'a'+1：将字符转换为数字索引(1-26)
3. tr[++tot][...] = rt
创建一个新节点，该节点通过字符s[son[x]]指向原来的根节点rt
第二行：rt = tot;
将新创建的节点设为新的根节点
本质上是在Trie的根部插入了一个新节点
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+5;

vector<int> v[N];
void add(int x, int y) { v[x].push_back(y); }

int tot=1, tr[N][27], rt;
void init() {
    for (int i = 1; i <= tot; ++i)
        for (int j = 1; j <= 26; ++j)
            tr[i][j] = 0;
    rt = tot = 1;
}

int sz[N], son[N];
void dfs(int x, int fa) {
    sz[x] = 1;
    int cnt = 0;
    for (int y : v[x]) {
        if (y == fa) continue;
        dfs(y, x);
        sz[x] += sz[y];
        if (sz[y] > cnt) {
            cnt = sz[y];
            son[x] = y;//找到最大子树作为重儿子
        }
    }
}

char s[N];
///将轻儿子子树的字符路径插入Trie
void dfs(int x, int fa, int sn, int p) {
    for (int y : v[x]) {
        if (y == fa || y == sn) continue;
        if (!tr[p][s[y]-'a'+1])
            tr[p][s[y]-'a'+1] = ++tot;
        dfs(y, x, sn, tr[p][s[y]-'a'+1]);
    }
}

int c[N], ans, cnt;
void dfs(int x, int fa, int p) {
    for (int y : v[x]) {
        if (y == fa) continue;
        if (y != son[x]) {
            dfs(y, x, rt);//处理轻儿子
            init();//清空Trie，避免影响其他子树
        }
    }
    if (son[x]) {
        dfs(son[x], x, rt);//先处理重儿子（保留其贡献）
        tr[++tot][s[son[x]]-'a'+1] = rt;//连接当前节点到重儿子
        rt = tot;
        dfs(x, fa, son[x], rt);//将当前节点连接到Trie
    }
    if (tot + c[x] > ans)//更新最大值
        ans = tot + c[x], cnt = 1;
    else if (tot + c[x] == ans) ++cnt;//更新计数
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<typename T,typename... Args>
void rd(T& t,Args&... args) {
    rd(t); rd(args...);
}

int n;
int main() {
    fast;
    rd(n);
    for (int i = 1; i <= n; ++i) rd(c[i]);//读取节点权值
    scanf("%s", s + 1);//读取节点字符
    for (int i = 1, x, y; i < n; ++i) {
        rd(x, y); add(x, y); add(y, x);
    }
    dfs(1, 0); dfs(1, 0, rt);
    cout << ans << '\n' << cnt << '\n';//最大值和方案数
    return 0;
}