//
// Created by Psy.C on 2025/9/13.
//

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define N 30
using namespace std;
const int INF = 0x3f3f3f3f;

struct Node {
    int x, y;
}a[N];

int dis[N][N], dp[(1 << 24) + 7];

int getdis(int i, int j) {
    return (a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y);
}


int main() {


    scanf("%d%d", &a[0].x, &a[0].y);
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) dis[i][j] = getdis(i, j);
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int i = 1; i < (1 << n); i++) {
        for (int j = 1; j <= n; j++) {
            if (i & (1 << (j - 1))) {
                if (dp[i ^ (1 << (j - 1))] == INF) continue;
                dp[i] = dp[i ^ (1 << (j - 1))] + dis[j][0] * 2;
                for (int k = j + 1; k <= n; k++) {
                    if (i & (1 << (k - 1))) {
                        if (dp[i ^ (1 << j - 1) ^ (1 << (k - 1))] == INF) continue;
                        dp[i] = min(dp[i], dp[i ^ (1 << (j - 1)) ^ (1 << (k - 1))] + dis[0][j] + dis[j][k] + dis[k][0]);
                    }
                }
                break;
            }
        }
    }
    printf("%d\n", dp[(1 << n) - 1]);
    vector<int> ans;

    int sta = (1 << n) - 1;
    while (sta) {
        int flag = 0, a = 0, b = 0;
        for (int i = 1; i <= n; i++) {
            if (sta & (1 << (i - 1))) {
                if (dp[sta] == dp[sta ^ (1 << (i - 1))] + dis[i][0] * 2) {
                    flag = 1;
                    a = i;
                    break;
                }
                for (int j = i + 1; j <= n; j++) {
                    if (sta & (1 << (j - 1))) {
                        if (dp[sta] == dp[sta ^ (1 << (i - 1)) ^ (1 << (j - 1))] + dis[0][i] + dis[i][j] + dis[j][0]) {
                            flag = 2;
                            a = i;
                            b = j;
                            break;
                        }
                    }
                }
                break;
            }
        }
        if (flag == 1) {
            ans.push_back(0);
            ans.push_back(a);
            sta ^= 1 << (a - 1);
        } else if (flag == 2) {
            ans.push_back(0);
            ans.push_back(a);
            ans.push_back(b);
            sta ^= 1 << (a - 1);
            sta ^= 1 << (b - 1);
        }
    }

    ans.push_back(0);
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) printf("%d ", ans[i]);

    return 0;
}