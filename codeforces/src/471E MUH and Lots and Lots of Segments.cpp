//
// Created by Psy.C on 2026/2/13.
//
/**
左边界、右边界和x坐标
p[N]：存储水平边
q[N<<1]：存储垂直边（双倍空间）
s[N<<3]：线段树数组

n：输入矩形数量
nq：垂直边数量
np：水平边数量
org[N<<1]：记录位置对应的边编号
re[N<<1]：离散化后的坐标数组
ans：最终答案
sum[N<<1]：每个边的贡献值
st：存储活跃区间端点的集合

i=j=1：将i和j都初始化为1
i：指向当前处理的水平边
j：指向当前处理的垂直边
i <= np：遍历所有水平边
++i：处理完一条水平边后，i自增
j <= nq：确保j没有超出垂直边的数量
q[j].x < p[i].x：当前垂直边的x坐标小于当前水平边的x坐标
q[j].x == p[i].x && q[j].r：x坐标相同，且q[j].r非0（开始事件）
这个条件确保在处理水平边前，先处理所有相关的垂直边事件
a = q[j].l：a存储当前垂直边的y坐标
b = q[j].r：b存储当前垂直边的r值（0表示结束事件，非0表示开始事件）
if (b)：如果b非0，表示这是一个开始事件
org[a] = j：将y坐标a映射到垂直边j的编号
sum[j] = b：设置边j的贡献值为b
st.insert(a)：将y坐标a插入活跃区间集合
update(1, m, 1, a, 1)：在线段树的第a个位置加1
这表示在y=a处有一个区间端点被激活
c = pre(a)：找到a位置前一个被标记的y坐标
if (c != -1) st.insert(c)：如果存在前一个端点，也插入集合
这是为了维护区间连续性
else：处理结束事件（b=0）
auto it = st.find(a)：在集合中查找y坐标a
it != st.end()：如果找到了
st.erase(it)：从集合中删除该端点
c = pre(a)：找到a的前一个活跃端点
if (c != -1) st.insert(c)：将前一个端点重新插入集合
update(1, m, 1, a, -1)：在线段树的第a个位置减1（取消激活）
j++：处理完当前垂直边后，j自增，指向下一个垂直边

re[p[i].r]-re[p[i].l]+1：当前水平边的长度（在离散化坐标系中）
count(1, m, 1, p[i].l, p[i].r)：查询[p[i].l, p[i].r]区间内活跃的垂直边数量
tmp：当前水平边实际能够覆盖的y区间长度（排除被垂直边分割的部分）
a = p[i].l - 1：设置起始位置
c = nxt(a)：找到a之后的下一个活跃y坐标
if (c <= p[i].r)：如果找到的坐标在当前水平边范围内
org[c]：找到y坐标c对应的垂直边编号
find(org[c])：找到该垂直边所在并查集的根
sum[find(org[c])] += tmp：将当前水平边的贡献加到根节点
while (1)：无限循环，直到break
st.lower_bound(p[i].l)：找到第一个>=p[i].l的y坐标
if (it == st.end() || (*it) > p[i].r) break：如果找不到或超出范围则退出
a = *it：获取找到的y坐标
c = nxt(a)：找到a之后的下一个活跃y坐标
if (c == -1 || c > p[i].r) break：如果没有下一个或超出范围则退出
st.erase(it)：从集合中删除当前y坐标
b = find(org[a])：找到a对应的垂直边的并查集根
d = find(org[c])：找到c对应的垂直边的并查集根
if (b != d)：如果不在同一个集合中
sum[d] += sum[b], fa[b] = d：合并两个集合（并查集合并操作）

if (b == d)：如果y坐标相同，这是一个水平线段
++nq：先将nq自增1，然后使用新值
q[++nq].x = a：设置线段的x坐标为a（左端点）
q[nq].l = b：设置线段的y坐标为b
q[nq].r = c - a + 1：记录线段长度，这是开始事件的标记
c - a + 1：线段从a到c，长度为c-a+1
q[++nq].x = c：添加结束事件，x坐标为c（右端点）
q[nq].l = b：y坐标仍为b
q[nq].r = 0：r=0表示这是一个结束事件
这样用两个事件（开始和结束）来表示一个水平线段
re[++m] = b：将y坐标b添加到坐标数组re中，用于后续离散化
else：如果y坐标不同，这是一个矩形
++np：先将np自增1，然后使用新值
p[++np].x = a：垂直边的x坐标为a
p[np].l = b：垂直边的下端点y坐标为b
p[np].r = d：垂直边的上端点y坐标为d
re[++m] = b：将y坐标b加入离散化数组
re[++m] = d：将y坐标d加入离散化数组

if (re[i] != re[j])：如果当前坐标与前一个不同（去重）
re[++j] = re[i]：将不同的坐标保存到re[++j]
m = j：更新m为离散化后坐标的数量

for (i = 1; i <= nq; ++i)：遍历所有垂直边事件
lower_bound(re+1, re+m+1, q[i].l)：在re数组中二分查找q[i].l
lower_bound(re+1, re+m+1, q[i].l)-re：返回找到位置的地址偏移
q[i].l = ...：将原始y坐标替换为离散化后的编号
fa[i] = i：初始化并查集，每个节点的父节点是自己
for (i = 1; i <= np; ++i)：遍历所有水平边
p[i].l = lower_bound(...)：将原始下端点y坐标离散化
p[i].r = lower_bound(...)：将原始上端点y坐标离散化



时间复杂度：O(n log n)，空间复杂度：O(n)
 */
#include <algorithm>
#include <iostream>
#include <set>
#define ll long long
#define N 200010
using namespace std;

struct Edge { int l, r, x; } p[N], q[N<<1];

int fa[N<<1];
int find(const int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

ll s[N<<3];
//区间[l,r]，当前节点x，更新位置a，更新值b
void update(const int l, const int r, const int x, const int a, const int b) {
    s[x] += b;//当前节点加上更新值
    if (l == r) return;
    if (const int mid = (l + r) >> 1; a <= mid) update(l, mid, x<<1, a, b);
    else update(mid+1, r, x<<1|1, a, b);
}

//区间[a,b]的和
int count(const int l, const int r, const int x, const int a, const int b) {
    if (a > b) return 0;//区间无效
    if (a <= l && r <= b) return s[x];
    const int mid = (l + r) >> 1;
    if (b <= mid) return count(l, mid, x<<1, a, b);
    if (a > mid) return count(mid+1, r, x<<1|1, a, b);
    return count(l, mid, x<<1, a, b) + count(mid+1, r, x<<1|1, a, b);
}

//找到第a个被标记的位置
int find(const int l, const int r, const int x, const int a) {
    if (l == r) return l;
    const int mid = (l + r) >> 1;
    if (a <= s[x<<1]) return find(l, mid, x<<1, a);//第a个位置在左子树
    return find(mid+1, r, x<<1|1, a - s[x<<1]);//在右子树中找第(a - 左子树数量)个位置
}

int m;
inline int pre(const int x) {//找到x的前一个被标记的位置
    const int t = count(1, m, 1, 1, x);//[1,x]区间内的标记数量
    if (t == 1) return -1;//只有1个标记，返回-1（没有前驱）
    return find(1, m, 1, t-1);//找第(t-1)个标记的位置
}

inline int nxt(const int x) {//找到x的后一个被标记的位置
    const int t = count(1, m, 1, 1, x);
    if (t == s[1]) return -1;//标记数量等于总数，返回-1（没有后继）
    return find(1, m, 1, t+1);
}

inline int rd() {
    int ret = 0, f = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') f = -f; c = getchar(); }
    while (c >= '0' && c <= '9') ret = ret*10 + (c^'0'), c = getchar();
    return ret*f;
}

bool cmp(const Edge& a, const Edge& b) {
    return a.x == b.x ? a.r > b.r : a.x < b.x;
}

int n, nq, np, org[N<<1];
ll re[N<<1], ans, sum[N<<1];
set<int> st;
int main() {
    n = rd();//n个矩形
    int i, j, a, b, c, d;//矩形的坐标 (a,b) 和 (c,d)
    for (i = 1; i <= n; ++i) {
        a = rd(), b = rd(), c = rd(), d = rd();
        if (b == d) {//水平边（矩形的上边和下边）
            q[++nq].x = a, q[nq].l = b, q[nq].r = c - a + 1;//开始事件 记录线段长度
            q[++nq].x = c, q[nq].l = b, q[nq].r = 0;//结束事件
            re[++m] = b;
        } else {//垂直边
            p[++np].x = a, p[np].l = b, p[np].r = d;
            re[++m] = b, re[++m] = d;
            ans = max(ans, 1ll*(d-b));
        }
    }
    sort(re + 1, re + m + 1);
    for (i = 1, j = 0, re[0] = -1<<30; i <= m; ++i)
        if (re[i] != re[j]) re[++j] = re[i];//坐标离散化
    m = j;
    //将原始坐标映射到离散化后的坐标
    for (i = 1; i <= nq; ++i) q[i].l = lower_bound(re+1, re+m+1, q[i].l)-re, fa[i] = i;
    for (i = 1; i <= np; ++i) p[i].l = lower_bound(re+1, re+m+1, p[i].l)-re,
        p[i].r = lower_bound(re+1, re+m+1, p[i].r)-re;
    sort(p+1, p+np+1, cmp);
    sort(q+1, q+nq+1, cmp);
    for (i=j=1; i <= np; ++i) {
        while (j <= nq && (q[j].x < p[i].x || (q[j].x == p[i].x && q[j].r))) {
            a = q[j].l, b = q[j].r;
            if (b) {//开始事件（边开始）
                //位置a对应的边编号 设置边的贡献 在集合中添加端点
                org[a] = j, sum[j] = b; st.insert(a);
                update(1, m, 1, a, 1);//线段树中该位置+1
                c = pre(a);
                if (c != -1) st.insert(c);
            } else {
                if (auto it = st.find(a); it != st.end()) st.erase(it);//从集合中删除端点
                c = pre(a);
                if (c != -1) st.insert(c);
                update(1, m, 1, a, -1);//线段树中该位置-1
            }
            j++;
        }
        const ll tmp = re[p[i].r]-re[p[i].l]+1-count(1, m, 1, p[i].l, p[i].r);
        a = p[i].l - 1, c = nxt(a);
        if (c <= p[i].r) {
            sum[find(org[c])] += tmp;
            while (1) {
                auto it = st.lower_bound(p[i].l);
                if (it == st.end() || (*it) > p[i].r) break;
                a = *it, c = nxt(a);
                if (c == -1 || c > p[i].r) break;
                st.erase(it);
                b = find(org[a]), d= find(org[c]);
                if (b != d) sum[d] += sum[b], fa[b] = d;
            }
        }
    }
    for (i = 1; i <= nq; ++i) ans = max(ans, sum[i]-1);
    printf("%lld", ans);
    return 0;
}