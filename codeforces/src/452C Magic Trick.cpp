//
// Created by Psy.C on 2026/2/10.
//
/**
预处理：O(N)，其中N=1000000
主计算：O(min(m,n))
空间复杂度：O(N)

sum = ln(C(m,i)) + ln(C(n*m-m, n-i)) - ln(C(n*m, n))
    = ln[C(m,i) * C(n*m-m, n-i) / C(n*m, n)]
 */
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000000
using namespace std;

double num[N+1];
void init() {//ln(1) + ln(2) + ... + ln(i) = ln(i!)
    for (int i = 1; i <= N; ++i) num[i] = num[i-1] + log(i);
}

//ln(C(m,n)) = ln(m!) - ln(n!) - ln((m-n)!)
double get(const int m, const int n) {
    return num[m] - num[n] - num[m - n];
}

int n, m;

int main() {
    fast; init();
    cin >> n >> m;
    double res = 0, sum = 0;
    for (int i = 1; i <= min(m, n); ++i) {
        ///C(m,i)的对数
        ///C(n*m-m, n-i)的对数
        ///-C(n*m, n)的对数
        sum = get(m, i) + get(n*m-m, n-i) - get(n*m, n);
        sum = exp(sum);//转换回原值
        res += sum*i*i/n;//权重项
    }
    cout << res << '\n';
    return 0;
}