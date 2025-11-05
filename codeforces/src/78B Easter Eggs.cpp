//
// Created by Psy.C on 2025/11/5.
//
/*
 *
*当i=3时：arr[3 + 3%4] = arr[3 + 3] = arr[6] = 'V'
当i=4时：arr[3 + 4%4] = arr[3 + 0] = arr[3] = 'G'
当i=5时：arr[3 + 5%4] = arr[3 + 1] = arr[4] = 'B'
当i=6时：arr[3 + 6%4] = arr[3 + 2] = arr[5] = 'I'
当i=7时：arr[3 + 7%4] = arr[3 + 3] = arr[6] = 'V'
 *
 */
#include <cstdio>
using namespace std;

const char arr[7] = {
    'R', 'O', 'Y', 'G', 'B', 'I', 'V'
};

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < 3; ++i) printf("%c", arr[i]);
    for (int i = 3; i < n; ++i) printf("%c", arr[3 + i%4]);
    puts("");
    return 0;
}