//
// Created by Psy.C on 2026/3/31.
//
/**
对数组 f 执行冒泡排序，按 first 字段升序排列
注意：函数参数 a 没有实际使用，直接操作全局数组 f
目的是将最小值移到前面
n：数组长度
k：维护的最大元素数量
q：查询次数
t[N]：存储每个位置的值
flag[N]：标记某位置是否被选中过

标记选中：flag[x] = 1，cnt++
当总数超过k时：
对前k个元素排序
寻找最小值（f[i].first），如果当前元素值更大，则替换
当总数不超过k时：
直接添加到数组中

查询位置x是否在当前维护的k个最大值中
首先检查 flag[x] 是否被标记过
如果被标记过，检查是否在当前前k个元素中
输出相应结果
单次操作可能达到O(k²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 150005;

ii f[7];
void get(ii *a, int n) {
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (f[i].first > f[j].first) {
                swap(f[i].first, f[j].first);
                swap(f[i].second, f[j].second);
            }
}

int n, k, q, t[N], flag[N];
int main() {
    fast;
    cin >> n >> k >> q;
    for (int i = 1; i <= n; ++i) cin >> t[i];
    int op, x, cnt = 0;
    while (q--) {
        cin >> op >> x;
        if (op == 1) {
            flag[x] = 1; cnt++;
            if (cnt > k) {
                get(f, k);
                for (int i = 1; i <= k; ++i)
                    if (t[x] > f[i].first) {
                        f[i].first = t[x];
                        f[i].second = x;
                        break;
                    }
            } else {
                f[cnt].first = t[x];
                f[cnt].second = x;
            }
        }
        if (op == 2) {
            if (flag[x]) {
                bool tag = false;
                for (int i = 1; i <= k; ++i)
                    if (f[i].second == x) {
                        tag = true;
                        break;
                    }
                if (tag) cout << "YES\n";
                else cout << "NO\n";
            } else cout << "NO\n";
        }
    }
    return 0;
}