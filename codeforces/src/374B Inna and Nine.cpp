//
// Created by Psy.C on 2026/1/22.
//
/*
* 时间复杂度: O(n)，单次遍历
空间复杂度: O(n)，存储辅助数组
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;


int main() {
    fast;
    char num[N]; scanf("%s\n", num + 1);
    const int n = static_cast<int>(strlen(num + 1));
    num[n+1] = 0;//在字符串末尾添加结束标志
    int l[N] = {};//连续满足条件的长度
    ll ans = 1l;
    for (int i = 2; i <= n + 1; ++i) {
        //两个数字之和是否等于9
        if (num[i-1] + num[i] - 2 * '0' == 9) l[i] = l[i-1]+1;
        //存在连续序列 l[i-1]是否为偶数
        else if (l[i-1] > 0 && !(l[i-1]&1)) ans *= (l[i-1]>>1) + 1l;//不同段的组合数相乘
    }
    cout << ans << '\n';
    return 0;
}