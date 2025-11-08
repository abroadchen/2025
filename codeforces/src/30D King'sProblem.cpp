//
// Created by Psy.C on 2025/9/21.
//时间复杂度：O(n log n) 主要由排序决定

#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
typedef double db;
const int N = 100010;

int x[N], y;// x坐标数组和y坐标（所有点在同一水平线上）
int n;
db a[N], b[N];// 辅助数组，存储前缀和后缀的最小路径

db getdis(db x, db y) { return sqrt(x*x + y*y); }

db calc(int l, int r, int k) {// 计算从最右点到区间[l,r]内所有点再回到最右点的最小路径长度
    db d1 = getdis(x[n] - x[l], y);// 从最右点到最左点的距离
    db d2 = getdis(x[n] - x[r], y);// 从最右点到最右点的距离
    // 路径长度 = 区间长度 + min(从右端点绕到左端点+回到关键点, 从左端点绕到右端点+回到关键点)
    if (k >= l && k <= r) return x[r] - x[l] + min(x[r] - x[k] + d1, x[k] - x[l] + d2);
    else return x[r] - x[l] + min(d1, d2);// 如果关键点不在区间内，选择较短的往返路径
}

int main() {
    int K2, K; scanf("%d%d", &n, &K2); K2--;
    for (int i = 0; i < n + 1; ++i) scanf("%d", &x[i]); scanf("%d", &y);

    int sx = x[K2];// 保存关键点的原始x坐标
    sort(x, x + n);
    // 找到排序后关键点的索引
    if (K2 == n) K = n;// 如果关键点是最后一个点
    else {
        for (int i = 0; i < n; ++i) {
            if (x[i] == sx) { K = i; break; }
        }
    }
    for (int i = 1; i <= n; ++i) a[i] = calc(0, i - 1, K);//a[i]表示从最右点访问前i个点的最小路径
    for (int i = 0; i < n; ++i) b[i] = calc(i, n - 1, K);//b[i]表示从最右点访问从第i个点开始的所有点的最小路径

    db ans = 1e9;
    if (K == n) ans = a[n];
    else {//枚举分割点，找到最小的总路径
        for (int i = 0; i < n + 1; ++i) ans = min(ans, a[i] + b[i]);
    }
    printf("%.9f\n", ans);

    return 0;
}