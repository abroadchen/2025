//
// Created by Psy.C on 2025/9/16.
//

#include <ios>
#include <iostream>
using namespace std;

long long xor_sum(long long n) {
    if (n <= 0) return 0;
    long long mod = n % 4;
    if (mod == 0) return n;
    if (mod == 1) return 1;
    if (mod == 2) return n + 1;
    return 0;
}

long long range_xor(long long a, long long b) {
    return xor_sum(b) ^ xor_sum(a - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    long long total_xor = 0;

    for (int i = 0; i < n; ++i) {
        long long x, m; cin >> x >> m;
        long long range_result = range_xor(x, x + m - 1);
        total_xor ^= range_result;
    }

    if (total_xor == 0) cout << "bolik\n";
    else cout << "tolik\n";
    
    return 0;
}