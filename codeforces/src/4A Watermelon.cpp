//
// Created by Psy.C on 2025/9/11.
//


#include <iostream>
using namespace std;

int main() {
    int w;
    cin >> w;

    if (w >= 4 && w % 2 == 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}