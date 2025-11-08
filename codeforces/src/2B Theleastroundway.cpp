//
// Created by Psy.C on 2025/9/10.
//


#include <ios>
#include <iostream>
using namespace std;

const int MAXN = 1005;
const int INF = 1e9;
int n;
long long mat[MAXN][MAXN];
int cnt2[MAXN][MAXN], cnt5[MAXN][MAXN];
int dp2[MAXN][MAXN], dp5[MAXN][MAXN];
int path2[MAXN][MAXN], path5[MAXN][MAXN];
bool has_zero = false;
int zero_x, zero_y;

pair<int, int> count_factors(long long num) {
    if (num == 0) return {0, 0};
    int cnt2 = 0, cnt5 = 0;
    long long temp = num;
    while (temp % 2 == 0) {
        cnt2++;
        temp = temp / 2;
    }
    temp = num;
    while (temp % 5 == 0) {
        cnt5++;
        temp = temp / 5;
    }
    return {cnt2, cnt5};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
            if (mat[i][j] == 0) {
                has_zero = true;
                zero_x = i;
                zero_y = j;
            }
            auto p = count_factors(mat[i][j]);
            cnt2[i][j] = p.first;
            cnt5[i][j] = p.second;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp2[i][j] = dp5[i][j] = INF;
        }
    }

    dp2[0][0] = cnt2[0][0];
    dp5[0][0] = cnt5[0][0];



    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) continue;

            if (i > 0 && dp2[i - 1][j] != INF) {
                if (dp2[i - 1][j] + cnt2[i][j] < dp2[i][j]) {
                    dp2[i][j] = dp2[i - 1][j] + cnt2[i][j];
                    path2[i][j] = 0;
                }
            }

            if (j > 0 && dp2[i][j - 1] != INF) {
                if (dp2[i][j - 1] + cnt2[i][j] < dp2[i][j]) {
                    dp2[i][j] = dp2[i][j - 1] + cnt2[i][j];
                    path2[i][j] = 1;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) continue;


            if (i > 0 && dp5[i - 1][j] != INF) {
                if (dp5[i - 1][j] + cnt5[i][j] < dp5[i][j]) {
                    dp5[i][j] = dp5[i - 1][j] + cnt5[i][j];
                    path5[i][j] = 0;
                }
            }

            if (j > 0 && dp5[i][j - 1] != INF) {
                if (dp5[i][j - 1] + cnt5[i][j] < dp5[i][j]) {
                    dp5[i][j] = dp5[i][j - 1] + cnt5[i][j];
                    path5[i][j] = 1;
                }
            }
        }
    }

    int res1 = min(dp2[n - 1][n - 1], dp5[n - 1][n - 1]);
    int res2 = INF;


    if (has_zero) res2 = 1;
    int result = min(res1, res2);
    cout << result << "\n";

    string path = "";

    if (has_zero && result == res2) {
        for (int i = 0; i < zero_y; i++) path += 'R';
        for (int i = 0; i < zero_x; i++) path += 'D';
        for (int i = zero_y; i < n - 1; i++) path += 'R';
        for (int i = zero_x; i < n - 1; i++) path += 'D';
    } else {
        if (dp2[n - 1][n - 1] <= dp5[n - 1][n - 1]) {
            int x = n - 1, y = n - 1;
            string temp_path = "";
            while (x > 0 || y > 0) {
                if (path2[x][y] == 0) {
                    temp_path += 'D';
                    x--;
                } else {
                    temp_path += 'R';
                    y--;
                }
            }
            reverse(temp_path.begin(), temp_path.end());
            path = temp_path;
        } else {
            int x = n - 1, y = n - 1;
            string temp_path = "";
            while (x > 0 || y > 0) {
                if (path5[x][y] == 0) {
                    temp_path += 'D';
                    x--;
                } else {
                    temp_path += 'R';
                    y--;
                }
            }
            reverse(temp_path.begin(), temp_path.end());
            path = temp_path;
        }
    }
    cout << path << "\n";
    return 0;
}
