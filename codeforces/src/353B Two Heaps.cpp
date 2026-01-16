//
// Created by Psy.C on 2026/1/16.
//
/**
* n: 一半的元素数量（总共有2n个元素）
a[N]: 存储输入的数组
num[N]={}: 计数数组，初始化为0，用于统计每个数字出现次数
*vis[N] = {}: 访问标记数组，初始化为0
ans[N] = {}: 结果数组，存储每个位置应分配的组（1或2），初始化为0
n0 = 0: 两个组都分配的数字种类数
n1 = 0: 分配到组1的元素个数
n2 = 0: 分配到组2的元素个数
 *
*遍历所有2n个元素
if (num[a[i]] >= 2): 如果当前数字在整个数组中出现至少2次
if (!vis[a[i]]): 如果这个数字还没被分配过
n0++: 增加双分配数字种类数
ans[i] = 1: 当前位置分配到组1
vis[a[i]] = 1: 标记该数字第一次被访问
else if (vis[a[i]]==1): 如果该数字已分配到组1
ans[i] = 2: 当前位置分配到组2
vis[a[i]] = 2: 标记该数字第二次被访问
else: 如果当前数字只出现1次
if (n1 > n2): 如果组1元素多于组2
ans[i] = 2, n2++: 分配到组2
else: 否则
ans[i] = 1, n1++: 分配到组1
 *
*找到那些出现次数≥2且已分配到两组，但ans[i]仍为0的元素
if (n1 < n): 如果组1还没满
ans[i] = 1, n1++: 分配到组1
else: 否则
ans[i] = 2: 分配到组2
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 205
using namespace std;


int main() {
    fast;
    int n, a[N], num[N]={}; cin >> n;
    for (int i = 1; i <= n<<1; ++i) {
        cin >> a[i];
        num[a[i]]++;//统计数字a[i]的出现次数
    }
    int vis[N] = {}, ans[N] = {}, n0 = 0, n1 = 0, n2 = 0;
    for (int i = 1; i <= n<<1; ++i) {
        if (num[a[i]] >= 2) {
            if (!vis[a[i]]) n0++, ans[i] = 1, vis[a[i]] = 1;
            else if (vis[a[i]]==1) ans[i] = 2, vis[a[i]] = 2;
        } else {
            if (n1 > n2) ans[i] = 2, n2++;
            else ans[i] = 1, n1++;
        }
    }
    n1 += n0, n2 += n0;//将双分配的数字加入各组计数
    cout << n1 * n2 << '\n';
    for (int i = 1; i <= n<<1; ++i) if (vis[a[i]] == 2 && !ans[i]) {
        if (n1 < n) ans[i] = 1, n1++;
        else ans[i] = 2;
    }
    for (int i = 1; i <= n<<1; ++i) cout << ans[i] << (i == n<<1 ? '\n' : ' ');
    return 0;
}