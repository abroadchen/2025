//
// Created by Psy.C on 2026/4/21.
//
/**
f[i]表示到达第i个位置能达到的最大值
n;        // 原始数据数量
b[N];     // 存储相对位置差值的数组
m;        // 总长度/模数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+7;

int f[N], n, b[N], m;
bool check(int x) {//是否可以用长度x满足条件
    f[1] = 0;//第一个位置能达到的最大值为0
    for (int i = 2; i <= n; ++i) {
        f[i] = f[i-1];//默认情况下，不采取任何操作，继承前一个状态
        //规则1：如果前面的位置能到达b[i]-1及以上的点，可以跳到b[i]+x
        if (f[i-1] >= b[i]-1) f[i] = max(f[i], b[i]+x);
        //规则2：如果前面的位置能到达b[i]-x-1及以上的点，可以跳到b[i]
        if (f[i-1] >= b[i]-x-1) f[i] = max(f[i], b[i]);
        //规则3：如果i>2且前前个位置能到达b[i]-x-1及以上的点，可以跳到b[i-1]+x
        if (i > 2 && f[i-2] >= b[i]-x-1) f[i] = max(f[i], b[i-1]+x);
    }
    if (f[n] >= m-x-1) return 1;//如果第一次尝试成功，返回true
    f[2] = max(b[2], x);//第二次尝试：初始化f[2]为较大值
    for (int i = 3; i <= n; ++i) {//重新计算从第3个位置开始
        f[i] = f[i-1];
        if (f[i-1] >= b[i]-1) f[i] = max(f[i], b[i]+x);
        if (f[i-1] >= b[i]-x-1) f[i] = max(f[i], b[i]);
        if (i > 2 && f[i-2] >= b[i]-x-1) f[i] = max(f[i], b[i-1]+x);
    }
    if (f[n] >= m+b[2]-x-1) return 1;//第二次尝试是否成功
    return 0;
}

int a[N<<1], id = 2;
int main() {
    fast;
    cin >> m >> n;
    if (n == 1) cout << m-1, exit(0);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) a[n+i] = a[i] + m;//将原数组扩展，模拟环形结构（加上m）
    for (int i = 3; i <= n+1; ++i)
        if (a[id] - a[id-1] < a[i] - a[i-1]) id = i;//最大的相邻间隔
    //计算相对位置差值，以id-1作为起点
    for (int i = 1; i <= n; ++i) b[i] = a[i+id-1] - a[id];
    //二分查找最小的可行解
    int l = 0, r = a[id] - a[id-1], ans = 0;//右边界为最大间隔
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid - 1, ans = mid;
        else l = mid + 1;
    }
    cout << ans;
    return 0;
}