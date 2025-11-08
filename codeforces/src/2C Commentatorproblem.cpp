
//
// Created by Psy.C on 2025/9/10.
//


#include <iostream>
#include <cmath>
using namespace std;



struct stadium {
    int x, y, r;
} stadium[3];

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, 1, -1, 0};

const double eps = 1e-6;
double stadium_tmp[3];

double cost(double x, double y) {
    for (int i = 0; i < 3; i++) {
        stadium_tmp[i] = sqrt(pow(x - stadium[i].x, 2) + pow(y - stadium[i].y, 2));
        stadium_tmp[i] /= stadium[i].r;
    }

    double ct = 0.0;
    for (int i = 0; i < 3; i++) {
        ct += pow(stadium_tmp[i] - stadium_tmp[(i + 1) % 3], 2);
    }
    return ct;
}




int main() {
    double x = 0.0, y = 0.0;
    for (int i = 0; i < 3; i++) {
        scanf("%d%d%d", &stadium[i].x, &stadium[i].y, &stadium[i].r);
        x += stadium[i].x;
        y += stadium[i].y;
    }
    x /= 3.0;
    y /= 3.0;
    double step = 1.0;

    double error = cost(x, y);
    double res_x = -1, res_y = -1;
    while (step > eps) {
        int min_error_index = -1;

        for (int i = 0; i < 4; i++) {
            double temp_x = 0.0, temp_y = 0.0;
            temp_x = x + dx[i] * step;
            temp_y = y + dy[i] * step;
            double temp_error = cost(temp_x, temp_y);
            if (temp_error < error) {
                error = temp_error;
                min_error_index = i;
                res_x = temp_x;
                res_y = temp_y;
            }
        }

        if (min_error_index == -1) step /= 2;
        else {
            x = x + dx[min_error_index] * step;
            y = y + dy[min_error_index] * step;
        }
    }
    if (error < eps) printf("%.5lf %.5lf\n", res_x, res_y);

    return 0;
}
