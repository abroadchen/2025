//
// Created by Psy.C on 2026/4/18.
//
/**
N = 1e5+5: 数组大小上限（约100005）
M1 = 316: 分块大小上限（约√N）
M2 = 1400: 辅助数组大小上限
ct[N]: 记录每个数值出现的次数
ct2[N]: 记录出现次数的分布（ct2[i]表示出现i次的数字有多少个）
ins(int v): 插入元素v的操作
ct2[ct[v]]--: 出现ct[v]次的数字减少1个
ct[v]++: v的出现次数增加
ct2[ct[v]]++: 出现ct[v]次的数字增加1个
del(int v): 删除元素v的操作（相反过程）

ve: 存储出现频次超过bv的数值
bv: 分界值，区分高频和低频元素
tmp[M2+5]: 临时数组，用于处理低频元素
创建小根堆，存储高频元素的出现次数
将所有出现次数大于bv的元素加入堆中
复制出现次数为1到bv的元素个数到tmp数组
遍历所有低频元素的出现次数
pre: 存储奇数个出现次数的值
对于每个出现次数i：
如果有pre值，将其与i合并
计算成对元素的贡献
处理剩余的奇数个元素
将剩余的pre值加入堆
不断取出两个最小值相加，直到只剩一个值
返回总的合并代价

bel[N]: 记录每个位置属于哪个块
node: 查询结构体，包含左右端点和查询编号
重载比较运算符：按块号排序，同一块内按右端点排序
n: 数组长度
a[N]: 输入数组
blk: 块大小
blt_cnt: 块的数量
L[], R[]: 每个块的左边界和右边界
qu: 查询数量
ret[N]: 存储答案

输入数组大小n
输入数组元素并统计每个值的出现次数
blk: 块大小设为√n
bv: 分界值，平衡高频和低频元素处理
blt_cnt: 块的数量
将出现次数超过bv的值加入ve数组
重置ct数组
设置每个块的边界
为每个位置分配所属的块号
输入查询数量
读取所有查询并排序（莫队排序）
莫队算法的指针移动
维护当前区间[cl, cr]
通过插入和删除操作调整到目标区间
计算当前区间的答案



pre = 0: 用于存储当前剩余的单独元素的出现次数，初始为0
ret = 0: 累计合并操作的总代价，初始为0
遍历所有出现次数从1到bv的数值
if (tmp[i]): 只处理出现次数为i的数值确实存在的那些情况
tmp[i]表示有多少个不同的数值恰好出现了i次
如果之前有剩余的单独元素(pre != 0)
将这个单独元素(pre)与当前出现i次的元素之一配对:
ret += pre + i: 合并代价为pre + i，累加到总代价
tmp[i]--: 出现i次的元素数量减1（拿出一个来配对）
if (pre + i <= bv) tmp[pre+i]++; else q.push(pre+i);: 配对后的新元素出现次数为pre+i，如果不超过bv则更新tmp数组，否则放入大根堆
pre = 0: 清除之前的单独元素
处理当前出现次数为i的元素中可以成对的部分
tmp[i]/2: 有tmp[i]/2对可以立即合并的元素
tmp[i]/2*2: 实际参与成对合并的元素个数
1ll*i*(tmp[i]/2*2): 每个元素贡献i的代价，共tmp[i]/2*2个元素
这一步相当于把相同的出现次数i的元素尽可能成对合并
如果合并后的新出现次数i+i仍然不超过bv
tmp[i+i] += tmp[i]/2: 将合并产生的新元素记录到对应位置
例如：两个出现3次的元素合并后变成一个出现6次的元素
如果合并后的新出现次数i+i超过了bv
将这些合并产生的新元素放入优先队列中处理
每次合并产生一个出现i+i次的元素
tmp[i]&1: 检查tmp[i]是否为奇数（位运算判断奇偶）
如果出现次数为i的元素个数是奇数，就会剩下一个无法配对的元素
pre = i: 将这个单独元素的出现次数保存到pre中，等待后续配对


cl: 当前处理区间的左端点，初始化为1
cr: 当前处理区间的右端点，初始化为0
初始状态是空区间[1, 0]，表示没有包含任何元素
遍历所有按莫队顺序排序的查询
扩展右边界
当当前右边界cr小于目标查询的右边界q[i].r时
++cr: 先将cr自增1，扩展右边界
ins(a[++cr]): 将新加入的元素a[cr]插入到当前数据结构中
通过不断扩展直到cr == q[i].r
扩展左边界（向左扩展）
当当前左边界cl大于目标查询的左边界q[i].l时
--cl: 先将cl自减1，扩展左边界（向左）
ins(a[--cl]): 将新加入的元素a[cl]插入到当前数据结构中
通过不断扩展直到cl == q[i].l
收缩左边界
当当前左边界cl小于目标查询的左边界q[i].l时
del(a[cl++]): 先删除a[cl]元素，然后将cl自增1
通过不断收缩直到cl == q[i].l
收缩右边界
当当前右边界cr大于目标查询的右边界q[i].r时
del(a[cr--]): 先删除a[cr]元素，然后将cr自减1
通过不断收缩直到cr == q[i].r
此时[cl, cr]正好对应目标查询区间[q[i].l, q[i].r]
调用get()函数计算当前区间的结果
将结果保存到对应查询编号的位置
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5, M1 = 316, M2 = 1400;

int ct[N], ct2[N];
void ins(int v) { ct2[ct[v]]--; ct[v]++; ct2[ct[v]]++; }
void del(int v) { ct2[ct[v]]--; ct[v]--; ct2[ct[v]]++; }

vector<int> ve;
int bv, tmp[M2+5];
ll get() {
    priority_queue<int, vector<int>, greater<>> q;
    for (int i : ve) if (ct[i] > bv) q.push(ct[i]);
    for (int i = 1; i <= bv; ++i) tmp[i] = ct2[i];
    int pre = 0; ll ret = 0;
    for (int i = 1; i <= bv; ++i) if (tmp[i]) {
        if (pre) {
            ret += pre + i; tmp[i]--;
            if (pre + i <= bv) tmp[pre+i]++; else q.push(pre+i);
            pre = 0;
        }
        ret += 1ll*i*(tmp[i]/2*2);
        if (i + i <= bv) tmp[i+i] += tmp[i]/2;
        else {
            for (int j = 1; j <= tmp[i]/2; ++j)
                q.push(i+i);
        }
        if (tmp[i]&1) pre = i;
    }
    if (pre) q.push(pre);
    while (q.size() > 1) {
        int x = q.top(); q.pop(); x += q.top(); q.pop();
        ret += x; q.push(x);
    }
    return ret;
}

int bel[N];
struct node {
    int l, r, id;
    bool operator<(const node &o) const {
        if (bel[l] != bel[o.l]) return bel[l] < bel[o.l];
        return r < o.r;
    }
} q[N];

int n, a[N], blk, blt_cnt, L[M1+2], R[M1+2], qu;
ll ret[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], ct[a[i]]++;
    blk = (int)pow(n, 0.5); bv = (int)sqrt(n*log(n)/log(2));
    blt_cnt = (n-1)/blk + 1;
    for (int i = 1; i <= N-5; ++i) if (ct[i] > bv) ve.push_back(i);
    memset(ct, 0, sizeof(ct));
    for (int i = 1; i <= blt_cnt; ++i) {
        L[i] = (i-1)*blk + 1; R[i] = min(i*blk, n);
        for (int j = L[i]; j <= R[i]; ++j) bel[j] = i;
    }
    cin >> qu;
    for (int i = 1; i <= qu; ++i)
        cin >> q[i].l >> q[i].r, q[i].id = i;
    sort(q + 1, q + qu + 1);
    int cl = 1, cr = 0;
    for (int i = 1; i <= qu; ++i) {
        while (cr < q[i].r) ins(a[++cr]);
        while (cl > q[i].l) ins(a[--cl]);
        while (cl < q[i].l) del(a[cl++]);
        while (cr > q[i].r) del(a[cr--]);
        ret[q[i].id] = get();
    }
    for (int i = 1; i <= qu; ++i) cout << ret[i] << '\n';
    return 0;
}