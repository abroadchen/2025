//
// Created by Psy.C on 2025/11/8.
//时间复杂度为O(log(min(a,b)))

#include <cstdio>
using namespace std;

int gcd(int a, int b) { return a%b==0?b:gcd(b,a%b); }

int main() {
    int a, b; scanf("%d %d",&a,&b);
    int g = gcd(a,b); a /= g; b /= g;//得到最简分数形式
    if (a == b - 1 || b == a - 1) puts("Equal");//|a-b| = 1（即a和b相差1）
    else if (a < b) puts("Dasha");
    else if (a > b) puts("Masha");
    return 0;
}