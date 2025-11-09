//
// Created by Psy.C on 2025/9/15.
//

#include <cstdio>
#include <map>
#include <cstdlib>
using namespace std;


int main() {
    map<int, map<int, int>> mp;
    map<int, int> mp1;
    int x[4], y[4], len = 0, flag = 1, x1[4], y1[4], xx = 0, yy = 0;
    for (int i = 0; i < 4; ++i) {
        scanf("%d%d", &x[i], &y[i]);
        scanf("%d%d", &x1[i], &y1[i]);
        mp[x[i]][y[i]]++;
        mp[x1[i]][y1[i]]++;
        if ((x1[i] == x[i]) && (y1[i] != y[i])) yy++;
        else if ((x1[i] != x[i]) && (y1[i] == y[i])) xx++;
        else flag = 0;
        len = abs(x1[i] - x[i] + y1[i] - y[i]);
        mp1[len]++;
    }
    if (xx != yy) flag = 0;
    for (int i = 0; i < 4; ++i) {
        if (mp[x[i]][y[i]] != 2 || mp[x1[i]][y1[i]] != 2) flag = 0;
        len = abs(x1[i] - x[i] + y1[i] - y[i]);
        if (mp1[len] < 2) flag = 0;
    }
    if (flag) puts("YES");
    else puts("NO");
    
    return 0;
}