//
// Created by Psy.C on 2026/3/26.
//
/**
str[0]为空字符串（占位符）
str[1]到str[12]对应不同的指数运算组合
x, y, z：输入的三个数值
num[13]：存储每种运算结果的对数值
ans：最大值

log(x^y) = log(x) * y，所以 log(x^(y^z)) = log(x) * (y^z)
通过比较对数值来避免直接计算巨大的指数值
具体计算：

num[1]：对应x^(y^z)的对数值，即log(x) * (y^z)
num[2]：对应x^(z^y)的对数值，即log(x) * (z^y)
num[3]：对应(x^y)^z的对数值，即log(x^y) * z = log(x) * y * z
num[5]：对应y^(x^z)的对数值，即log(y) * (x^z)
以此类推...
注意：跳过了num[4]和num[8]，它们对应(x^z)^y和(y^z)^x，但实际上这两个表达式等价于num[3]和num[7]

t：记录最大值对应的索引
循环遍历1到11，跳过4和8（因为它们与3和7重复）
i == 1 || ans < num[i]：更新最大值和对应索引
i == 1：当处理第一个元素时，由于ans初始化为0，我们需要先用第一个元素初始化ans
ans < num[i]：当当前元素比之前记录的最大值更大时

时间复杂度：O(1)（固定12种情况） 空间复杂度：O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ld long double
using namespace std;
char str[][13] = {
    "", "x^y^z", "x^z^y", "(x^y)^z", "(x^z)^y", "y^x^z",
    "y^z^x", "(y^x)^z", "(y^z)^x", "z^x^y", "z^y^x", "(z^x)^y", "(z^y)^x"
};
ld x, y, z, num[13], ans;
int main() {
    fast;
    cin >> x >> y >> z;
    num[1] = log(x) * pow(y, z);
    num[2] = log(x) * pow(z, y);
    num[3] = log(x) * (y*z);
    num[5] = log(y) * pow(x, z);
    num[6] = log(y) * pow(z, x);
    num[7] = log(y) * (x*z);
    num[9] = log(z) * pow(x, y);
    num[10] = log(z) * pow(y, x);
    num[11] = log(z) * (x*y);
    int t = 0;
    for (int i = 1; i < 12; ++i) {
        if (i == 4 || i == 8) continue;
        if (i == 1 || ans < num[i]) {
            ans = num[i];
            t = i;
        }
    }
    cout << str[t] << '\n';
    return 0;
}