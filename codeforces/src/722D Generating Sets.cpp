//
// Created by Psy.C on 2026/4/23.
//
/**
v：临时存储结果的向量
ut：哈希集合，用于去重
n：数组长度
a[N]：输入数组

v.clear(); ut.clear();：清空临时容器
遍历数组a中的每个元素：
x = a[i]：当前处理的数
while (x >= 1)：不断变换x直到变成0
if (x <= up && !ut.contains(x))：如果x不超过上限且未被使用
将x加入集合和向量
break;：找到合适的值后跳出循环
if (x&1) x = (x-1)/2; else x >>= 1;：变换规则
如果x是奇数：x = (x-1)/2
如果x是偶数：x >>= 1（即x = x/2）
返回是否成功分配了n个数

将数组a按降序排序（从大到小)
二分搜索最小的上限值
l = 1, r = mx：搜索范围[1, mx]
mid = (l + r) >> 1：计算中点
if (ok(mid))：如果mid可行
r = mid - 1：尝试更小的值
ans = v：保存结果
else l = mid + 1：如果不可行，增大下界
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e4+7;

vector<int> v;
unordered_set<int> ut;
int n, a[N];
bool ok(int up) {
    v.clear(); ut.clear();
    for (int x, i = 1; i <= n; ++i) {
        x = a[i];
        while (x >= 1) {
            if (x <= up && !ut.contains(x)) {
                ut.insert(x);
                v.push_back(x);
                break;
            }
            if (x&1) x = (x-1)/2; else x >>= 1;
        }
    }
    return v.size() == n;
}

int mx;
vector<int> ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], mx = max(mx, a[i]);
    sort(a + 1, a + n + 1); reverse(a + 1, a + n + 1);
    int l = 1, r = mx, mid;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (ok(mid)) r = mid - 1, ans = v; else l = mid + 1;
    }
    for (auto x : ans) cout << x << ' ';
    return 0;
}