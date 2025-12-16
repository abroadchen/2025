//
// Created by Psy.C on 2025/12/16.
//
/*
*内层循环n-1次，生成序列剩余的n-1个元素
每次将cnt加1，然后检查flag[cnt]是否为true(已被使用)
如果已被使用就继续递增cnt，直到找到未使用的数字
输出找到的数字
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 901
using namespace std;


int main() {
    fast;
    int n, k, a[30]; cin >> n >> k;
    bool flag[N] = {false};
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
        flag[a[i]] = true;//将这些特殊值在flag数组中标记为true(已使用)
    }
    int cnt = 0;//寻找未使用的数字
    for (int i = 0; i < k; ++i) {
        cout << a[i];//首先输出该序列的第一个元素(即对应的特殊值a[i])
        for (int j = 1; j < n; ++j) {
            ++cnt;
            while (flag[cnt]) ++cnt;
            cout << ' ' << cnt;
        }
        cout << '\n';
    }
    return 0;
}