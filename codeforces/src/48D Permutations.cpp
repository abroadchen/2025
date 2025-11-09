//
// Created by Psy.C on 2025/10/12.
//
/*
*创建二维数组s[N][2]并初始化为0，用于存储输入数据及其出现次序
创建一维数组s1[N]并初始化为0，用于统计每个数字出现的次数

 *
 *声明变量n（数据个数）、f（标志位，默认为1表示true）、mid（记录最大值，默认为0）
 *
*读取第i个数据存入s[i][0]
如果当前数据大于已知最大值mid，则更新mid
在s1数组中对应位置计数加1（统计该数字出现次数）
将当前数字是第几次出现记录在s[i][1]中
 *
*检查条件：从1到mid-1，检查每个数字的出现次数是否不小于其后继数字的出现次数

如果发现某个数字出现次数小于后一个数字的出现次数，则将标志f设为0并跳出循环
 *
 *如果f为真（满足条件），输出第一个数字的出现次数，并依次输出每个输入数据是该数字的第几次出现
 *
 */
#include <ios>
#include <iostream>
using namespace std;

const long N = 200000;
int s[N][2] = {0}, s1[N] = {0};

int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    for (int i = 0; i < N; ++i) s1[i] = 0;
    int n, f(1), mid(0); cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> s[i][0];
        if (s[i][0] > mid) mid = s[i][0];
        s1[s[i][0]]++;
        s[i][1] = s1[s[i][0]];
    }
    for (int i = 1; i <= mid - 1; ++i) {
        if (s1[i] < s1[i + 1]) {
            f = 0;
            break;
        }
    }
    if (f) {
        cout << s1[1] << endl;
        for (int i = 0; i < n; ++i) cout << s[i][1] << ' ';
    } else cout << "-1";
    return 0;
}