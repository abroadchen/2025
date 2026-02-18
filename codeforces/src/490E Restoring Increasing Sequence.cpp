//
// Created by Psy.C on 2026/2/18.
//
/**
w[M]: 存储十进制权重的数组
n: 输入的字符串数量
s[N][M]: 二维字符数组，存储输入的字符串
lst = 0记录上一个转换后的数值
now: 存储当前字符串中确定数字部分的数值
cnt: 统计问号('?')的数量
(s[i][j]&15) 将字符转换为数字(0-9)
w[len-j] 是对应位置的权重
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5+1, M = 10;
int w[M], n;
char s[N][M];
int main() {
    w[0] = 1;//个位权重
    for (int i = 1; i <= 8; ++i) w[i] = w[i-1]*M;//w[1]=10, w[2]=100, w[3]=1000
    scanf ("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);//从第2个位置开始存储
    for (int i = 1, lst = 0; i <= n; ++i) {
        int len = strlen(s[i] + 1), now = 0, cnt = 0;
        for (int j = 1; j <= len; ++j) {
            if (s[i][j] != '?') now += (s[i][j]&15)*w[len-j];
            else ++cnt;
        }
        if (!cnt && lst > now) {//没有问号且上一个值大于当前值
            puts("NO");
            return 0;
        }
        int l = s[i][1] == '?' ? w[cnt-1] : 0, r = w[cnt]-1, ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1, tmp = mid, sum = now;
            for (int j = len; j >= 1; --j) if (s[i][j] == '?') {
                sum += tmp%10*w[len-j];
                tmp /= 10;
            }
            if (sum > lst) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        if (ans == -1) { puts("NO"); return 0; }
        for (int j = len; j >= 1; --j) if (s[i][j] == '?') {//找到的最佳替换方案填入问号位置
            s[i][j] = ans%10|48;//将数字转换回字符
            now += (ans%10)*w[len-j];
            ans /= 10;
        }
        lst = now;//设为当前值供下次比较使用
    }
    puts("YES");
    for (int i = 1; i <= n; ++i) puts(s[i] + 1);
    return 0;
}