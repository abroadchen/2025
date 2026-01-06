/**
* nxt[27]: 转移数组，大小为27（26个字母+1个特殊字符）
fa: 后缀链接，指向该节点的后缀链接节点
mx: 该节点表示的最长字符串长度
t[N<<1]: 后缀自动机数组，大小为2*N
*lst=1: 记录当前处理字符串的最后一个后缀节点（初始为1）
siz=1: 当前后缀自动机中节点的数量（初始为1）
tot[N<<1][12]: 计数数组，tot[i][j]表示第j类字符串在节点i中出现的次数
 *
*solve函数：向后缀自动机中添加字符c，标记为id类
p = lst: 从当前最后一个节点开始
np = ++siz: 创建新节点np，节点编号递增
*tot[np][id]++: 在新节点np中，id类字符串计数+1
t[np].mx = t[p].mx + 1: 新节点的最长字符串长度比当前节点+1
*从节点p开始，沿着后缀链接向上，直到找到有字符c转移边的节点
在路径上的所有节点添加字符c的转移边，指向新节点np
 *获取通过字符c能到达的节点q
*如果节点q的长度正好是p的长度+1，则np的后缀链接直接指向q
否则需要创建一个新的分割节点
*nq = ++siz: 创建新的分割节点nq
t[nq] = t[q]: 复制q节点的所有信息到nq
t[nq].mx = t[p].mx + 1: 设置nq的长度
设置q和np的后缀链接都指向nq
*将路径上所有指向q的转移边改为指向nq
更新lst为当前节点np
 *
 *s为字符串数组，n为查询数量，l和r为边界数组，tax为计数数组，id为排序后节点编号数组
*设置节点0的mx为-1（特殊节点）
将节点0的所有转移边都指向节点1
 *遍历字符串，将每个字符添加到后缀自动机，标记为第0类
*对于每个查询：
solve(26, n + 1): 添加特殊字符26（作为分隔符）
读取字符串和边界l[i], r[i]
将查询字符串添加到后缀自动机，标记为第i类
*进行基数排序：按节点长度对节点进行排序
tax[t[i].mx]++: 统计每个长度的节点数量
tax[i] += tax[i-1]: 计算前缀和
id[tax[t[i].mx]--] = i: 根据长度排序节点编号
 *
 *从大到小遍历排序后的节点（拓扑排序顺序）
*将当前节点x的计数信息传递给其后缀链接节点
这样可以统计每个节点在所有后缀路径中出现的次数
 *如果第0类字符串（原字符串）在该节点中出现次数为0，则跳过
*检查当前节点是否满足所有查询的边界条件
flag &= ...: 使用按位与更新flag，如果任何条件不满足，flag变为false
*如果满足所有条件，将该节点代表的子串数量加到答案中
t[x].mx - t[t[x].fa].mx: 该节点表示的长度范围内的不同子串数量
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define ll long long
#define N 550005
using namespace std;

struct node { int nxt[27], fa, mx; } t[N<<1];

int lst=1, siz=1;
ll tot[N<<1][12];
void solve(const int c, const int id) {
    int p = lst; const int np = ++siz;
    tot[np][id]++;
    t[np].mx = t[p].mx + 1;
    for (; !t[p].nxt[c]; p = t[p].fa) t[p].nxt[c] = np;
    const int q = t[p].nxt[c];
    if (t[q].mx == t[p].mx + 1) t[np].fa = q; else {
        const int nq = ++siz;
        t[nq] = t[q], t[nq].mx = t[p].mx + 1;
        t[q].fa = t[np].fa = nq;
        for (; t[p].nxt[c] == q; p = t[p].fa) t[p].nxt[c] = nq;
    }
    lst = np;
}

int main() {
    fast; char s[N]; int n, l[15], r[15], tax[N<<1], id[N<<1];
    t[0].mx = -1;
    for (int& i : t[0].nxt) i = 1;
    cin >> s; int m = static_cast<int>(strlen(s));
    for (int i = 0; i < m; ++i) solve(s[i] - 'a', 0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        solve(26, n + 1);
        cin >> s >> l[i] >> r[i]; m = static_cast<int>(strlen(s));
        for (int j = 0; j < m; ++j) solve(s[j] - 'a', i);
    }
    for (int i = 1; i <= siz; ++i) tax[t[i].mx]++;
    for (int i = 1; i <= siz; ++i) tax[i] += tax[i-1];
    for (int i = 1; i <= siz; ++i) id[tax[t[i].mx]--] = i;
    ll ans = 0;
    for (int i = siz; i >= 2; --i) {
        const int x = id[i];
        for (int j = 0; j <= n; ++j) tot[t[x].fa][j] += tot[x][j];
        if (tot[x][0] == 0) continue;
        bool flag = true;
        for (int j = 1; flag && j <= n; ++j) flag &= l[j] <= tot[x][j] && tot[x][j] <= r[j];
        if (flag) ans += t[x].mx - t[t[x].fa].mx;
    }
    cout << ans << '\n';
    return 0;
}