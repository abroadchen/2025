//
// Created by Psy.C on 2026/3/3.
//
/**
sz: 栈的大小
st[N]: 单调栈数组
val[N]: 值数组

二分查找第一个满足val[st[i]] >= x的位置
sz: 当前栈大小为0时返回0
使用二分查找在单调栈中查找符合条件的位置
返回满足条件的最大索引

维护单调栈的单调性
弹出栈顶小于等于val[x]的元素
将x压入栈中

n: 输入数据数量
x[N]: 位置数组
d[N]: 距离数组
l[N], r[N]: 左右边界数组

初始化栈，将0压入栈
从左到右遍历，计算每个位置的左边界
维护单调栈，当条件2*d[st[sz]] < x[i] - x[st[sz-1]]成立时弹出栈顶
l[i] = x[st[sz]]: 记录左边界
将当前位置压入栈
重新初始化栈，将n+1压入栈
从右到左遍历，计算每个位置的右边界
类似左边界计算，但方向相反

重置栈大小
初始化结果为整个区间长度
如果l[n+1] != 0，说明有特殊情况，直接输出0
遍历每个关键点
使用二分查找获取索引
检查多个条件并更新最小结果
minn()宏用于更新最小值
更新val数组并维护单调栈

时间复杂度约为O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define minn(a,b) a=min(a,b)
using namespace std;
constexpr int N = 1e5+20;

int sz, st[N];
ll val[N];
int upper(const ll x) {
    if (!sz) return 0;
    int l = 0, r = sz+1;
    while (l < r-1) {
        if (const int mid = (l+r)>>1; val[st[mid]] >= x) l = mid;
        else r = mid;
    }
    return l;
}

void get(const int x) {
    while (sz && val[st[sz]] <= val[x]) --sz;
    st[++sz] = x;
}

int n, x[N], d[N], l[N], r[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i <= n+1; ++i) cin >> x[i];
    for (int i = 1; i <= n; ++i) cin >> d[i];
    st[++sz] = 0;
    for (int i = 1; i <= n+1; ++i) {
        while (sz > 1 && 2*d[st[sz]] < x[i] - x[st[sz-1]]) sz--;
        l[i] = x[st[sz]];
        st[++sz] = i;
    }
    sz = 0; st[++sz] = n+1;
    for (int i = n; i >= 0; --i) {
        while (sz > 1 && 2*d[st[sz]] < x[st[sz-1]] - x[i]) sz--;
        r[i] = x[st[sz]];
        st[++sz] = i;
    }
    sz = 0;
    ll res = x[n+1] - x[0];
    if (l[n+1] != 0) { cout << "0.00000\n"; return 0; }
    for (int i = 1; i <= n; ++i) {
        const int idx = upper(r[i] - 2*d[i]);
        if (r[i] - 2*d[i] < x[i])
            if (idx) minn(res, 1ll*x[i]-x[st[idx]]);
        if (1ll*r[i] - 2*d[i] < 1ll*x[i])
            minn(res, 1ll*x[i] - x[0]);
        if (1ll*l[i] + 2*d[i] > 1ll*x[i])
            minn(res, 1ll*x[n+1] - x[i]);
        val[i] = 2ll*d[i] + l[i];
        if (val[i] > 1ll*x[i]) get(i);
    }
    printf("%.10f\n", res/2.);
    return 0;
}