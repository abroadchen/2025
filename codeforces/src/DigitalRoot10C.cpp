//
// Created by Psy.C on 2025/9/14.
//

#include <ios>
#include <iostream>
#include <vector>
using namespace std;

int digital_root(long long n) {
    while (n > 9) {
        long long sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        n = sum;
    }
    return n;
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N; cin >> N;
    vector<long long> count(10, 0);
    for (long long i = 1; i <= N; i++) count[digital_root(i)]++;

    long long result = 0;
    for (int dr_a = 1; dr_a <= 9; ++dr_a) {
        for (int dr_b = 1; dr_b <= 9; ++dr_b) {
            int product_dr = digital_root((long long)dr_a * dr_b);
            long long count_c = count[product_dr];
            result += count[dr_a] * count[dr_b] * count_c;
        }
    }

    for (long long A = 1; A <= N; ++A) {
        for (long long B = 1; B <= min(N, (long long)(N/A)); ++B) {
            long long C = A * B;
            if (C <= N) {
                int dr_a = digital_root(A);
                int dr_b = digital_root(B);
                int dr_c = digital_root(C);
                int product_dr = digital_root((long long)dr_a * dr_b);
                if (product_dr == dr_c) result--;
            }
        }
    }

    cout << result << "\n";
    return 0;
}