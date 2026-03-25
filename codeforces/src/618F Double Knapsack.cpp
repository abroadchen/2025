//
// Created by Psy.C on 2026/3/25.
//
/**
N：数组大小常量
vis：访问标记数组
n：输入数据长度
p：记录位置数组
d, d1, d2：差值变量
l1, r1, l2, r2：左右边界变量

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}


#define int long long
constexpr int N = 1e6+5;
int vis[N], n, p[N], d, d1, d2, l1, r1, l2, r2;
void get(const int a[], const int b[]) {
    memset(vis, -1, sizeof vis);
    for (int i = 0, j = 0; i <= n; ++i) {//遍历数组a
        while (a[i] - b[j] >= n) j++;//调整j的位置，使差值小于n
        p[i] = j, d = a[i] - b[j];//记录j的位置和当前差值
        if (vis[d] == -1) vis[d] = i;//如果这个差值第一次出现，记录位置
        else {//如果差值重复出现
            d1 = i - vis[d], d2 = j - p[vis[d]];//计算两个区间长度
            l1 = vis[d] + 1, r1 = i;//设置第一个区间的边界
            l2 = p[vis[d]] + 1, r2 = j;//设置第二个区间的边界
        }
    }
}

int a[N], b[N];///前缀和数组
signed main() {
    fast;
    n = rd();
    for (int i = 1; i <= n; ++i) a[i] = rd() + a[i-1];
    for (int i = 1; i <= n; ++i) b[i] = rd() + b[i-1];
    if (a[n] <= b[n]) get(a, b);//根据总和大小决定调用顺序
    else get(b, a), swap(d1, d2), swap(l1, l2), swap(r1, r2);
    cout << d1 << '\n';
    for (int i = l1; i <= r1; ++i) cout << i << ' ';//输出第一个区间索引
    cout << '\n';
    cout << d2 << '\n';
    for (int i = l2; i <= r2; ++i) cout << i << ' ';
    return 0;
}