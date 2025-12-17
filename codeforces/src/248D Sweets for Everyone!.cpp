//
// Created by Psy.C on 2025/12/16.
//
/*
*n：字符串长度
h：字符串中'H'字符的数量
str[N]：存储输入字符串的字符数组
*ok函数判断在给定条件下是否可行
mid：当前的某种状态值（可能是差值）
step：剩余步数
cnt：已处理的'H'字符数量
p1：第一个'H'的位置（初始化为-1）
p2：最近一个'H'的位置
sub：累积的某种距离
 *
*遍历字符串
如果所有'H'都已处理完且状态非负：
如果剩余步数足够，则返回true
否则返回false
*步数减1
如果当前字符是'H'：
如果状态为0，记录位置信息
状态减1，计数加1
如果当前字符是'S'：
状态加1
如果状态变为0，更新累积距离
*循环结束后检查最终条件
如果步数足够且状态非负，返回true
否则返回false
 *
*'H'可能代表某种需要消耗资源的操作
'S'可能代表某种补充资源的操作
目标是在有限步数内处理所有'H'字符
 *
*二分优化：将枚举优化为二分搜索O(log h)
模拟验证：每次验证需要O(n)时间
总体复杂度：O(n log h)
 *
 *
*当mid可行时，mid本身可能就是答案，所以r = mid（保留mid）
当mid不可行时，mid肯定不是答案，所以l = mid + 1（排除mid）
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 5000005
using namespace std;

int n, h;
char str[N];
int ok(int mid, int step) {
    int cnt = 0, p1 = -1, p2 = 0, sub = 0;
    for (int i = 0; i < n; ++i) {
        if (cnt == h && mid >= 0) {
            if (step >= min(i - p1, sub)) return true;
            return false;
        }
        step--;
        if (str[i] == 'H') {
            if (mid == 0) {
                if (p1 == -1) p1 = i;
                p2 = i;
            }
            mid--; cnt++;
        } else if (str[i] == 'S') {
            mid++;
            if (mid == 0) {
                sub += i - p2;
                if (cnt != h) sub += i - p2;//如果还没有处理完所有的'H'字符
            }
        }
    }//直线距离成本 实际路径成本 选择成本较低的方案
    if (step >= min(n - 1 - p1, sub) && mid >= 0) return true;
    return false;
}


int main() {
    fast;
    int t; cin >> n >> t;
    cin >> str;
    for (int i = 0; i < n; ++i) if (str[i] == 'H') h++;
    int l = 0, r = h;
    while (l < r) {
        const int mid = (l + r) >> 1;
        if (ok(mid, t)) r = mid; else l = mid + 1;
    }
    if (ok(l, t)) cout << l << '\n';
    else cout << "-1\n";
    return 0;
}