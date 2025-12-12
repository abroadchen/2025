//
// Created by Psy.C on 2025/12/12.
//
/*
*后缀自动机的状态节点。
nxt[26]：指向下一个状态的转移边数组（对应 a-z 字符）。
fa：父节点指针（suffix link）。
mx：当前节点代表子串的最大长度。
创建全局数组 t[] 存储所有状态节点（大小为 N*2）
 *siz：记录当前构造出的节点数量
 *
*向后缀自动机中添加一个新的字符，并维护其结构。
参数说明：
p：当前所在节点编号；
c：新增加的字符索引（相对于 'a'）。
返回值：新创建或更新后的节点编号
*如果从当前节点 p 可以通过字符 c 转移到另一个节点，并且满足最长长度条件，则直接返回目标节点。
否则新建一个节点 np 并设置其最大长度。
沿着 suffix link 回溯并建立新的转移边直到找到已有转移为止。
根据情况判断是否需要拆分旧节点来维持正确性
 *
*计算字符串 s 的最小周期长度。
使用了经典的 KMP 失配函数构建方法。
最终返回的是字符串的最短重复周期长度
 *
*快速读取输入字符串 str，将其转换成从索引 1 开始存储的字符数组 s[]。
初始化后缀自动机相关数据结构：
清空状态表 t[]；
设置初始状态 0 的最大长度为 -1；
将初始状态的所有转移都指向根节点 1；
初始化计数数组 r[]、桶排序辅助数组 tx[] 和拓扑排序 ID 数组 id[]
 *
*遍历整个原始字符串，在后缀自动机上逐个插入字符。
统计每个节点被访问的次数（即有多少个子串对应于这个节点）。
对所有节点按照长度进行桶排序得到拓扑序。
自底向上合并各个节点的访问次数到其父节点中
 *
*输入查询次数 m。
循环处理每次查询请求：
获取待查字符串 q；
计算其最小周期长度 tr；
在已构造好的 SAM 上模拟匹配过程，累计符合条件的节点访问次数作为答案输出
 *
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000005
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;


struct node { int nxt[26], fa, mx; } t[N<<1];
int siz;
int f(int p, const int c) {
    if (t[p].nxt[c] && t[p].mx + 1 == t[t[p].nxt[c]].mx) return t[p].nxt[c];
    const int np = ++siz; t[np].mx = t[p].mx + 1;
    for (; !t[p].nxt[c]; p = t[p].fa) t[p].nxt[c] = np;
    const int q = t[p].nxt[c];
    if (t[p].mx + 1 == t[q].mx) t[np].fa = q;
    else {
        const int nq = ++siz;
        t[nq] = t[q], t[nq].mx = t[p].mx + 1;
        t[q].fa = t[np].fa = nq;
        for (; t[p].nxt[c] == q; p = t[p].fa) t[p].nxt[c] = nq;
    }
    return np;
}

int fail[N];
int kmp(const char s[], const int n) {
    fail[0] = fail[1] = 0;
    for (int i = 2; i <= n; ++i) {
        int k = fail[i-1];
        while (k > 0 && s[i] != s[k+1]) k = fail[k];
        fail[i] = k + (s[k+1] == s[i] ? 1 : 0);
    }
    int x = fail[n];
    while (x > 0 && n % (n - x) != 0) x = fail[x];
    return n - x;
}

int main() {
    fast;
    string str; cin >> str;
    const int n = static_cast<int>(str.length());
    char s[N];
    for (int i = 0; i < n; ++i) s[i + 1] = str[i];
    memset(t, 0, sizeof(t));
    siz = 1; t[0].mx = -1;
    for (int& i : t[0].nxt) i = 1;
    int r[N<<1]={}, tx[N]={}, id[N<<1];
    for (int i = 1, p = 1; i <= n; ++i) p = f(p, s[i] - 'a'), r[p]++;
    rep(i,siz) tx[t[i].mx]++;
    rep(i,n) tx[i] += tx[i-1];
    rep(i,siz) id[tx[t[i].mx]--] = i;
    for (int i = siz; i >= 1; --i) r[t[id[i]].fa] += r[id[i]];
    int m; cin >> m;
    while (m--) {
        string q; cin >> q;
        const int len = static_cast<int>(q.length());
        for (int i = 0; i < len; ++i) s[i + 1] = q[i];
        const int tr = kmp(s, len);
        ll ans = 0;
        int p = 1, ok = 0;
        rep(i,len) {
            const int c = s[i] - 'a';
            while (!t[p].nxt[c]) p = t[p].fa, ok = t[p].mx;
            p = t[p].nxt[c]; ok++;
        }
        rep(i,tr) {
            const int c = s[i] - 'a';
            while (!t[p].nxt[c]) p = t[p].fa, ok = t[p].mx;
            p = t[p].nxt[c]; ok++;
            while (t[t[p].fa].mx >= len) p = t[p].fa, ok = t[p].mx;
            if (ok >= len) ans += r[p];
        }
        cout << ans << '\n';
    }
    return 0;
}