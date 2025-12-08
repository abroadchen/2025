//
// Created by Psy.C on 2025/12/7.
//
/*
*n：第一个数组的大小
m：第二个数组的大小（稍后输入）
a[50]：存储第一组数字的数组
mx：跟踪目前为止找到的最大商值（初始化为0）
cnt：统计达到最大商值的次数（初始化为1）
 *
*遍历第二个数组中的每个元素b（共m个元素）
对于每个b，检查数组a[]中的所有元素
找到第一个能整除b的元素（b % a[j] == 0）
计算商值x = b / a[j]（这代表某种"效率"）
如果这个商值大于当前最大值：
更新最大值（mx = x）
重置计数器为1（cnt = 1）
如果这个商值等于当前最大值：
增加计数器（++cnt）
跳出内层循环（只考虑a[]中第一个有效的元素）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m; cin >> n;
    int a[50], mx = 0, cnt = 1;
    for (int i = 0; i < n; ++i) cin >> a[i];
    cin >> m;
    for (int i = 0, b; i < m; ++i) {
        cin >> b;
        for (int j = 0; j < n; ++j) {
            if (b % a[j] == 0) {
                const int x = b / a[j];
                if (x > mx) { mx = x; cnt = 1; }
                else if (x == mx) ++cnt;
                break;
            }
        }
    }
    cout << cnt << '\n';
    return 0;
}