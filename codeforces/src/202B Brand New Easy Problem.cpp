//
// Created by Psy.C on 2025/12/5.
//
/*
*s[21][25]：最多存储21个字符串，每个字符串最长24个字符
k：实际字符串数量
v[10]：存储10个这样的结构体
 *n(关键词数量)、m(测试用例数量)
 *初始化排列数组f为[0,1,2,...,n-1]
 *p(最优测试用例索引)、ans(最优逆序对数)
 *
*计算当前排列的逆序对数sum
逆序对：对于i<j，如果f[i]>f[j]则构成逆序对
*剪枝：如果当前逆序对数已经超过最优解，则跳过
检查每个测试用例是否包含所有关键词：
按照当前排列f的顺序，在测试用例中查找关键词
k表示按顺序匹配到的关键词数量
如果k>=n说明全部匹配完成，跳出循环
*如果当前测试用例有效(i<m)且优于当前最优解：
更新最优解：p记录测试用例索引，ans记录逆序对数
继续下一个排列
*如果没有找到有效解(p仍为初始值20)，输出"Brand new problem!"
否则输出：
最优测试用例编号(索引+1)
特殊格式输出，其中'|'的数量根据逆序对数计算得出
 *
 *时间复杂度：O(n! × m × max_length)，其中n是关键词数量，m是测试用例数量
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

struct node { char s[21][25]; int k; } v[10];

int main() {
    fast;
    int n, m, f[4]; cin>>n;
    char a[4][20];
    for (int i = 0; i < n; ++i) cin>>a[i];
    cin>>m;
    for (int i = 0; i < n; ++i) f[i] = i;
    for (int i = 0; i < m; ++i) {
        cin >> v[i].k;
        for (int j = 0; j < v[i].k; ++j) cin >> v[i].s[j];
    }
    int p = 20, ans = 10000;
    do {
        int sum = 0, i;
        for (i = 0; i < n; ++i) for (int j = 0; j < i; ++j) {
            if (f[j] > f[i]) sum++;
        }
        if (sum > ans) continue;
        for (i = 0; i < m; ++i) {
            int k = 0;
            for (int j = 0; j < v[i].k && k < n; ++j) {
                if (strcmp(a[f[k]], v[i].s[j]) == 0) k++;
            }
            if (k >= n) break;
        }
        if (i < m && (sum < ans || sum == ans && p > i)) {
            p = i; ans = sum;
        }
    } while (next_permutation(f, f+n));
    if (p == 20) cout << "Brand new problem!\n";
    else {
        cout << p + 1 << "\n[:";
        const int t = n * (n - 1) / 2 + 1 - ans;
        for (int i = 0; i < t; ++i) cout << '|';
        cout << ":]\n";
    }
    return 0;
}