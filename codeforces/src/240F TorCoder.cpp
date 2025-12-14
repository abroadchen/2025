//
// Created by Psy.C on 2025/12/13.
//
/*
*定义线段树结构体，包含26棵线段树（对应26个小写字母）
sum[N<<2]: 存储区间和（线段树节点值）
tag[N<<2]: 懒标记数组
a[N]: 原始数组
宏定义：
mid: 区间中点，等价于(l+r)/2
ls: 左子节点索引，等价于rt*2
rs: 右子节点索引，等价于rt*2+1
 *
 *向上传递函数：父节点的值等于左右子节点值之和
*构建线段树函数：
初始化当前节点的懒标记为-1（表示无标记）
如果是叶子节点（l==r），直接赋值为原始数组对应元素
否则递归构建左右子树，然后向上更新
*下传懒标记函数：
如果当前节点有懒标记（不等于-1）
将标记传递给左右子节点
更新子节点的值：节点值 = 区间长度 × 标记值
清空当前节点的懒标记
*区间查询函数：查询区间[L,R]的和
如果当前区间完全包含在查询区间内，直接返回当前节点值
否则先下传懒标记
分别查询左右子区间并累加结果
*区间更新函数：将区间[L,R]的值都更新为v
如果当前区间完全包含在更新区间内，设置懒标记并更新节点值
否则先下传懒标记
递归更新左右子区间
向上传递更新结果
 *
*对于位置i的字符，将其对应字母的线段树在位置i设为1
例如：如果s[i]='c'，则t[2].a[i]=1（因为'c'-'a'=2）
*偶数长度回文串：所有字符都必须出现偶数次（cnt=0）
奇数长度回文串：最多只能有一个字符出现奇数次（cnt≤1）
 *
*重构回文串：
首先将区间[l,r]内所有字符清零
对于每个出现的字母：
在区间左半部分放置该字母出现次数的一半
在区间右半部分放置该字母出现次数的一半
如果出现奇数次，中间位置放置一个该字母
 *
*遍历每个位置p
查找在该位置哪个字母存在（值为1）
输出对应的字符
找到后跳出内层循环
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
using namespace std;

struct sgt {
    int sum[N<<2], tag[N<<2], a[N];
#define mid ((l+r)>>1)
#define ls rt<<1
#define rs (ls|1)
    void up(const int rt) { sum[rt] = sum[ls] + sum[rs]; }
    void build(const int rt, const int l, const int r) {
        tag[rt] = -1;
        if (l == r) { sum[rt] = a[l]; return; }
        build(ls, l, mid); build(rs, mid+1, r);
        up(rt);
    }
    void down(const int rt, const int l, const int r) {
        if (tag[rt] != -1) {
            tag[ls] = tag[rs] = tag[rt];
            sum[ls] = (mid - l + 1) * tag[ls], sum[rs] = (r - mid) * tag[rs];
            tag[rt] = -1;
        }
    }
    int query(const int rt, const int l, const int r, const int L, const int R) {
        if (L <= l && r <= R) return sum[rt];
        down(rt, l, r);
        int ret = 0;
        if (L <= mid) ret += query(ls, l, mid, L, R);
        if (R > mid) ret += query(rs, mid+1, r, L, R);
        return ret;
    }
    void update(const int rt, const int l, const int r, const int L, const int R, const int v) {
        if (L <= l && r <= R) {
            tag[rt] = v, sum[rt] = (r - l + 1) * v; return;
        }
        down(rt, l, r);
        if (L <= mid) update(ls, l, mid, L, R, v);
        if (R > mid) update(rs, mid+1, r, L, R, v);
        up(rt);
    }
} t[26];


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    int n, m, tot[26]; cin >> n >> m;
    string str; cin >> str; const int len = static_cast<int>(str.size());
    char s[N];
    for (int i = 0; i < len; i++) s[i + 1] = str[i];
    for (int i = 1; i <= n; ++i) t[s[i] - 'a'].a[i] = 1;
    for (int i = 0; i <= 25; ++i) t[i].build(1, 1, n);
    while (m--) {
        int l, r, cnt = 0; cin >> l >> r;
        for (int i = 0; i <= 25; ++i) {
            tot[i] = t[i].query(1, 1, n, l, r);
            if (tot[i] & 1) cnt++;
        }
        if ((r - l + 1) % 2 == 0 && cnt) continue;
        if ((r - l + 1) % 2 == 1 && cnt > 1) continue;
        for (int i = 0; i <= 25; ++i) t[i].update(1, 1, n, l, r, 0);
        for (int i = 0; i <= 25; ++i) if (tot[i]) {
            t[i].update(1, 1, n, l, l + tot[i] / 2 - 1, 1);
            t[i].update(1, 1, n, r - tot[i] / 2 + 1, r, 1);
            l += tot[i] / 2, r -= tot[i] / 2;
            if (tot[i] & 1) t[i].update(1, 1, n, mid, mid, 1);
        }
    }
    for (int p = 1; p <= n; ++p) for (int i = 0; i <= 25; ++i) if (t[i].query(1,1,n,p,p)) {
        cout << static_cast<char>('a' + i); break;
    }
    return 0;
}