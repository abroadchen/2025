//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
res：当前这一轮要填的数值基数。每一轮从 1 开始，每进入下一轮就 *2
当 n > 3 时：
先输出 (n+1)/2 个相同的值 res（即向上取整个数，ceil(n/2)）。
然后 res *= 2（值基数翻倍），n /= 2（剩余待处理长度减半，整数除法向下）。
效果：一轮输出约一半的长度，把剩余问题规模减半，同时数值基数翻倍。
直观理解（配合尾部）：每轮把近一半的元素"打包"成相同值，剩下的一半进入下一轮，值翻倍，保证相邻层的数值满足倍率差
循环结束后 n 只剩下 1、2、3 三种可能，分别处理：
只剩 1 个：输出 res。
剩 2 个：输出 res、res*2（两个值，差倍率为 2）。
剩 3 个：输出 res、res、res*3
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    int res = 1;
    while (n > 3) {
        for (int i = 1; i <= (n+1)/2; i++) cout << res << ' ';
        res *= 2; n /= 2;
    }
    if (n == 1) cout << res << '\n';
    else if (n == 2) cout << res << ' ' << res*2 << '\n';
    else cout << res << ' ' << res << ' ' << res*3 << '\n';
    return 0;
}