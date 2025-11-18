//
// Created by Psy.C on 2025/11/18.
//
/*
*计算圆j相对于圆i的第一类切线角度范围[low, high]
asin计算反正弦值
添加进入事件(角度low, 类型1)和离开事件(角度high-eps, 类型-1)
如果low > high说明跨越了-π到π的边界，tmp加1
*计算圆j相对于圆i的第二类切线角度范围
同样添加进入和离开事件
如果跨越边界，tmp加1
 *
*按顺序处理所有事件
更新最大值ans
根据事件类型更新tmp计数器
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#define pi acos(-1.0)
#define eps 1.e-9
using namespace std;

typedef long long ll;

struct node { double x, y; };

double ang(node p, node q) {
    double dx = q.x - p.x, dy = q.y - p.y;
    return atan2(dy, dx);//向量的角度（弧度制）
}

double dist(node p, node q) {
    double dx = p.x - q.x, dy = p.y - q.y;
    return sqrt(dx * dx + dy * dy);
}

double norm(double t) {
    while (t < -pi) t += 2. * pi;
    while (t > pi) t -= 2. * pi;
    return t;//将角度规范化到[-π, π]范围内
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    ll n, k; cin >> n >> k;
    vector<node> o(n);//存储圆心坐标
    vector<double> r(n);//半径
    for (int i = 0; i < n; ++i) cin >> o[i].x >> o[i].y >> r[i];
    int ans = 1;
    for (int i = 0, tmp; i < n; ++i) {//遍历每个圆i作为参考圆
        tmp = 1;//（包含自己）
        vector<pair<double, int>> v;//角度和事件类型
        for (int j = 0; j < n; ++j) {//遍历其他所有圆j
            if (j != i) {//计算圆i到圆j的方向角mid和距离d
                double mid = ang(o[i], o[j]),
                d = dist(o[i], o[j]);
                {
                    double low = mid - asin((r[j] - r[i]) / d),
                    high = mid - asin((-r[j] - r[i]) / d);
                    low = norm(low), high = norm(high);
                    v.push_back({low, 1});
                    v.push_back({high - eps, -1});
                    if (low > high) tmp++;
                }
                {
                    double low = mid + pi - asin((r[j] + r[i]) / d),
                    high = mid + pi - asin((-r[j] + r[i]) / d);
                    low = norm(low), high = norm(high);
                    v.push_back({low + eps, 1});
                    v.push_back({high, -1});
                    if (low > high) tmp++;
                }
            }
        }
        sort(v.begin(), v.end());
        for (int j = 0; j < v.size(); ++j) {
            ans = max(ans, tmp);
            tmp += v[j].second;
        }
    }
    cout << n + ans * k + k * (k - 1) / 2 << '\n';
    return 0;
}