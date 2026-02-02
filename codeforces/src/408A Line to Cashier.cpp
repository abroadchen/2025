//
// Created by Psy.C on 2026/2/2.
//
/**
* t：测试用例数量
i：外层循环索引
num[110]：存储每个测试用例中数字的数量
sum：当前测试用例的总和
j：内层循环索引
n：当前读入的数字
 *
*时间复杂度：O(∑num[i])，即所有数字的总数
空间复杂度：O(t)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define inf 9999999
using namespace std;


int main() {
    fast;
    int t, i, num[110], sum, j, n; cin >> t;
    for (i = 0; i < t; ++i) cin >> num[i];//读入每个测试用例包含的数字个数
    int cnt = inf;//用于找最小值
    for (i = 0; i < t; ++i) {//遍历每个测试用例
        for (sum = j = 0; j < num[i]; ++j) {//循环读入num[i]个数字
            cin >> n;//读入当前数字
            sum += n * 5 + 15;//每个数字的贡献值
        }
        cnt = cnt < sum ? cnt : sum;//保留最小值
    }
    cout << cnt << '\n';
    return 0;
}