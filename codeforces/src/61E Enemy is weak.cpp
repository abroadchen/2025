//
// Created by Psy.C on 2025/10/28.
//
/*
*n: 元素个数
a[N]: 原始数组
t[N]: 临时数组用于排序
seg[4*N]: 线段树数组
tar: 目标位置（用于更新线段树）
s, e: 查询区间起点和终点
mx[N], mn[N]: 存储每个位置左侧较大元素和右侧较小元素的个数
mp: 映射容器用于离散化
res: 结果变量，初始化为0
 *
 *定义线段树更新函数，参数为当前节点rt，区间[l,r]
 *如果目标位置不在当前区间范围内，直接返回
 *如果是叶子节点，将该位置标记为1（表示存在）
*递归更新左右子树
rt<<1表示左子节点，rt<<1|1表示右子节点
 *更新当前节点的值为左右子节点值的和
 *
 *定义线段树查询函数，在区间[l,r]中查询[s,e]范围内的元素个数
 *如果查询区间与当前区间无交集，返回0
 *如果当前区间完全包含在查询区间内，返回当前节点的值
 *递归查询左右子树并返回结果之和
 *
*离散化处理：为排序后的唯一元素分配连续的编号
cnt从1开始，为每个不同的值分配一个递增的编号
 *
*初始化线段树为0
将第一个元素加入线段树
*查询在当前元素右侧（值更大）的已处理元素个数
设置查询区间为[a[i]+1, 1e6]，并将结果存储在mx[i]
 *将当前元素加入线段树，为后续查询做准备
 *
*重新初始化线段树
将最后一个元素加入线段树
 *从倒数第二个元素到第二个元素进行处理（从右到左）
*查询在当前元素左侧（值更小）的已处理元素个数
设置查询区间为[1, a[i]-1]，并将结果存储在mn[i]
 *
 */
#include <cstdio>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;

typedef long long ll;
const int N = 1e6+1;
int n, a[N], t[N], seg[4*N], tar, s, e, mx[N], mn[N];
map<int,int> mp;
ll res(0);


void update(int rt, int l, int r) {
    if (tar < l || tar > r) return;
    if (l == r) { seg[rt] = 1; return; }
    int mid = (l + r) >> 1;
    update(rt<<1, l, mid);
    update(rt<<1|1, mid+1, r);
    seg[rt] = seg[rt<<1] + seg[rt<<1|1];
}

int get(int rt, int l, int r) {
    if (e < l || s > r) return 0;
    if (l >= s && r <= e) return seg[rt];
    int mid = (l + r) >> 1;
    return get(rt<<1, l, mid) + get(rt<<1|1, mid+1, r);
}

int main() {
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        t[i] = a[i];
    }
    sort(t + 1, t + n + 1);
    for (int i = 1, cnt = 1; i <= n; ++i) {
        if (!mp.count(t[i])) mp[t[i]] = cnt++;
    }
    for (int i = 1; i <= n; ++i) a[i] = mp[a[i]];//将原数组中的值替换为对应的离散化编号
    memset(seg, 0, sizeof(seg));
    tar = a[1];
    update(1, 1, n);

    for (int i = 2; i < n; ++i) {
        s = a[i] + 1, e = 1e6;
        mx[i] = get(1, 1, n);
        tar = a[i];//将当前元素加入线段树，为后续查询做准备
        update(1, 1, n);
    }

    memset(seg, 0, sizeof(seg));
    tar = a[n];
    update(1, 1, n);
    for (int i = n - 1; i > 1; --i) {
        s = 1, e = a[i] - 1;
        mn[i] = get(1, 1, n);
        tar = a[i];
        update(1, 1, n);
    }

    for (int i = 1; i <= n; ++i) res += 1ll*mx[i]*mn[i];
    printf("%lld\n", res);
    return 0;
}