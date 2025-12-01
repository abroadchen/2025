//
// Created by Psy.C on 2025/11/30.
//
/*
*从2开始寻找x的第一个因子（最小因子）
循环到√x即可，因为如果存在大于√x的因子，必然对应一个小于√x的因子
如果找到因子i（即x % i == 0）：
 *将x除以找到的最小因子i
 *将除法后的结果x加到答案中
 *递归调用DFS函数处理新的x值
 *找到第一个因子并处理后就返回，不再继续寻找其他因子
 *如果没有找到任何因子（说明x是质数），将ans加1
 *
 *初始化ans为n，这是第一次分解的结果
 *n加上n的所有最小因子分解过程中产生的商的和，再加上最后的1。
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, ans;

void dfs(int x) {
    if (x == 1) { ans++; return; }//返回，结束当前递归分支
    for (int i = 2; i * i <= x; ++i) if (x % i == 0) {
        x /= i;
        ans += x;
        dfs(x);
        return;
    }
    ans++;
}

int main() {
    fast;
    cin>>n;
    ans = n;
    dfs(n);
    cout<<ans<<'\n';
    return 0;
}