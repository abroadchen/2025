//
// Created by Psy.C on 2025/11/4.
//
/*
*重新定义getchar函数，实现快速输入优化：
使用大缓冲区(8MB)一次性读入大量数据
p1和p2是指向缓冲区的指针，p1指向当前读取位置，p2指向缓冲区末尾
 *N = 1000：分割点数
 *c：当前读取的字符
 *
*快速读取整数的函数：
第一个循环：跳过非数字字符，如果是负号则设置符号标志f=-1
第二个循环：读取数字字符并转换为整数，使用位运算优化(x<<3)+(x<<1)=x*10
返回带符号的结果
*快速读取浮点数的函数：
前两行同整数读取，处理整数部分
如果没有小数点，直接返回整数部分
如果有小数点，继续读取小数部分，逐位累加到结果中
 *
*(x1,y1)和(x2,y2)是线段两个端点
x和y是角度相关参数
res存储结果的最大值
*将线段分成N份(1000份)，遍历每一份：
u,v：在线段上插值得到的点坐标
t：该点相对于原点的角度(使用atan2函数)
d：角度差值
 *角度标准化，确保d在[0, 2π)范围内
*j：角度差的最小值除以y参数
k：点(u,v)到点(x1,y1)的距离
更新res为k/j的最大值
 *返回计算得到的最大值
 *
 *
*循环处理每个测试点：
读取测试点坐标(x,y)和参数(u,v)
调用solve函数计算结果，并添加到res向量中
*将结果按降序排序
添加一个0到结果末尾（防止越界）
读取一个索引值并输出对应位置的结果（保留10位小数）
 */
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
#include <cctype>
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin)),*p2=0,*p1++)
using namespace std;

const int N = 1000, M = 8888888;
const double pi = acos(-1);

char buf[M], *p1 = buf, *p2 = buf, c;
int read(int x=0, int f=1) {
    for (; !isdigit(c); c=getchar()) (c == '-') && (f = -1);
    for (; isdigit(c); c=getchar()) x = (x << 3) + (x << 1) + (c&15);
    return x * f;
}
double readf(double x=0, int f=1, double p=1) {
    for (; !isdigit(c); c=getchar()) (c == '-') && (f = -1);
    for (; isdigit(c); c=getchar()) x=x * 10 + (c&15);
    if (c != '.') return x * f;
    for (c = getchar(); isdigit(c); c=getchar()) x+=(p*=0.1)*(c^48);
    return x;
}


double solve(int x1, int y1, int x2, int y2, double x, double y) {
    double res(0);
    for (int i = 0; i <= N; ++i) {
        double u = (x1 * i + x2 * (N - i)) / 1000.0,
        v = (y1 * i + y2 * (N - i)) / 1000.0,
        t = atan2(v, u), d = t - x;
        while (d > 2 * pi) d -= 2 * pi;
        while (d < 0) d += 2 * pi;
        double j = min(d, 2 * pi - d) / y,
        k = hypot(x1 - u, y1 - v);
        res = max(res, k / j);
    }
    return res;
}

int main() {
    int x1 = read(), y1 = read(), x2 = read(), y2 = read();
    vector<double> res;
    int n = read();
    while (n--) {
        int x = read(), y = read();
        double u = readf(), v = readf();
        res.push_back(solve(x1 - x, y1 - y, x2 - x, y2 - y, u, v));
    }
    sort(res.begin(), res.end(), greater<double>());
    res.push_back(0);
    printf("%.10lf\n", res[read()]);
    return 0;
}