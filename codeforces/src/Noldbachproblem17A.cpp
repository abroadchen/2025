//
// Created by Psy.C on 2025/9/16.
//

#include <ios>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k; cin >> n >> k;
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i])
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
    }

    vector<int> primes;
    for (int i = 2; i <= n; ++i)
        if (is_prime[i])
            primes.push_back(i);

    int count = 0;
    for (int i = 0; i < (int)primes.size() - 1; ++i) {
        int sum = primes[i] + primes[i + 1] + 1;
        if (sum <= n && is_prime[sum]) count++;
    }

    if (count >= k) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}