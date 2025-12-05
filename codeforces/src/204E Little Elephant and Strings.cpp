//
// Created by Psy.C on 2025/12/5.
//
/*
*N: 常量，数组最大大小
cnt: 计数器，记录处理的字符总数
a[N]: 存储字符编码的数组
b[N]: 存储字符串标识的数组
mp[N]: 映射数组，记录每个字符串最后出现的位置
root[N]: 线段树根节点数组
s[N]: 临时存储输入字符串
res[N]: 结果数组，存储每个字符串的答案
*t1[N], t2[N]: 临时数组，用于基数排序
c[N]: 计数数组
sa[N]: 后缀数组，sa[i]表示排名第i的后缀在原串中的起始位置
 *
*初始化基数排序
x[i] = t[i]: 将输入数组复制到x中作为第一关键字
计算每个字符的出现次数并转换为前缀和
根据第一关键字对后缀进行排序
 *
*j: 当前比较的长度，每次翻倍
构造第二关键字y数组
对二元组(x[i], x[i+j])进行基数排序
重新分配排名，相同二元组获得相同排名
如果所有后缀排名都不同则提前结束
 *
*rk[N]: rank数组，rk[i]表示起始位置为i的后缀的排名
h[N]: height数组，h[i]表示sa[i]和sa[i-1]的最长公共前缀长度
利用height数组的性质优化计算：h[i] ≥ h[i-1]-1
*
*构建ST表(稀疏表)用于RMQ查询
d[N][19]: ST表，d[i][k]表示从位置i开始长度为2^k的区间的最小值
预处理实现O(1)时间内的区间最小值查询
 *
*l, r: 左右子节点编号
sum: 区间和
T[N*40]: 线段树节点数组(主席树)
tot: 节点计数器
 *
*主席树单点更新
创建新版本的线段树，在位置pos增加val
采用函数式编程思想，保留历史版本
 *
*ST表区间最小值查询
查询区间[l,r]内的最小height值
 *
*：计算两个后缀的最长公共前缀长度
特殊情况处理：相同后缀、相邻后缀等
 *
*二分查找左侧边界
找到最大的l使得lcp(l,x) ≥ k
*二分查找右侧边界
找到最小的r使得lcp(x,r) ≥ k
 *
*主席树区间查询
查询版本fa中[k,n]区间的元素个数
 *
*读取n个字符串并处理：
如果k=1，直接输出每个字符串的子串数：l*(l+1)/2
将字符串连接，用分隔符分开
a[]: 存储字符编码(1-26)
b[]: 存储所属字符串编号，分隔符标记为n+1
*添加终止符
构建后缀数组、height数组和ST表
*从后往前构建主席树：
对每个后缀，更新其所属字符串的最新位置
维护每个字符串在各个位置的出现情况
*对每个后缀计算其对答案的贡献：
二分搜索最长公共前缀长度
使用主席树查询包含该后缀且LCP≥m的后缀个数
如果个数≥k，则更新答案
 *
 *
*x[i] - 获取第i个元素的关键字（字符编码）
c[x[i]] - 获取该关键字的计数器值
--c[x[i]] - 将该计数器值减1（前置递减）
sa[--c[x[i]]] - 访问sa数组的相应位置
sa[--c[x[i]]] = i - 将i赋值给sa数组的该位置
 *将后缀i放置到排序后的正确位置
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+10;
int cnt, a[N], b[N], mp[N], root[N];
char s[N];
ll res[N];

int t1[N], t2[N], c[N], sa[N];
void build(const int t[], const int n, int m) {
    int i, *x = t1, *y = t2;
    for (i = 0; i < m; ++i) c[i] = 0;
    for (i = 0; i < n; ++i) c[(x[i] = t[i])]++;
    for (i = 1; i < m; ++i) c[i] += c[i-1];
    for (i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
    for (int j = 1; j <= n; j <<= 1) {
        int p = 0;
        for (i = n - j; i < n; ++i) y[p++] = i;
        for (i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
        for (i = 0; i < m; ++i) c[i] = 0;
        for (i = 0; i < n; ++i) c[x[y[i]]]++;
        for (i = 1; i < m; ++i) c[i] += c[i-1];
        for (i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
        swap(x, y); p = 1; x[sa[0]] = 0;
        for (i = 1; i < n; ++i) x[sa[i]] = y[sa[i-1]] == y[sa[i]] &&
            y[sa[i-1]+j] == y[sa[i]+j] ? p - 1 : p++;
        if (p >= n) break;
        m = p;
    }
}

int rk[N], h[N];
void get(const int t[], const int n) {
    int i, k = 0;
    for (i = 0; i <= n; ++i) rk[sa[i]] = i;
    for (i = 0; i < n; ++i) {
        if (k) k--;
        const int j = sa[rk[i] - 1];
        while (t[i+k] == t[j+k]) k++;
        h[rk[i]] = k;
    }
}

int d[N][19];
void init(const int n) {
    for (int i = 1; i <= n; ++i) d[i][0] = h[i];
    for (int k = 1; (1<<k) <= n; ++k) for (int i = 0; i + (1<<k) <= n; ++i) {
        d[i][k] = min(d[i][k-1], d[i+(1<<(k-1))][k-1]);
    }
}


struct node { int l, r, sum; } T[N*40];
int tot = 0;
void update(const int l, const int r, int& x, const int y, const int pos, const int val) {
    T[++tot] = T[y], T[tot].sum += val;
    x = tot;
    if (l == r) return;
    const int m = (l + r) >> 1;
    if (pos <= m) update(l, m, T[x].l, T[y].l, pos, val);
    else update(m + 1, r, T[x].r, T[y].r, pos, val);
}

int query(const int l, const int r) {
    int k = 0;
    while (1<<(k+1) <= r - l + 1) k++;
    return min(d[l][k], d[r-(1<<k)+1][k]);
}

int lcp(int l, int r) {
    if (l == r) return cnt - sa[l];
    if (l > r) swap(l, r);
    if (l + 1 == r) return h[r];
    return query(l + 1, r);
}

int getl(const int x, const int k) {
    int l = 1, r = x, ans = 0;
    while (l <= r) {
        const int m = (l + r) >> 1;
        if (lcp(m, x) >= k) { ans = m; r = m - 1; }
        else l = m + 1;
    }
    return ans;
}
int getr(const int x, const int k) {
    int l = x, r = cnt, ans = 0;
    while (l <= r) {
        const int m = (l + r) >> 1;
        if (lcp(m, x) >= k) { ans = m; l = m + 1; }
        else r = m - 1;
    }
    return ans;
}

int query(const int l, const int r, const int fa, const int k) {
    if (l == r) return T[fa].sum;
    const int m = (l + r) >> 1;
    if (m < k) return T[T[fa].l].sum + query(m + 1, r, T[fa].r, k);
    return query(l, m, T[fa].l, k);
}

int main() {
    fast;
    int n, k; cin>>n>>k; cnt = 0;
    int mx = 'z' - 'a' + 2;//字符集大小，用于分隔符
    for (int i = 1; i <= n; ++i) {
        cin>>s;
        const int l = static_cast<int>(strlen(s));
        if (k == 1) cout << 1ll*l*(l+1)/2 << ' ';
        for (int j = 0; j < l; ++j) a[cnt] = s[j] - 'a' + 1, b[cnt++] = i;
        if (i < n) a[cnt] = mx++, b[cnt++] = n + 1;
    }
    if (k == 1) return cout << '\n', 0;
    a[cnt] = 0; b[cnt] = n + 1;
    build(a, cnt + 1, mx + 2); get(a, cnt); init(cnt);
    for (int i = cnt; i >= 1; --i) {
        const int t = b[sa[i]];
        if (!mp[t]) update(1, cnt, root[i], root[i+1], i, 1);
        else {
            update(1, cnt, root[i], root[i+1], mp[t], -1);
            update(1, cnt, root[i], root[i], i, 1);
        }
        mp[t] = i;
    }
    for (int i = 1; i <= cnt; ++i) {
        if (b[sa[i]] == n + 1) continue;
        int l = 0, r = max(h[i], h[i+1]), ans = 0;
        while (l <= r) {
            const int m = (l + r) >> 1, fl = getl(i, m), fr = getr(i, m),
            num = query(1, cnt, root[fl], fr);
            if (num >= k) { ans = m; l = m + 1; }
            else r = m - 1;
        }
        res[b[sa[i]]] += 1ll*ans;
    }
    for (int i = 1; i <= n; ++i) cout << res[i] << ' ';
    cout << '\n';
    return 0;
}