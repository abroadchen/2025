//
// Created by Psy.C on 2025/10/13.
//将序列1,2,3,...,n重新排列为2,3,4,...,n,1

#include <ios>
#include <iostream>
using namespace std;

int n;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;

    for (int i = 1; i <= n - 1; ++i) cout << i + 1 << " ";
    cout << "1 ";
    return 0;
}