//
// Created by Psy.C on 2025/12/2.
//
/*
*n: 元素个数
x: 去重后的元素个数
tr[N]: 树状数组(Fenwick Tree)
m: 目标值
sum[N]: 前缀和数组
num[N]: 排序用的数组
 *lb函数，返回t的最低位1所代表的值
 *read函数，用于查询树状数组前t项的和
 *
*a: num数组中小于等于t的元素个数
b: sum[i]在num数组中的位置
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+100;
constexpr ll inf = 1e18;
int n, x, tr[N];
ll m, sum[N], num[N];

int lb(const int t) { return t&(-t); }
int read(int t) {
    int s = 0;
    while (t > 0) { s += tr[t]; t -= lb(t); }//不断向前累加，直到t变为0
    return s;
}
void add(int pos, const int val) {//在位置pos处增加val
    while (pos <= n) {//不断向上更新树状数组
        tr[pos] += val;
        pos += lb(pos);
    }
}

ll f(const ll mid) {
    memset(tr, 0, sizeof(tr)); ll ans = 0;//清空树状数组，初始化答案为0
    for (int i = 1; i <= n; ++i) {//遍历所有位置
        if (sum[i] >= mid) ans++;//如果当前前缀和大于等于mid，答案加1
        ll t = sum[i] - mid;//计算目标值t
        const int a = static_cast<int>(upper_bound(num + 1, num + n + 1, t) - num - 1),
        b = static_cast<int>(lower_bound(num + 1, num + n + 1, sum[i]) - num);
        ans += read(a); add(b, 1);//累加小于等于a的元素个数，然后在位置b处加1
        //当前的sum[i]加入到计数器中(add(b, 1))，供后续使用
    }
    return ans;
}

int main() {
    fast;
    while (cin >> n >> m) {
        sum[0] = 0; ll l, r;
        for (int i = 1; i <= n; ++i) {
            cin >> sum[i];
            sum[i] += sum[i-1];
            num[i] = sum[i];//同时复制到num数组
        }
        sort(num + 1, num + n + 1);
        x = static_cast<int>(unique(num + 1, num + n + 1) - num - 1);//去除num数组中的重复元素
        ll ans = -1; l = -inf, r = inf;
        while (l <= r) {
            const ll mid = l + (r - l + 1) / 2;
            if (f(mid) >= m) { ans = mid; l = mid + 1; }
            else r = mid - 1;
        }
        cout << ans << '\n';
    }
    return 0;
}