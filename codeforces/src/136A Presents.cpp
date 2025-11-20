//
// Created by Psy.C on 2025/11/20.
//
/*
 *O(n²)：对于每个位置都需要遍历整个数组查找
 *O(n)：只需要存储输入数组
 */
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin>>n;
    int p[100];
    for (int i = 0; i < n; ++i) cin>>p[i];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) if (p[j] == i + 1) {//查找值为i+1的元素
            cout << j + 1 << " ";//该元素的索引加1
            break;//假设每个数字只出现一次
        }
    }
    return 0;
}