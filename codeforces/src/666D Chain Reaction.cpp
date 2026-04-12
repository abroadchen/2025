//
// Created by Psy.C on 2026/4/12.
//
/**
x[], y[]: 存储输入的坐标点
p[]: 用于排列的数组
mn: 记录最小代价，初始化为1e9
resx[], resy[]: 存储结果坐标
验证是否形成矩形：Y[0]和Y[1]应相等，Y[2]和Y[3]应相等，X[1]和X[2]应相等，X[3]和X[0]应相等
验证相邻边长度是否相等，(i+1)&3等价于(i+1)%4，确保循环访问
如果X[0]等于X[1]，说明矩形退化成线，返回无穷大
检查变换后的点是否至少有一个坐标与原始点相同
计算最大曼哈顿距离，即变换的代价

初始化结果数组和最小值
读取四个点的坐标
rv控制是否交换x,y坐标；p数组存储排列；do-while循环遍历所有排列
遍历16种状态掩码；定义lambda函数upd用于更新最优解
msk==10：特定的坐标重排
msk==0：计算理想矩形的纵坐标，使四个点构成一个矩形
处理特定掩码模式，根据位掩码确定哪些坐标的修改方式
next_permutation：生成下一个排列
交换x,y坐标，尝试另一种方向
如果最小代价过大，输出-1；否则输出最小代价和最终坐标


rv=0: 考虑正常坐标系下的情况
rv=1: 考虑交换x和y坐标后的情况（相当于旋转90度）
这样可以处理矩形的两种方向：水平放置和垂直放置
初始化排列数组p=[0,1,2,3]
枚举所有4! = 24种排列方式
这是为了找到哪4个输入点对应矩形的哪4个角
枚举0到15共16种状态掩码
每个掩码代表一种不同的约束条件或变换方式
Lambda函数用于更新最优解
如果找到更小的代价，就更新全局最小值和对应的结果坐标
注意这里根据rv值决定是否交换x,y坐标
特定的坐标重新分配模式
将点按某种规律重新排列以尝试构成矩形
计算理想的矩形上下边界
A是矩形的宽度
通过排序四个候选纵坐标，取中间值作为上下边界
设置上边两个点的纵坐标相同，下边两个点的纵坐标相同
根据掩码的位模式来决定如何构造矩形
~msk & 1检查第0位是否为0（即未被固定）
~msk >> 1 & 1检查第1位是否为0
通过这种方式，程序能处理各种约束条件下矩形的构造
交换每个点的x和y坐标
这样可以在下次外层循环中尝试矩形的另一种方向

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pb push_back
using namespace std;

template<typename T1, typename T2> void chkmax(T1 &x, T2 y) {if (x < y) x = y;}
int x[5], y[5], p[5], mn = 1e9, resx[5], resy[5];
int calc(int X[4], int Y[4], int P[4]) {
	if (Y[0] != Y[1] || Y[2] != Y[3] || X[1] != X[2] || X[3] != X[0]) return 1e9;
	for (int i = 0; i < 4; i++)
		if (abs(X[i] - X[(i + 1) & 3]) + abs(Y[i] - Y[(i + 1) & 3]) != abs(X[0] - X[1]))
			return 1e9;
	if (X[0] == X[1]) return 1e9;
	for (int i = 0; i < 4; i++) {
		int sum = (X[i] == x[P[i]]) + (Y[i] == y[P[i]]);
		if (sum == 0) return 1e9;
	}
	int mx = 0;
	for (int i = 0; i < 4; i++) chkmax(mx, abs(X[i] - x[P[i]]) + abs(Y[i] - y[P[i]]));
	return mx;
}
void solve() {
	memset(resx, 0, sizeof(resx)); memset(resy, 0, sizeof(resy)); mn = 1e9;
	for (int i = 0; i < 4; i++) scanf("%d%d", &x[i], &y[i]);
	for (int rv = 0; rv < 2; rv++) {
		for (int i = 0; i < 4; i++) p[i] = i;
		do {
			for (int msk = 0; msk < 16; msk++) {
				static int nwx[5], nwy[5];
				auto upd = [&](int cst) {
					if (mn > cst) {
						mn = cst;
						for (int i = 0; i < 4; i++) {
							if (!rv) resx[p[i]] = nwx[i], resy[p[i]] = nwy[i];
							else resx[p[i]] = nwy[i], resy[p[i]] = nwx[i];
						}
					}
				};
				for (int i = 0; i < 4; i++) nwx[i] = x[p[i]], nwy[i] = y[p[i]];
				if (msk == 10) {
					nwy[0] = y[p[1]]; nwx[1] = x[p[2]]; nwy[2] = y[p[3]]; nwx[3] = x[p[0]];
					upd(calc(nwx, nwy, p));
				} else if (msk == 0) {
					int A = x[p[1]] - x[p[0]];
					vector<int> vec; vec.pb(y[p[0]] - A); vec.pb(y[p[1]] - A); vec.pb(y[p[2]]); vec.pb(y[p[3]]);
					ranges::sort(vec); int dw = vec[0] + vec[3] >> 1, up = dw + A;
					nwy[0] = nwy[1] = up; nwy[2] = nwy[3] = dw;
					upd(calc(nwx, nwy, p));
				} else {
					//处理前两个位置未被固定的情况
					if ((~msk & 1) && (~msk >> 1 & 1)) {
						int A = abs(nwx[0] - nwx[1]);
						for (int i = 2; i <= 3; i++) if (msk >> i & 1) {
							nwx[i] = nwx[3 - i]; nwy[i ^ 1] = nwy[i];
							nwy[0] = nwy[1] = nwy[i] + A; nwx[i ^ 1] = nwx[3 - (i ^ 1)];
							break;
						}
						upd(calc(nwx, nwy, p));
					}
					//处理后两个位置未被固定的情况
					else if ((~msk >> 2 & 1) && (~msk >> 3 & 1)) {
						int A = abs(nwx[3] - nwx[2]);
						for (int i = 0; i <= 1; i++) if (msk >> i & 1) {
							nwx[i] = nwx[3 - i]; nwy[i ^ 1] = nwy[i];
							nwy[2] = nwy[3] = nwy[i] - A; nwx[i ^ 1] = nwx[3 - (i ^ 1)];
							break;
						}
						upd(calc(nwx, nwy, p));
					}
				}
			}
		} while (next_permutation(p, p + 4));
		for (int i = 0; i < 4; i++) swap(x[i], y[i]);
	}
	if (mn > 200000000) puts("-1");
	else {
		printf("%d\n", mn);
		for (int i = 0; i < 4; i++) printf("%d %d\n", resx[i], resy[i]);
	}
}
int main() {
	int qu; scanf("%d", &qu);
	while (qu--) solve();
	return 0;
}