//
// Created by Psy.C on 2025/9/11.
//


#include <ios>
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, c, d;
    cin >> a >> b >> c >> d;

    int sides[4] = {a, b, c, d};
    sort(sides, sides + 4);

    if (sides[0] + sides[1] > sides[2]) {
        cout << "TRIANGLE\n";
        return 0;
    }
    if (sides[0] + sides[1] > sides[3]) {
        cout << "TRIANGLE\n";
        return 0;
    }
    if (sides[0] + sides[2] > sides[3]) {
        cout << "TRIANGLE\n";
        return 0;
    }
    if (sides[1] + sides[2] > sides[3]) {
        cout << "TRIANGLE\n";
        return 0;
    }

    if (sides[0] + sides[1] == sides[2] ||
        sides[0] + sides[1] == sides[3] ||
        sides[0] + sides[2] == sides[3] ||
        sides[1] + sides[2] == sides[3]) {
        cout << "SEGMENT\n";
        return 0;
    }
    cout << "IMPOSSIBLE\n";
    return 0;
}