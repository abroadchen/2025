//
// Created by Psy.C on 2025/12/8.
//
/*
*n：需要分配的资源总数
m：容器数量
a[N]：数组存储每个容器的容量
 *
*mn：累计最小成本
num：当前可使用的最小容量（初始为最小容器容量）
k：当前处理的容器索引
循环n次（分配n个资源）：
将当前容量加入总成本
容量减1（该容器剩余容量减少）
如果当前容器用完（num==0），切换到下一个容器
 *
*使用greater<>谓词对数组进行降序排序
mx：累计最大成本
循环n次（注意这里n会递减至0）：
将最大容量加入总成本
最大容量容器的容量减1
*从第二个元素开始检查
如果当前元素大于前一个元素，则交换它们
这确保了每次操作后数组仍然是降序排列的
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000
using namespace std;


int main() {
    fast;
    int n, m, a[N]; cin>>n>>m;
    for (int i = 0; i < m; ++i) cin>>a[i];
    sort(a,a+m);
    int mn = 0, num = a[0], k = 0;
    for (int i = 0; i < n; ++i) {
        mn += num;
        num -= 1;
        if (num == 0) num = a[++k];
    }
    sort(a, a + m, greater<>());
    int mx = 0;
    while (n--) {
        mx += a[0];
        a[0] -= 1;
        for (int i = 1; i < m; ++i) {
            if (a[i] <= a[i-1]) break;
            swap(a[i], a[i-1]);
        }
    }
    cout << mx << ' ' << mn << '\n';
    return 0;
}