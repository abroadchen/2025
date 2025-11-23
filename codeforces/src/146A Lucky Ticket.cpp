//
// Created by Psy.C on 2025/11/21.
//时间复杂度：O(n) 空间复杂度：O(n)

#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    int n; scanf("%d\n", &n);//读取一个整数后读取换行符
    string num; getline(cin, num);
    string ans = "YES";
    int sum1(0), sum2(0);//sum1:前半部分数字和, sum2:后半部分数字和
    for (int i = 0; i < n/2; ++i) {
        if (num[i] != '4' && num[i] != '7') { ans = "NO"; break; }
        if (num[n/2+i] != '4' && num[n/2+i] != '7') { ans = "NO"; break; }
        sum1 += num[i] - '0'; sum2 += num[n/2+i] - '0';
    }
    if (sum1 != sum2) ans = "NO";
    cout << ans << '\n';
    return 0;
}