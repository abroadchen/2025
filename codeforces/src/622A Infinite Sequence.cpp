//
// Created by Psy.C on 2026/3/26.
//
/**
先找到n所在的行号k
k*(k+1)/2是前k行的总数
k*(k-1)/2是前k-1行的总数
n - k*(k-1)/2就是n在第k行的位置（列号）

数字n在三角形排列中处于第几列。
时间复杂度：O(1) 空间复杂度：O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, k;
int main() {
    fast;
    cin >> n;
    k = floor(sqrt(n<<1));//√(2n)
    //1+2+3+...+k的和
    if (k*(k+1)/2 < n) k++;
    cout << n-k*(k-1)/2;
    return 0;
}