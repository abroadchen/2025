//
// Created by Psy.C on 2026/2/10.
//
/**
后缀自动机(SAM)节点：
nxt[26]：转移数组（26个小写字母）
fa：后缀链接（fail指针）
mx：该节点最长串的长度
rt：SAM根节点
siz：当前节点数量

清空t数组
根节点rt=1，当前大小siz=1
t[0].mx = -1：虚拟节点长度为-1
t[0].nxt[i] = 1：所有转移指向根节点

p：当前状态（节点）
c：要插入的字符（0-25表示'a'-'z'）
返回：插入字符后的新状态（节点）
t[p].nxt[c]：当前节点p有字符c的转移
t[p].mx + 1 == t[t[p].nxt[c]].mx：转移后的节点长度正好比当前节点长1
创建新节点np，长度为p的长度+1
这是因为我们需要一个新的状态来表示字符串p+c
当p没有字符c的转移时，沿着后缀链接向上
在路径上的每个节点都建立字符c到np的转移
这确保了所有包含p作为后缀的字符串都能正确转移到np
p经过字符c到达q，且q的长度=p长度+1 操作：直接让np的后缀链接指向q 原因：q已经是最优的后缀链接
分裂操作：
创建新节点nq，复制q的信息，但长度改为t[p].mx + 1
让原来的q和新的np都指向nq作为后缀链接
将路径上的所有指向q的转移改为指向nq

s[N]：输入字符串缓存
n：最小字符串长度
r[S][3]：每个节点在3个字符串中的出现次数
in[S]：拓扑排序入度
hd, tl, q[S]：拓扑排序队列
ans[N]：最终答案数组

r[p][i]++：在路径节点上标记字符串i的贡献

i从2到siz遍历所有节点（节点0和1是特殊节点）
t[i].fa：节点i的后缀链接指向的父节点
in[t[i].fa]++：父节点的入度+1

将所有入度为0的节点加入队列
从队列头部取出一个节点x
r[x][i]：节点x在第i个字符串中的出现次数
将x的计数传递给其父节点t[x].fa
这样实现了从叶子向根的计数聚合
父节点的入度减1
表示从x到父节点这条边被"处理"了
t[x].fa > 1：确保不是根节点（根节点是虚拟节点）
!in[t[x].fa]：父节点入度为0，说明所有子节点都已处理
将父节点加入队列等待处理

r[i][0]：节点i在第1个字符串中的出现次数
r[i][1]：节点i在第2个字符串中的出现次数
r[i][2]：节点i在第3个字符串中的出现次数
add = r[i][0] * r[i][1] * r[i][2]：以节点i代表的子串作为公共子串的方案数
ans[t[t[i].fa].mx + 1] += add：在区间起始处加add
ans[t[i].mx + 1] -= add：在区间结束后的下一处减add
将差分数组还原为实际答案

时间复杂度：O(总字符数)，SAM的线性性质
空间复杂度：O(总字符数)
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 300005
#define S N<<1
#define mod 1000000007
using namespace std;

struct SAM { int nxt[26], fa, mx; } t[S];

int rt, siz;
void init() {
    memset(t, 0, sizeof(t));
    rt = siz = 1;
    t[0].mx = -1;
    for (int& i : t[0].nxt) i = 1;
}

int ex(int p, const int c) {
    if (t[p].nxt[c] && t[p].mx + 1 == t[t[p].nxt[c]].mx) return t[p].nxt[c];
    const int np = ++siz;
    t[np].mx = t[p].mx + 1;
    for (; !t[p].nxt[c]; p = t[p].fa) t[p].nxt[c] = np;
    if (const int q = t[p].nxt[c]; t[p].mx + 1 == t[q].mx) t[np].fa = q;
    else {
        const int nq = ++siz;
        t[nq] = t[q], t[nq].mx = t[p].mx + 1;
        t[q].fa = t[np].fa = nq;
        for (; t[p].nxt[c] == q; p = t[p].fa) t[p].nxt[c] = nq;
    }
    return np;
}

char s[N];
int n = 1e9, r[S][3], in[S], hd, tl, q[S], ans[N];

int main() {
    fast;
    init();
    for (int i = 0, now; i < 3; ++i) {
        scanf("%s", s + 1); n = min(n, now=strlen(s + 1));
        for (int j = 1, p = rt; j <= now; ++j)
            r[p=ex(p, s[j]-'a')][i]++;
    }
    for (int i = 2; i <= siz; ++i) in[t[i].fa]++;
    hd = tl = 0;
    for (int i = 2; i <= siz; ++i) if (in[i] == 0) q[++tl] = i;
    while (hd < tl) {
        const int x = q[++hd];
        for (int i = 0; i < 3; ++i) r[t[x].fa][i] += r[x][i];
        in[t[x].fa]--;
        if (t[x].fa > 1 && !in[t[x].fa]) q[++tl] = t[x].fa;
    }
    memset(ans, 0, sizeof ans);
    for (int i = 2; i <= siz; ++i) {
        const int add = 1ll*r[i][0]*r[i][1]*r[i][2]%mod;
        (ans[t[t[i].fa].mx + 1] += add) %= mod;
        (ans[t[i].mx + 1] += mod - add) %= mod;
    }
    for (int i = 1; i <= n; ++i) {
        ans[i] = (ans[i] + ans[i-1]) % mod;
        printf("%d ", ans[i]);
    }
    return 0;
}