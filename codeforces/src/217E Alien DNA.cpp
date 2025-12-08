//
// Created by Psy.C on 2025/12/7.
//
/*
*N和M: 大小常量，用于数组大小
s[M]: 字符数组，存储输入字符串
n: 字符串长度
m: 操作次数
c[N]: 树状数组(Fenwick Tree)，用于高效计算前缀和
f[M]: 结果映射数组
a[N]: 结构体数组，存储操作区间信息
*p[]: 预计算2的幂次方值
lim: 计算log₂(n)的上限，用于二分查找
 *
*cur从n开始递减
对每个操作区间逆序处理
通过复杂的索引计算重新排列字符位置
使用树状数组维护可用位置
将结果记录在f数组中
 *
*初始化：
x = a[i].l + 1：起始位置为当前操作区间的左端点+1
j = 1：计数器，表示这是第几个被处理的元素
循环条件（两个必须同时满足）：
a[i].r < cur：当前操作区间的右端点小于当前处理位置
j <= a[i].r - a[i].l + 1：已处理元素数量不超过操作区间长度
每次循环后的更新：
x += 2：x增加2（跳跃式移动）
++j：计数器加1
--cur：当前处理位置前移
 *如果x超出了当前操作区间的右端点，则将x重置为区间的左端点，实现循环访问区间内的位置
 *使用树状数组查询当前第(a[i].r + 1)小的元素位置，即找到在排序后位于区间末尾的那个元素的实际位置
 *在树状数组中将该位置标记为已使用（减少1），表示这个位置的字符已经被处理过
 *将位置pos映射到新的位置query(x)，即记录字符应该移动到的新位置
 */
#include <iostream>
#include <cmath>
#include <cstring>
#define ll long long
using namespace std;

constexpr int N = 3e6+5, M = 3e6+11;
char s[M];
int n, m, c[N], f[M];
struct node { int l, r; } a[N];

int lb(const int i) { return i & (-i); }
void add(int x, const ll val) {//在位置x处增加val值，并更新所有相关的父节点
    while (x <= n) { c[x] += static_cast<int>(val); x += lb(x); }
}

ll p[100];
int lim;
void init() {
    p[0] = 1;
    for (int i = 1; i < 30; ++i) p[i] = p[i-1] << 1;
    lim = static_cast<int>(log(n) / log(2) + 1);
}
int query(const int x) {//查询第x小元素的位置
    int ans = 0, sum = 0;
    for (int j = lim; j >= 0; --j) {
        if (ans + p[j] <= n && sum + c[ans+p[j]] < x) {
            sum += c[ans+p[j]];
            ans += static_cast<int>(p[j]);
        }
    }
    return ans + 1;
}

char ans[M];
int main() {
    scanf("%s",s + 1); scanf("%d%d",&n,&m);
    memset(c,0,sizeof(c));
    for (int i = 1; i <= n; ++i) add(i, 1);//在树状数组每个位置添加1，表示初始时所有位置都可用
    for (int i = 1; i <= m; ++i) cin >> a[i].l >> a[i].r;
    init();
    for (int cur = n, i = m; i >= 1; --i) {
        for (int x = a[i].l + 1, j = 1; a[i].r < cur &&
            j <= a[i].r - a[i].l + 1; x += 2, ++j, --cur) {
            if (x > a[i].r) x = a[i].l;
            const int pos = query(a[i].r + 1);
            add(pos, -1);
            f[pos] = query(x);
        }
    }
    for (int i = 1, j = 0; i <= n; ++i) {
        if (f[i] != 0) ans[i] = ans[f[i]];
        else ans[i] = s[++j];//从原字符串s中依次取字符
    }
    printf("%s",ans + 1);
    return 0;
}
