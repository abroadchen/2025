//
// Created by Psy.C on 2026/4/18.
//
/**
sum /= n>>1 表示每一对的期望和
因为有n个数要分成n/2对，总和除以对数得到每对的平均值

外层循环遍历所有位置
if (!use[i]): 如果位置i还没被使用
use[i] = true: 标记位置i已使用
cout << i << ' ': 输出第一个配对元素的位置
内层循环寻找与位置i元素配对的元素
if (!use[j] && num[i] + num[j] == sum):
!use[j]: 位置j未被使用
num[i] + num[j] == sum: 两数之和等于目标值
找到配对后输出位置j，标记为已使用，跳出内层循环

时间复杂度：O(n²) 空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;
int n, num[N];
bool use[N];
int main() {
    fast;
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> num[i]; sum += num[i];
    }
    sum /= n>>1;//配对的数量
    for (int i = 1; i <= n; ++i) {
        if (!use[i]) {
            use[i] = true;
            cout << i << ' ';
            for (int j = 1; j <= n; ++j) {
                if (!use[j] && num[i] + num[j] == sum) {
                    cout << j << '\n';
                    use[j] = true;
                    break;
                }
            }
        }
    }
    return 0;
}