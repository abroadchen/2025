//
// Created by Psy.C on 2025/12/5.
//
/*
*定义两个结构体：
tc: 存储序列信息，包括当前计数、总数和序列元素
sc: 存储元素及其来源ID
声明数组：
q[M]: 存储多个序列
as[N], s[N]: 用于归并排序的数组
 *
*归并两个已排序的子数组
使用双指针技术合并两个有序序列
保持稳定性（相等元素按原来顺序排列）
 *将未处理完的左半部分或右半部分复制到结果数组
 *将合并结果复制回原数组
*归并排序的递归实现
分治策略：将数组分成两半，分别排序后再合并
 *
*读取参数：k(序列长度)、a(初始值)、x,y,m(线性同余生成器参数)
l: 累计总元素数
使用线性同余生成器生成序列：p[j] = (x * p[j-1] + y) % m
统计每个序列中的递减对数
更新最大递减对数ans
 *
*如果总元素数不超过阈值，则进行全局排序：
使用多路归并的方式逐步生成和排序元素
st, ed: 标记当前排序区间的起始和结束位置
对每个序列，从上次中断的位置继续生成元素
遇到递减点则暂停该序列的生成
使用归并排序对新生成的元素进行排序
 *输出排序后的所有元素及其来源序列ID（从1开始计数）
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 200010
#define M 5001
using namespace std;

constexpr int inf = 2e5;
struct tc { int cnt, count; ll p[M]; } q[M];
struct sc { int id; ll num; } as[N], s[N];


void merge(const int l, const int mid, const int r) {
    int i = l, j = mid + 1, t = l;
    while (i <= mid && j <= r) {
        if (as[i].num <= as[j].num) {
            s[t].id = as[i].id;
            s[t++].num = as[i++].num;
        } else {
            s[t].id = as[j].id;
            s[t++].num = as[j++].num;
        }
    }
    while (i <= mid) {
        s[t].id = as[i].id;
        s[t++].num = as[i++].num;
    }
    while (j <= r) {
        s[t].id = as[j].id;
        s[t++].num = as[j++].num;
    }
    for (i = l; i < t; ++i) {
        as[i].id = s[i].id;
        as[i].num = s[i].num;
    }
}

void mergesort(const int x, const int y) {
    if (x < y) {
        const int mid = (x + y) >> 1;
        mergesort(x, mid);
        mergesort(mid + 1, y);
        merge(x, mid, y);
    }
}


int main() {
    fast;
    ll n, a, x, y, m;
    cin>>n;
    int k, l = 0, ans = -1, i, j;
    for (i = 0; i < n; ++i) {
        cin >> k >> a >> x >> y >> m; int sum = 0; l += k;
        q[i].cnt = 1; q[i].count = k; q[i].p[1] = a;
        for (j = 2; j <= k; ++j) {
            q[i].p[j] = (x * q[i].p[j-1] + y) % m;
            if (q[i].p[j] < q[i].p[j-1]) sum++;
        }
        ans = max(ans, sum);
    }
    cout << ans << '\n';
    if (l <= inf) {
        int st = 0, ed = 0;
        while (ed < l) {
            for (i = 0; i < n; ++i) {
                for (j = q[i].cnt; j <= q[i].count; ++j) {
                    if (j != q[i].cnt && q[i].p[j] < q[i].p[j-1]) {
                        q[i].cnt = j; break;
                    }
                    as[ed].id = i;
                    as[ed++].num = q[i].p[j];
                }
                if (j > q[i].count) q[i].cnt = j;
            }
            mergesort(st, ed - 1);
            st = ed;
        }
        for (i = 0; i < l; ++i) cout << as[i].num << ' ' << as[i].id + 1 << '\n';
    }
    return 0;
}