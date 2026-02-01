//
// Created by Psy.C on 2026/2/1.
//
/**
* 第一轮：O(n) - 读入并统计互补对
第二轮：O(N) - 遍历整个范围
总体：O(N)，由于N通常远大于n
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000000
using namespace std;


int main() {
    fast;
    int n; cin >> n; cout << n << '\n';
    vector used(N+1, 0);//数字是否被使用
    int cnt = 0;//特殊配对的数量
    for (int p = 0, x; p < n; ++p) {
        cin >> x; used[x] = 1;//读入n个数字并标记为已使用
        if (used[N+1-x]) ++cnt;//N+1-x是否已存在 x和N+1-x都存在，则cnt++（形成互补对)
    }
    for (int p = 1; p <= N; ++p) {
        //p被使用而N+1-p未被使用时
        if (used[p] && !used[N+1-p]) cout << N+1-p << ' ';
        //还有剩余配对需求(cnt > 0)且p和N+1-p都未被使用时
        if (cnt > 0 && !used[p] && !used[N+1-p]) {
            --cnt;//减少配对计数器
            cout << p << ' ' << N+1-p << ' ';//输出一对互补数字p和N+1-p
        }
    }
    cout << '\n';
    return 0;
}