//
// Created by Psy.C on 2025/9/17.
//

/*
*计算欧拉函数φ(a)：
欧拉函数表示小于等于a且与a互质的正整数个数
对a进行质因数分解，对于每个质因子i，ans乘以(1-1/i)
处理完所有质因子后，如果a>1说明还有一个大的质因子
 *
 *
 *
*快速幂运算（模运算版本）：
计算a^k mod p
使用二进制拆分法，时间复杂度O(log k)
每次平方底数，根据指数的二进制位决定是否累乘到结果中
 *
 *
*b: 将bIn字符串转换为模c的数字
n: 将nIn字符串转换为模1e9的数字（用于判断大小）
p: 计算c的欧拉函数φ(c)
k: 后面将计算的指数值
 *
*判断指数是否过大：
如果n大于φ(c)或者nIn长度超过9位，则需要使用欧拉定理优化
根据欧拉定理：a^φ(m) ≡ 1 (mod m)，当gcd(a,m)=1时
此时k = (n-1) mod φ(c) + φ(c)（保证结果为正）
否则直接k = n-1
 *
 *
 *计算 1 + b + b^2 + ... + b^(n-1) mod c
 *
 */


#include <ios>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;


//将字符串s转换为数字
long long read(const string& s, long long p) {
    long long ans = 0;
    int len = s.length();
    for (int i = 0; i < len; ++i) {
        ans = ans * 10 + s[i] - '0';
        ans %= p;
    }
    return ans;
}

long long phi(long long a) {
    long long ans = a;
    for (long long i = 2; i * i <= a; ++i) {
        if (a % i == 0) {
            ans = ans / i * (i - 1);
            while (a % i == 0) a /= i;
        }
    }
    if (a > 1) ans = ans / a * (a - 1);
    return ans;
}

long long pow(long long a, long long k, long long p) {
    long long ans = 1;
    for (; k; k >>= 1, a = a * a % p)
        if (k & 1)
            ans = ans * a % p;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string bIn, nIn; long long c;
    cin >> bIn >> nIn >> c;
    
    long long b = read(bIn, c), n = read(nIn, 1e9), p = phi(c), k;

    if (n > p || nIn.length() > 9) k = (read(nIn, p) - 1 + p) % p + p;
    else k = n - 1;

    long long ans = (b - 1 + c) % c * pow(b, k, c) % c;
    cout << (ans ? ans : c) << '\n';
    return 0;
}