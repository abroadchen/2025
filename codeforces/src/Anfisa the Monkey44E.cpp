//
// Created by Psy.C on 2025/9/26.
//
/*
*优化输入输出性能：
关闭C++流与C流的同步
解除cin与cout的绑定，提高IO效率
 *
*k：要分割的段数
a：每段的最小长度
b：每段的最大长度
 *
 *条件判断：检查字符串长度是否在有效范围内
*avg：平均每段的长度（整除部分）
add：余数，表示有多少段需要额外增加1个字符
cnt：当前段已输出的字符计数器，初始化为0
 *
*如果当前段字符数达到目标长度则换行：
目标长度 = avg + (add > 0 ? 1 : 0)
当add > 0时，当前段长度为avg+1；否则为avg
 *
 *减少余数计数，表示一个需要额外字符的段已经处理完毕
 *
 *
 */
#include <ios>
#include <iostream>
using namespace std;

int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    long k, a, b; cin >> k >> a >> b;
    string s; cin >> s;

    if (s.size() < k * a || s.size() > k * b) {
        cout << "No solution" << endl;
        return 0;
    }

    long avg = s.size() / k, add = s.size() % k, cnt(0);
    for (long i = 0; i < s.size(); ++i) {
        cout << s[i];
        ++cnt;
        if (cnt >= avg + (add > 0)) {
            cout << endl;
            cnt = 0;
            --add;
        }
    }
    return 0;
}