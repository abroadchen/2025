//
// Created by Psy.C on 2025/9/14.
//

#include <cstdio>
#include <cstdlib>

using namespace std;

static const int N = 1002;
int n, k, x;
int mp[N][N];


void solve(int x) {
    int px = (k + 1) / 2, py = (k + 1) / 2;
    int ans1=0, ans2=0, ans3=0, ans4=1e9;

    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= k - x + 1; ++j) {
            int sum = 0, flag = 1;
            for (int t = j; t < j + x; ++t) {
                if (mp[i][t]) {
                    flag = 0;
                    break;
                }
                sum += abs(t - py) + abs(i - px);
            }
            if (flag == 1 && sum < ans4)
                ans4 = sum, ans1 = i, ans2 = j, ans3 = j + x - 1;
        }
    }
    if (ans4 == 1e9) printf("-1\n");
    else {
        for (int i = ans2; i <= ans3; ++i) mp[ans1][i] = 1;
        printf("%d %d %d\n", ans1, ans2, ans3);
    }
}








int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &x), solve(x);
    return 0;
}