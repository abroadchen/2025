//
// Created by Psy.C on 2025/10/28.
//
/*
 *右边界br是否在[gl-1, 2*(gl+1)]范围内
 *左边界bl是否在[gr-1, 2*(gr+1)]范围内
 */
#include <cstdio>
using namespace std;

int gl(0), gr(0), bl(0), br(0);

int main() {
    scanf("%d %d", &gl, &gr);
    scanf("%d %d", &bl, &br);
    if (gl - 1 <= br && br <= 2 * (gl + 1) ||
        gr - 1 <= bl && bl <= 2 * (gr + 1))
        puts("YES");
    else puts("NO");
    return 0;
}