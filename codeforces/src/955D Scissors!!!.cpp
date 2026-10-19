//
// Created by Psy.C on 2026/10/19.
//
/**
自定义字符串类，用 char dat[N] 定长数组存，len 记长度。

sz() 返回长度；
rev() 反转内容（在 s/t 上原地反转，用于求后缀匹配）；
重载 operator[] 支持下标访问（const / 非 const 两个版本）
Z 算法：z[i] = s1 从位置 i 开始的子串和 s2 前缀的最大公共长度。

n1 = s1 长度；n2 = 匹配上限 = min(s2长度, z_limit)（最多只匹配到 z_limit，通常是 k，因为窗口长度限制为 k）。
z[0] 初始直接暴力匹配 s1 与 s2 的开头
标准 Z 算法线性部分：

维护已匹配区间 [l, r]；
若 i < r，利用已知的 Z 值 z_s2[i-l] 初始化 z[i]（这里是 min(r-i, z_s2[i-l])，z_s2 是 s2 自身的 Z 数组，用于复用）；
然后暴力扩展，同时保证不超过 n2（匹配长度上限）和 i+z[i] < n1（不越出 s1）；
更新区间。
注意此处的巧妙点：传入 z_s2（s2 的 Z 数组）‍，使得 s1 与 s2 匹配时能借用 s2 自身前缀的边界信息来加速——这是"两串 Z 匹配（s1 挂在 s2 上）"的经典写法
普通并查集，带路径压缩。用于区间覆盖时跳过已访问位置（类似 union-find 优化区间赋值，使每个位置只被处理一次，整体 O(n α(n))）

读入：n = s 的长度，m = t 的长度，k = 窗口长度（每次匹配片段的长度上限）
先对 t 自身做 Z 算法（z_t = t 的 Z 数组），用于后续复用；
再对 s 和 t 做匹配得到 z_pre：z_pre[i] = s 从 i 开始与 t 前缀的最大匹配长度（上限 k
把 s、t 反转；
重新求 t 的 Z、再做 s 与 t 匹配得到 z_suf（此时是对反转后的串）；
再把 z_suf 反转回来 → z_suf[i] = s 中位置 i 结尾的、与 t 后缀匹配的长度（上限 k）。
于是：

z_pre[i]：以 s[i] 起头，向前匹配 t 前缀的长度；
z_suf[i]：以 s[i] 结尾，向后（即匹配 t 的末尾方向）的长度

若 t1 == -1 输出 No；
否则输出 Yes，并输出两个窗口起点（1-indexed）：t1-k+1+1（即 t1-k+2）和 s2+1
情况一：m ≤ k（模式串本身不超过一个窗口）
当 m ≤ k 时，整个 t 可以被一个窗口覆盖。遍历 s 中每个位置 i，若 z_pre[i]==m（s 从 i 起完整匹配 t）：

找一个能包住这段匹配的长度 k 窗口（左端 start_L）；
再尝试让另一个窗口也放得下，试探左右两侧，输出两个窗口起点。
为什么要找两个窗口？ —— 题意应是恰好选两个窗口（都必须给出），所以即便 m≤k 也要输出两个位置。于是它在找到第一个完整匹配后，再尝试安排第二个窗口的位置（放在前面或后面，只要不越界）
情况二：m > k（需要两个窗口拼起来）

这是主体。思路：用两个窗口，一个匹配 t 的前缀（长度 a ≤ k），一个匹配 t 的后缀（长度 b ≤ k），且满足 a + b = m（a = 某个 z_pre，b = m - a 由 z_suf 提供）。

关键：用 z_suf 预处理"每个后缀长度对应的窗口起点"
对每个 s 位置 i（它表示后缀匹配的起始处），后缀匹配长度为 z_suf[i]。我们希望：对于某个需要的后缀长度 val，找它对应的"窗口起点"。

oper[i] 存区间 [l, r]：r = z_suf[i]（最大可取后缀长度），l 是某种下界。意思是"从 i 出发能匹配 t 后缀的长度范围"。

区间覆盖：对每个后缀长度 val，记录能取到的最大"后缀窗口起点"
mx[i] 记录：当需要的 t 后缀长度为 i 时，能取到的"最靠后（最大）的窗口起点"（初始 -1 表示没有）。
用并查集跳过已填的位置，对每个 oper[x] 的区间 [l, r] 做赋值 mx = x。
外层 x 从 n-1 倒序遍历，保证后处理的 x 更大，覆盖更靠后的值——这样每个 mx[i] 存的是满足"后缀长度可取 i"的最大起点（贪心：起点越靠后越好）。
含义：mx[b] = 若第二个窗口需匹配 t 的后缀、且其覆盖长度可达 b，则后缀窗口起点最大为 mx[b]

第一段：对每个 i，z_pre[i] 是前缀窗口匹配长度（s 从 i 起匹配 t 前缀的长度 a）。

检查边界条件：前缀窗口能"包住"且长度合理（z_pre[i] <= k），剩下的 m - z_pre[i] 是要由后缀补的 b，要求 b <= k。
然后查 mx[m-z_pre[i]]（后缀长度为 b 时的最优后缀窗口起点），若存在（≠-1）且两个窗口不重叠（后缀窗口起点 > 前缀窗口终点，即 mx[b]-b+1 > i+a-1），则找到答案，输出两个窗口起点。
Ans 第一个参数 i+a-1 是前缀窗口终点；mx[b]-b+1 是后缀窗口起点。
第二段：把满足特定边界条件的前缀长度 k-1-i+1 压入 arr——这似乎是前缀窗口起点恰好卡在最左 k-1 内的候选（为下面最后兜底判断用）。
对于 arr 中的每个候选前缀长度 z，检查后缀长度 m-z 是否可行，若两个窗口不重叠则输出（前缀窗口起点固定为 k-1）
找不到则输出 No



问题（重构）：给出文本串 s（长 n）、模式串 t（长 m），以及窗口长度 k。判断能否找到两个长度为 k 的窗口（位置可重叠，each 覆盖 s 中一段），使得：

第一个窗口匹配 t 的一段前缀（长度 a ≤ k，窗口内连续）；
第二个窗口匹配 t 的一段后缀（长度 b ≤ k）；
满足 a + b = m（两段正好拼出整个 t）；
两个窗口互不重叠（在 s 中的位置不相交）。
方法：

Z 算法双向求 z_pre（前缀匹配）与 z_suf（后缀匹配），匹配长度上限均为 k；
用并查集优化的区间赋值，预处理 mx[b] = 后缀匹配长度可达 b 时的最大窗口起点；
遍历每个前缀匹配，用 mx 尝试与后缀匹配组合，满足 a+b=m 且不重叠即得解；
m≤k 时有特判（单窗口可覆盖）。
复杂度：O((n+m)·α(n)) 左右，Z 算法 O(n+m)，覆盖 O(n α(n))。
 */
#include <bits/stdc++.h>
#define ii pair<int,int>
using namespace std;

constexpr int N = 5e5+5;

struct str {
    char dat[N];
    int len;
    int sz() const { return len; }
    void rev() { reverse(dat, dat+len); }
    char &operator[](const int& x) { return dat[x]; }
    char operator[](const int& x) const { return dat[x]; }
};

void z_algorithm(const str &s1, const str &s2, vector<int> &z, const vector<int> &z_s2, const int &z_limit){
	const int n1 =s1.sz(), n2 =min(s2.sz(), z_limit);
	while(z[0] < n2 && s1[z[0]] == s2[z[0]])
		++z[0];
	for(int i =1, l =0, r =0; i < n1; ++i){
		if(i < r)
			z[i] =min(r-i, z_s2[i-l]);
		while(z[i] < n2 && i+z[i] < n1 && s1[i+z[i]] == s2[z[i]])
			++z[i];
		if(r < i+z[i])
			l =i, r =i+z[i];
	}
}

struct djs {
    vector<int> fa;
    djs(const int& n) {
        fa.resize(n);
        for (int i = 0; i < n; ++i) fa[i] = i;
    }
    int find(const int& x) {
        if (x == fa[x]) return x;
        return fa[x] = find(fa[x]);
    }
    void merge(int x, int y) {
        x = find(x); y = find(y);
        fa[x] = y;
    }
};


inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

void read_str(str& s) {
    char ch = getchar();
    while (ch < 'a' && ch > 'z') ch = getchar();
    s.len = 0;
    while (ch >= 'a' && ch <= 'z') s[s.len++] = ch, ch = getchar();
}

int main() {
    int n =rd(), m =rd(), k =rd();
	str s, t; read_str(s), read_str(t);

	vector<int> z_pre(n, 0), z_suf(n, 0), z_t(m, 0);
	z_algorithm(t, t, z_t, z_t, k);
	z_algorithm(s, t, z_pre, z_t, k);
	s.rev(), t.rev();
	z_t.assign(m, 0);
	z_algorithm(t, t, z_t, z_t, k);
	z_algorithm(s, t, z_suf, z_t, k);
	ranges::reverse(z_suf);

	auto Ans =[&](const int &t1, const int &s2){
		if(t1 == -1)
			putchar('N'), putchar('o');
		else{
			putchar('Y'), putchar('e'), putchar('s'), putchar('\n');
			write(t1-k+1 +1), putchar(' '), write(s2 +1);
		}
		return 0;
	};

	if(m <= k)
		for(int i =0; i < n; ++i)
			if(z_pre[i] == m){
				int start_L =max(0, (i+z_pre[i]-1) -k+1), start_R =start_L+k;
				int start_R2 =min(i, (n-1)-k+1), start_L2 =(start_R2-1)-k+1;
				if(start_R+k-1 <= n-1)
					return Ans(start_L+k-1, start_R);
				if(start_L2 >= 0)
					return Ans(start_L2+k-1, start_R2);
			}

	vector<vector<ii>> oper(n);
	for(int i =0; i < n; ++i){
		int l =max(1, i-min(i, (n-1)-k+1)+1), r =z_suf[i];
		if(l <= r)
			oper[i].emplace_back(l, r);
	}
	vector mx(n+1, -1);
	djs DS(n+1);
	auto modify =[&](const int &l, const int &r, const int &val){
		for(int i =DS.find(l); i <= r; DS.merge(i, i+1), i =DS.find(i)){
			if(mx[i] == -1)
				mx[i] =val;
		}
	};
	for(int x =n-1; x >= 0; --x)
		for(auto [fst, snd]:oper[x])
			modify(fst, snd, x);

	vector<int> arr; arr.reserve(n);
	for(int i =0; i < n; ++i){
		if((i+z_pre[i]-1) >= k && z_pre[i] <= k && m-z_pre[i] <= k)
			if(mx[m-z_pre[i]] != -1 && mx[m-z_pre[i]]-(m-z_pre[i])+1 > i+z_pre[i]-1)
				return Ans(i+z_pre[i]-1, mx[m-z_pre[i]]-(m-z_pre[i])+1);

		if(i <= k-1 && i+z_pre[i]-1 >= k-1)
			arr.push_back(k-1-i+1);
	}

	for(int z:arr)
		if(z <= k && m-z <= k)
			if(mx[m-z] != -1 && mx[m-z]-(m-z)+1 > k-1)
				return Ans(k-1, mx[m-z]-(m-z)+1);

	return Ans(-1, -1);
}