//
// Created by Psy.C on 2026/2/2.
//

#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    char s[111]; cin >> s;
    const int len = static_cast<int>(strlen(s));
    if (int n1 = 0, n2 = 0, n3 = 0; len < 5) cout << "Too weak\n"; else {
        for (int i = 0; i < len-1; ++i) {
            if (s[i] >= '0' && s[i] <= '9') n1++;
            else if (s[i] >= 'a' && s[i] <= 'z') n2++;
            else if (s[i] >= 'A' && s[i] <= 'Z') n3++;
        }
        if (n1 > 0 && n2 > 0 && n3 > 0) cout << "Correct\n"; else {
            cout << "Too weak\n";
        }
    }
    return 0;
}