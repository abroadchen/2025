//
// Created by Psy.C on 2026/2/11.
//

#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100001
#define get(i,j) ((-c[i]+1.*a[i]*i+c[j]-1.*a[j]*j)/(a[i]-a[j]))//两条直线交点的x坐标
using namespace std;

struct node {
    int x, y, id;
    bool operator<(const node o) const {
        return y < o.y;
    }
} q[N];

int top, st[N];//单调栈，存储数组下标
int find(const int u) {
    int l = 1, r = top, ans = 0;
    while (l <= r) {//第一个大于u的位置
        if (const int mid = (l + r) >> 1; st[mid] > u) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    return ans;
}
//c[N]：a数组的前缀和
int n, a[N], c[N], m, ans[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], c[i] = c[i-1] + a[i];
    cin >> m;
    for (int i = 1; i <= m; ++i) cin >> q[i].x >> q[i].y, q[i].id = i;
    sort(q + 1, q + m + 1);
    for (int i = 1, j = 1; i <= n; ++i) {
        //弹出所有大于等于当前a[i]的元素（维护单调性）
        while (top > 0 && a[st[top]] >= a[i]) top--;
        //弹出不构成凸包的点（斜率优化）
        while (top > 1 && get(st[top], i) <= get(st[top-1], i)) top--;
        st[++top] = i;//将当前下标加入栈顶
        //已按y值排序，所以y=i的查询会连续出现
        while (j <= m && q[j].y == i) {
            //有效决策点的左边界 右边界是栈顶-1（因为要比较相邻两个元素）
            int l = find(i - q[j].x), r = top - 1, now = i;//初始化最优决策点为当前位置i
            while (l <= r) {
                if (const int mid = (l + r) >> 1; get(st[mid], st[mid+1]) >= i - q[j].x)
                    now = st[mid], r = mid - 1;
                else l = mid + 1;
            }
            ans[q[j].id] = c[i] - c[now] + a[now]*(q[j].x-i+now);
            j++;
        }
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
    return 0;
}