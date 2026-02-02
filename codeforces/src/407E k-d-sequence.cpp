//
// Created by Psy.C on 2026/2/1.
//
/**
* 时间复杂度：O(N log N)
空间复杂度：O(N)

mn[MS]：线段树数组，存储区间最小值
tg[MS]：懒惰标记数组，用于区间更新优化
static：静态局部变量，避免重复创建销毁
B[MN]：用于排序的副本
C[MN]：离散化后的数组
Lst[MN]：记录每个值最后出现位置
stk1[MN]：单调递减栈（最大值栈）
stk2[MN]：单调递增栈（最小值栈）

unique：去重函数，将相邻重复元素移到末尾
返回去重后数组的结束位置
M：去重后不同值的数量
C[i]：A[i]在去重数组B中的排名（离散化值）

MinL：当前允许的最左端点
tp1：栈1的栈顶指针
tp2：栈2的栈顶指针

弹出栈顶元素直到A[stk1[tp1]] > A[i]
对区间[stk1[tp1-1]+1, stk1[tp1]]加上A[i] - A[stk1[tp1]]
弹出栈顶元素直到A[stk2[tp2]] < A[i]
对区间[stk2[tp2-1]+1, stk2[tp2]]加上A[stk2[tp2]] - A[i]

N：数组长度
K：阈值参数
D：分组参数
A[MN]：原数组
R[MN]：余数数组
B[MN]：临时数组
t：B数组当前大小

mxl：最大长度
lst：上一个元素值
len：当前长度
ans：答案起始位置

tp1 - 栈顶指针
tp1：单调栈stk1的栈顶指针
指向栈中元素的数量
tp1=0表示栈为空
2. stk1[tp1] - 栈顶元素
stk1：单调递减栈（存储数组A的索引）
stk1[tp1]：栈顶元素，即数组A的一个索引
3. A[stk1[tp1]] - 实际值
A：原输入数组
A[stk1[tp1]]：原数组A中对应栈顶索引位置的值



 */
#include <cstdio>
#include <algorithm>

const int MN = 200005;//数组最大长度
const int MS = 1 << 19 | 7;//线段树大小

#define li (i << 1)//左子节点
#define ri (i << 1 | 1)//右子节点
#define mid ((l + r) >> 1)
#define ls li, l, mid//左/右子树参数
#define rs ri, mid + 1, r
int mn[MS], tg[MS];//节点i的最小值 懒惰标记（区间更新标记）
//给节点i加上值x
inline void P(int i, int x) { mn[i] += x, tg[i] += x; }
//下推懒惰标记
inline void pd(int i) { if (tg[i]) P(li, tg[i]), P(ri, tg[i]), tg[i] = 0; }
void Build(int i, int l, int r) {
	mn[i] = tg[i] = 0;//初始化节点值和懒惰标记
	if (l == r) return ;
	Build(ls), Build(rs);
}
//将[a,b]区间所有元素加上x
void Mdf(int i, int l, int r, int a, int b, int x) {
	if (r < a || b < l) return ;//无交集
	if (a <= l && r <= b) return P(i, x);//完全包含，直接更新
	pd(i), Mdf(ls, a, b, x), Mdf(rs, a, b, x);//下推标记并递归修改
	mn[i] = std::min(mn[li], mn[ri]);//更新当前节点的最小值
}
//在[a,b]中找到第一个≤x的位置
int Qur(int i, int l, int r, int a, int b, int x) {
	if (r < a || b < l || mn[i] > x) return -1;//无交集或最小值超过阈值
	if (l == r) return l;//叶子节点，返回位置
	pd(i);
	int lpos = Qur(ls, a, b, x);
	return ~lpos ? lpos : Qur(rs, a, b, x);//如果左子树找到则返回，否则查询右子树
}

int Ans, MaxLen;
//全局答案（起始位置） 全局最大长度
/**
 *
 * @param A 输入数组
 * @param N 数组长度
 * @param K 阈值参数
 * @param offset 偏移量（原始索引偏移）
 */
inline void Solve(int *A, int N, int K, int offset) {
	if (N <= MaxLen) return ;//当前长度不大于已知最大长度
	static int B[MN], C[MN], Lst[MN], stk1[MN], stk2[MN];//值C[i]最后一次出现的位置
	for (int i = 1; i <= N; ++i) B[i] = A[i];//将原数组A复制到B，用于排序
	std::sort(B + 1, B + N + 1);
	int M = std::unique(B + 1, B + N + 1) - B - 1;//将相邻重复元素移到末尾
	for (int i = 1; i <= N; ++i)
		C[i] = std::lower_bound(B + 1, B + M + 1, A[i]) - B;//A[i]离散化后的值
	for (int i = 1; i <= M; ++i) Lst[i] = 0;
	int MinL = 1, tp1 = 0, tp2 = 0;//当前允许的最左端点
	Build(1, 1, N);//构建线段树，节点1对应区间[1, N]
	for (int i = 1; i <= N; ++i) {
		MinL = std::max(MinL, Lst[C[i]] + 1);//更新最左端点（避免重复值）
		Lst[C[i]] = i;//记录当前值最后出现位置
		for (; tp1 && A[stk1[tp1]] <= A[i]; --tp1)//维护单调递减栈（最大值处理）
			Mdf(1, 1, N, stk1[tp1 - 1] + 1, stk1[tp1], A[i] - A[stk1[tp1]]);
		for (; tp2 && A[stk2[tp2]] >= A[i]; --tp2)//维护单调递增栈（最小值处理）
			Mdf(1, 1, N, stk2[tp2 - 1] + 1, stk2[tp2], A[stk2[tp2]] - A[i]);
		stk1[++tp1] = stk2[++tp2] = i;//将当前索引i压入两个栈
		Mdf(1, 1, N, i, i, i);//在位置i加上i的值
		int lpos = Qur(1, 1, N, MinL, i, K + i);//查询[MinL, i]区间内≤K+i的第一个位置
		if (~lpos && MaxLen < i - lpos + 1) {//lpos!=-1
			MaxLen = i - lpos + 1;//更新最大长度和答案
			Ans = lpos + offset;
		}
	}
}

int N, K, D;
int A[MN], R[MN], B[MN], t;

int main() {
	scanf("%d%d%d", &N, &K, &D);
	for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
	if (D == 0) {//找最长连续相同元素
		int mxl = 1, lst = A[1], len = 1, ans = 1;
		for (int i = 2; i <= N; ++i) {
			if (A[i] == lst) ++len;
			else len = 1, lst = A[i];
			if (len > mxl) mxl = len, ans = i - mxl + 1;
		}
		printf("%d %d\n", ans, ans + mxl - 1);
		return 0;
	}
	for (int i = 1; i <= N; ++i) R[i] = (A[i] % D + D) % D;
	for (int i = 1; i <= N; ++i) {//按余数相同的连续段分组处理
		B[++t] = (A[i] - R[i]) / D;
		if (i == N || R[i] != R[i + 1])
			Solve(B, t, K, i - t), t = 0;//处理当前组，清空B数组
	}
	printf("%d %d\n", Ans, Ans + MaxLen - 1);//起始和结束位置
	return 0;
}