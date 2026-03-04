//
// Created by Psy.C on 2026/3/4.
//
/**
a[]: 存储0-9的英文单词
b[]: 存储10-19的英文单词
c[]: 存储20, 30, 40, ..., 90的英文单词

如果n < 10（0-9）：
直接输出a[n]，即对应数字的英文单词
否则，如果n < 20（10-19）：
输出b[n-10]，即10-19的英文单词
否则（20-99）：
输出c[n/10-2]，即十位数的英文（如20对应c[0]="twenty"）
如果个位不为0：
输出"-"连接符和个位数字的英文单词

时间复杂度为O(1)，空间复杂度为O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
string a[] = {
    "zero" , "one" , "two" , "three" , "four" ,
    "five" , "six" , "seven" , "eight" , "nine"
}, b[] = {
    "ten" , "eleven" , "twelve" , "thirteen" , "fourteen" ,
    "fifteen" , "sixteen" , "seventeen" , "eighteen" , "nineteen"
}, c[] = {
    "twenty" , "thirty" , "forty" , "fifty" , "sixty" ,
    "seventy" , "eighty" , "ninety"
};
int main() {
    fast;
    cin >> n;
    if (n < 10) cout << a[n];
    else {
        if (n < 20) cout << b[n-10];
        else {
            cout << c[n/10-2];
            if (n%10 != 0) cout << '-' << a[n%10];
        }
    }
    return 0;
}