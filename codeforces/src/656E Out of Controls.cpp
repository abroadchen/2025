//
// Created by Psy.C on 2026/4/8.
//

#include <bits/stdc++.h>
#def\
ine F fo\
r
using namespace std;
int n;
int main() {
    scanf("%d", &n);
    vector d(n, vector(n, 10000));
    F(int row = 0; row < n; row++) {
        F(int col = 0; col < n; col++) {
            scanf("%d", &d[row][col]);
        }
    }

    F(int k = 0; k < n; k++) {
        F(int a = 0; a < n; a++) {
            F(int b = 0; b < n; b++) {
                int test = d[a][k] + d[k][b];
                d[a][b] = d[a][b] < test ? d[a][b] : test;
            }
        }
    }

    int mx(0);
    F(int a = 0; a < n; a++) {
        F(int b = 0; b < n; b++) {
            mx = mx > d[a][b] ? mx : d[a][b];
        }
    }

    printf("%d\n", mx);
    return 0;
}
