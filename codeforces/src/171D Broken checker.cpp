//
// Created by Psy.C on 2025/11/28.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;
ll n;

int main() {
    fast;
    cin>>n;
    cout << n % 5 % 3 + 1;
    return 0;
}