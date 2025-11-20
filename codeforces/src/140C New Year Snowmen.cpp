//
// Created by Psy.C on 2025/11/20.
//
/*
*a[N]: 存储输入数据的数组
f[N][4]: 二维数组，用于存储分组结果，每组最多3个元素
 *
*函数ok(k)判断是否能将数组分成k组
k: 要分成的组数
j: 当前组的索引（从1开始）
q: 每组中已放置的元素数量（从0开始计数）
前k个元素作为每组的第一个元素
 *
*从第k+1个元素开始处理
如果当前元素a[i]大于当前组最后一个元素f[j][q-1]，则将其放入当前组
移动到下一组(j++)
如果所有组都用完了(j > k)，则回到第一组并增加组内元素计数(q++)
如果每组都有3个元素(q == 3)，说明分配成功，返回1
否则返回0表示无法按k组分配
 *
 *使用二分搜索找到最大的可行组数
 *由于循环条件是 l <= r，结束时必然有 l = r + 1
 */
#include <algorithm>
#include <cstdio>
#define rep(i,n) for(i=1;i<=(n);++i)
using namespace std;

const int N = 1e5+10;
int n, a[N], f[N][4];

int ok(int k) {
    int i, j(1), q(1);
    rep(i,k) f[i][0] = a[i];
    for (i = k + 1; i <= n; ++i) {
        if (a[i] > f[j][q - 1]) { f[j][q] = a[i]; j++; }
        if (j > k) { j = 1; q++; }
        if (q == 3) return 1;
    }
    return 0;
}

int main() {
    scanf("%d",&n); int i;
    rep(i,n) scanf("%d",&a[i]);
    sort(a + 1,a+n+1); int l(1), r(n/3);
    while (l <= r) {
        int mid = (l+r)>>1;
        if (ok(mid)) l = mid + 1;
        else r = mid - 1;
    }
    ok(l - 1); printf("%d\n",l - 1);
    rep(i,l-1) printf("%d %d %d\n",f[i][2], f[i][1], f[i][0]);
    return 0;
}