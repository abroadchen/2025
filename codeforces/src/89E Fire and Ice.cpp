//
// Created by Psy.C on 2025/11/9.
//
/*
*n：数组长度
a[N]：存储输入数据的数组
b[N]：临时计算数组
 *
*寻找最优解：
ans：最优解的代价，初始化为无穷大
t：最优位置
对每个位置i进行计算：
构造数组b：b[j] = max(0, a[j] - (j >= i))，即如果j≥i则a[j]减1
计算代价sum：
初始值为-i（惩罚项）
对每个元素加上3*b[j]（基础代价）
加上2*max(b[j]-b[j-1], 0)（递增惩罚）
更新最优解
 *根据最优解t，将位置t及之后的所有元素减1（至少为0）
 *
*生成主要的输出字符串：
对每个位置i：
当a[i]大于0时循环：
输出"ARA"
找到连续非零段的末尾j
从j到i逆序输出"L"，同时将对应位置的a值减1
输出"A"
输出"AR"
 *
*输出结尾部分：
输出"A"
从位置n到t逆序输出"L"
输出"A"
 *
 */
#include <algorithm>
#include <iostream>
#define rep(i,n) for(int i=1;i<=(n);++i)
using namespace std;

const int N = 1005, inf = 1e9;
int n, a[N], b[N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    rep(i,n) cin >> a[i];
    while (!a[n]) n--;//移除末尾的0元素，调整n的值
    int ans(inf), t(0);
    rep(i,n) {
        rep(j,n) b[j] = max(0, a[j] - (j >= i));
        int sum = -i;
        rep(j,n) sum += 3 * b[j] + 2 * max(b[j] - b[j - 1], 0);
        if (sum < ans) ans = sum, t = i;
    }
    for (int j = t; j <= n; ++j) a[j] = max(a[j] - 1, 0);
    rep(i,n) {
        while (a[i]) {
            cout << "ARA";
            int j = i;
            while (a[j + 1]) j++, cout << "RA";
            for (int k = j; k >= i; --k) cout << "L", a[k] = max(a[k] - 1, 0);
            cout << "A";
        }
        cout << "AR";
    }
    cout << "A";
    for (int j = n; j >= t; --j) cout << "L";
    cout << "A";
    return 0;
}