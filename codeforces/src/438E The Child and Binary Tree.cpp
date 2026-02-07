//
// Created by Psy.C on 2026/2/7.
//
/**
F[], G[], S[]: 用于多项式运算的数组
rev[]: NTT中用于位逆序置换的数组
c[], tmp[]: 临时数组
F[]: 存储多项式求逆的结果
G[]: 存储多项式开方的结果
S[]: 存储输入数据的统计结果

n: 变换长度（必须是2的幂）
a: 要变换的数组指针
f: 变换方向（1为正向，-1为反向）

((i & 1) * (n >> 1))
将i的最低位移到n的最高位
如果i是偶数：0 * (n>>1) = 0
如果i是奇数：1 * (n>>1) = n/2


w: 前半部分的索引
w + m: 后半部分的对应索引
g: 当前的旋转因子ω_k
t = a[w + m] * g: 计算要合并的值
a[w + m] = a[w] - t: 后半部分更新
a[w] = a[w] + t: 前半部分更新
+ mo防止负数取模

正向NTT
将系数表示转换为点值表示
用于快速多项式乘法
逆向NTT
将点值表示转换回系数表示
恢复原始多项式系数
时间复杂度
O(n log n)，其中n是变换长度
与FFT的关系
NTT是FFT在有限域上的等价形式
使用整数运算避免浮点误差
只能在特定模数下使用（如998244353）
蝶形运算的数学原理
对于长度为i的区间，将其分为前后两半，每一对元素进行如下变换：

A[w] = A[w] + ω^k * A[w+m]
A[w+m] = A[w] - ω^k * A[w+m]
这就是Cooley-Tukey算法的核心思想。


// 时域/系数表示：多项式 A(x) = a₀ + a₁x + a₂x² + ... + aₙ₋₁xⁿ⁻¹
A = [a₀, a₁, a₂, ..., aₙ₋₁]

// 频域/点值表示：在特定点的函数值
A(ω⁰), A(ω¹), A(ω²), ..., A(ωⁿ⁻¹)  （其中ω是单位根）

transform(N, a, 1);  // 从系数表示 → 点值表示（正向变换）

// 时域：A(x) * B(x) 需要 O(n²) 时间
// 频域：A(ωᵏ) * B(ωᵏ) 只需 O(1) 时间，总共 O(n) 时间
时域：C = A ⊗ B (卷积)    ←→    频域：C(ωᵏ) = A(ωᵏ) * B(ωᵏ) (点乘)
 */
#include <bits/stdc++.h>
using namespace std;

const int mo = 998244353;//NTT的基础质数 2^23 * 7 * 17 + 1
const int inv2 = 499122177;//2在模mo下的逆元（2^(-1) mod mo）
const int MAXN = 100000 + 10;

int n, m, x;
int F[MAXN * 4], G[MAXN * 4], S[MAXN * 4], rev[MAXN * 4], c[MAXN * 4], tmp[MAXN * 4];

int ksm(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1) res = (long long)res * x % mo;
		x = (long long)x * x % mo, y /= 2;
	}
	return res;
}

void transform(int n, int *a, int f) {
	for (int i = 0; i < n; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (n >> 1));
	//将数组按位逆序重新排列
	for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int i = 2; i <= n; i *= 2) {
		//当前长度的一半 3是原根
		int m = i >> 1, g1 = ksm(3, (mo - 1) / i);//单位根
		for (int j = 0; j < n; j += i) {//每次处理长度为i的区间
			//j: 每个长度为i区间的起始位置
			int g = 1;//当前旋转因子
			for (int w = j; w < j + m; w++, g = (long long)g * g1 % mo) {
				int t = (long long)a[w + m] * g % mo;//蝴蝶操作的临时值
				//更新后半部分 更新前半部分
				a[w + m] = (a[w] - t + mo) % mo, a[w] = (a[w] + t) % mo;
			}
		}
	}
	if (f == 1) return;//正向变换
	int now = ksm(n, mo - 2);//n的模逆元
	reverse(a + 1, a + n);//除了第0个元素
	for (int i = 0; i < n; i++) a[i] = (long long)a[i] * now % mo;
}

/**
 *
 * @param n 多项式的长度
 * @param a 输入多项式
 * @param b 输出多项式（a的逆）
 */
void getinv(int n, int *a, int *b) {
	//b[0]是a[0]的模逆元
	if (n == 1) { b[0] = ksm(a[0], mo - 2); return; }
	getinv((n + 1) >> 1, a, b);//递归计算前(n+1)/2项的逆
	int N = 1; while (N < n * 2) N *= 2;//大于等于2n的最小2的幂
	for (int i = 0; i < n; i++) c[i] = a[i];//复制a到c，并补0到长度N
	for (int i = n; i < N; i++) c[i] = 0;
	transform(N, c, 1), transform(N, b, 1);//对c和b进行正向NTT
	//牛顿迭代公式：B_new = B_old * (2 - A * B_old)
	for (int i = 0; i < N; i++) b[i] = (long long)b[i] * (2 - (long long)b[i] * c[i] % mo + mo) % mo;
	transform(N, b, -1);//执行逆NTT，清除超出范围的项
	for (int i = n; i < N; i++) b[i] = 0;
}

void getsqrt(int n, int *a, int *b) {
	if (n == 1) { b[0] = 1; return; }
	getsqrt((n + 1) >> 1, a, b);//递归计算前半部分的平方根
	int N = 1; while (N < n * 2) N *= 2;//计算NTT长度
	for (int i = 0; i < N; i++) tmp[i] = 0;
	//计算b的逆，转换到频域
	getinv(n, b, tmp), transform(N, tmp, 1);
	for (int i = 0; i < n; i++) c[i] = a[i];//复制a到c，转换b和c到频域
	for (int i = n; i < N; i++) c[i] = 0;
	transform(N, b, 1), transform(N, c, 1);
	for (int i = 0; i < N; i++) b[i] = (long long)(b[i] + (long long)c[i] * tmp[i] % mo) * inv2 % mo;
	transform(N, b, -1);
	for (int i = n; i < N; i++) b[i] = 0;
}

int main() {
	scanf("%d %d",&n, &m);
	//统计每个数的出现次数
	for (int i = 1; i <= n; i++) scanf("%d", &x), S[x]++;
	for (int i = 0; i <= m; i++) S[i] = (mo - 4 * S[i]) % mo;
	S[0]++, getsqrt(m + 1, S, G);//计算S的平方根，结果存到G
	G[0]++, getinv(m + 1, G, F);//计算G的逆，结果存到F
	for (int i = 1; i <= m; i++) printf("%d\n", F[i] * 2 % mo);
}