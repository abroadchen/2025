//
// Created by Psy.C on 2026/3/21.
//
/**
圆心坐标(x1,y1)、半径r1和圆心坐标(x2,y2)、半径r2
计算两圆心之间的欧几里得距离
当两圆相离或恰好外切时，交集面积为0
当一个圆完全包含另一个圆时，交集面积就是较小圆的面积
输出精确到20位小数
a = acos((r1²+d²-r2²)/(2×r1×d))：第一个圆的扇形中心角的一半
b = acos((r2²+d²-r1²)/(2×r2×d))：第二个圆的扇形中心角的一半

扇形面积：θ × r² / 2（这里角度是半角，所以整体乘以2）
三角形面积：0.5 × r² × sin(2θ)
圆段面积：扇形面积 - 三角形面积
最终相交面积 = 第一个圆的圆段面积 + 第二个圆的圆段面积
时间复杂度：O(1)，空间复杂度：O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ld long double
using namespace std;
const ld pi = acos(-1.);

int main() {
    fast;
    ld x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    ld d = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    if (r1 + r2 <= d) {
        cout << "0.00000000000000000000\n";
        return 0;
    }
    if (r1 >= r2 + d || r2 >= r1 + d) {
        ld r = min(r1, r2), ans = pi*r*r;
        printf("%.20f\n", (double)ans);
        return 0;
    }
    ld a = acos((r1*r1+d*d-r2*r2)/2/r1/d),
            b = acos((r2*r2+d*d-r1*r1)/2/r2/d),
            ans = a*r1*r1-0.5*r1*r1*sin(a*2)+
                  (b*r2*r2-0.5*r2*r2*sin(b*2));
    printf("%.20f\n", (double)ans);
    return 0;
}