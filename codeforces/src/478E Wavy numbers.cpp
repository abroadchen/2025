//
// Created by Psy.C on 2026/2/16.
//
/**
预处理：O(10^7)（生成所有锯齿数）
查询：O(k)（在预处理结果中查找）

to[]快速定位模n的值
第一维：0-9，表示低位部分的第一个数字
第二维：0或1，表示类型（0表示该位小于前一位，1表示该位大于前一位）
第三维：存储具体的低位数字

id: 用于映射的ID计数器
to[M]: 模运算到ID的映射数组
cnt[10][2][N]: 计数数组，记录各种情况的数量
dig[10]: 存储当前数字的各个数位，索引1-7对应数字的各个位


 */
#include <bits/stdc++.h>
#define ll long long
#define N 850000
#define M 10000000
#define inf 100000000000000LL
using namespace std;

ll n, k;//模数n，查询第k个数
int tothigh;//高位部分总数
int anshigh[N];//存储高位部分
vector<int> anslow[10][2];//存储低位部分，[首位数字][类型]
int id, to[M], cnt[10][2][N];//映射和计数数组
int dig[10];//当前数字的各位

///将当前数字转换为高位部分并存储
void get_high(const int bit) {
	int num = 0, i = bit;//i从当前位开始
	while (i) {
		num = num * 10 + dig[i];//将dig[i]添加到num末尾（从高位到低位）
		i--;//处理下一位
	}
	anshigh[tothigh++] = num;//存入数组
}

void find_high(const int bit) {
	for (int i = 0; i <= 9; i++) {
		if (i != dig[bit - 1]) {//当前位不能与前一位相同
			///是前两位或满足锯齿条件
			///当前位比前一位大，且前一位比前前位大
			///当前位比前一位小，且前一位比前前位小
			if (bit <= 2 || (bit > 2 && ((i > dig[bit - 1] && dig[bit - 2] > dig[bit - 1])
				|| (i < dig[bit - 1] && dig[bit - 2] < dig[bit - 1])))) {
				dig[bit] = i;//设置当前位为i
				if (i) get_high(bit);//存储
				if (bit < 7) find_high(bit + 1);//没到第7位，继续递归
			}
		}
	}
}

void get_low() {
	int num = 0, i = 7;//从第7位开始构造数字
	while (i) {
		num = num * 10 + dig[i];
		i--;
	}
	if (dig[7] < dig[6]) {//第7位小于第6位
		anslow[dig[7]][0].push_back(num);//存入类型0（递减）
		if (!to[num % n]) to[num % n] = ++id;//如果该模值未映射，建立映射
		cnt[dig[7]][0][to[num % n]]++;//增加计数
	} else {//存入类型1（递增）
		anslow[dig[7]][1].push_back(num);
		if (!to[num % n]) to[num % n] = ++id;
		cnt[dig[7]][1][to[num % n]]++;
	}
}

///递归生成低位锯齿数
void find_low(const int bit) {
	for (int i = 0; i <= 9; i++) {
		if (i != dig[bit - 1]) {
			if (bit <= 2 || (bit > 2 && ((i > dig[bit - 1] && dig[bit - 2] > dig[bit - 1])
				|| (i < dig[bit - 1] && dig[bit - 2] < dig[bit - 1])))) {
				dig[bit] = i;
				if (bit == 7) get_low();
				else  find_low(bit + 1);
			}
		}
	}
}

bool check(ll x) {
	int a = x % 10; x /= 10;//获取最后一位，x去掉最后一位
	int b = x % 10; x /= 10;//获取倒数第二位
	while (x) {
		const int c = x % 10; x /= 10;//获取当前位，x去掉当前位
		if ((b > a && b > c) || (b < a && b < c)) {}//满足锯齿条件
		else return false;
		a = b;//更新a和b为下一轮比较做准备
		b = c;
	}
	return true;//所有位都满足条件
}

int main() {
	scanf("%lld%lld", &n, &k);
	dig[0] = -1;//避免边界问题
	find_high(1); find_low(1);//生成高低位部分
	sort(anshigh, anshigh + tothigh);//对高位部分排序
	for (int i = 0; i < tothigh; i++) {
		if (anshigh[i] % n == 0) {//高位部分本身就是n的倍数
			k--;
			if (!k) {//k变为0
				printf("%d\n", anshigh[i]);
				return 0;
			}
		}
	}
	if (n >= M) {
		for (ll i = n; i <= inf; i += n) {//枚举n的倍数
			if (check(i)) {//验证是否为锯齿数
				k--;
				if (!k) {
					printf("%lld\n", i);
					return 0;
				}
			}
		}
	} else
		for (int i = 0; i < tothigh; i++) {
			///计算需要的低位部分的模值
			const int r = to[(n - (ll) anshigh[i] * M % n) % n];
			if (!r) continue;//没有这样的低位部分
			if (anshigh[i] < 10) {//处理一位高位的情况
				for (int j = 0; j <= 9; j++) {
					if (j == anshigh[i]) continue;
					if (j > anshigh[i]) {//低位首数字大于高位数字
						if (cnt[j][1][r]) {
							if (k > cnt[j][1][r]) k -= cnt[j][1][r];//k大于当前类型的数量
							else {
								ranges::sort(anslow[j][1]);
								for (const int it : anslow[j][1]) {
									if (to[it % n] == r) {
										k--;
										if (!k) {
											printf("%d%07d\n", anshigh[i], it);
											return 0;
										}
									}
								}
							}
						}
					} else {
						if (cnt[j][0][r]) {
							if (k > cnt[j][0][r]) k -= cnt[j][0][r];
							else {
								ranges::sort(anslow[j][0]);
								for (const int it : anslow[j][0]) {
									if (to[it % n] == r) {
										k--;
										if (!k) {
											printf("%d%07d\n", anshigh[i], it);
											return 0;
										}
									}
								}
							}
						}
					}
				}
			} else {//处理多位高位的情况
				if (anshigh[i] % 10 > anshigh[i] / 10 % 10) {//最后两位是否满足锯齿条件
					for (int j = 0; j < anshigh[i] % 10; j++) {//遍历可能的低位首数字
						if (cnt[j][0][r]) {
							if (k > cnt[j][0][r]) k -= cnt[j][0][r];
							else {
								ranges::sort(anslow[j][0]);
								for (const int it : anslow[j][0]) {
									if (to[it % n] == r) {
										k--;
										if (!k) {
											printf("%d%07d\n", anshigh[i], it);
											return 0;
										}
									}
								}
							}
						}
					}
				} else {
					for (int j = anshigh[i] % 10 + 1; j <= 9; j++) {
						if (cnt[j][1][r]) {
							if (k > cnt[j][1][r]) k -= cnt[j][1][r];
							else {
								ranges::sort(anslow[j][1]);
								for (const int it : anslow[j][1]) {
									if (to[it % n] == r) {
										k--;
										if (!k) {
											printf("%d%07d\n", anshigh[i], it);
											return 0;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	printf("-1\n");
	return 0;
}