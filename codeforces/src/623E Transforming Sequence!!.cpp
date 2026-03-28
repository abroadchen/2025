//
// Created by Psy.C on 2026/3/27.
//
/**
定义复数结构体 实部x和虚部y
实现复数的四则运算和共轭操作
N: 数组大小
C: FFT的常量
M: 掩码（低15位）
L: 长度限制
fac: 阶乘数组
ifac: 阶乘逆元数组

初始化阶乘和阶乘逆元
c(n,m) 计算组合数 C(n,m)
初始化π值和位逆序数组
初始化单位根数组（用于FFT）
实现快速傅里叶变换
支持正向和反向变换
使用FFT实现高精度多项式乘法
通过拆分高低位避免精度问题
初始化辅助数组，将系数乘以2的幂


当mod为素数时，x的逆元为x^(mod-2) mod mod
friend: 友元函数，可以访问类的私有成员
两个复数相加，实部加实部，虚部加虚部
两个复数相减
复数乘法公式：(a+bi)(c+di) = (ac-bd) + (ad+bc)i
复数除以标量，实部虚部都除以该数
返回共轭复数，实部不变，虚部变号
const: 函数不会修改对象状态
重载/=运算符，将当前复数除以b
N=30005: 数组最大长度
C=16: FFT相关常数
M=(1<<15)-1: 掩码，二进制前15位全为1，用于分离高低位
L=(1<<C)+1: L=2^16+1，用于数组大小

fac[0]=ifac[0]=1;: 0! = 1, (0!)^-1 = 1
for(int i=1;i<=len;i++)fac[i]=mul(fac[i-1],i);: 计算阶乘，使用模乘
ifac[len]=Inv(fac[len]);: 计算最大阶乘的逆元
for(int i=len-1;i;i--)ifac[i]=mul(ifac[i+1],i+1);: 从后往前计算逆元
n<m?0:: 如果n<m，组合数为0
mul(fac[n],mul(ifac[m],ifac[n-m])): C(n,m) = n! / (m!(n-m)!)
rev[L]: FFT中的位逆序数组
lim: FFT长度
计算位逆序排列
(rev[i>>1]>>1): i>>1的位逆序右移一位
((i&1)*(lim>>1)): i的最低位移到最高位
这样得到i的位逆序表示

plx *w[C+1];: 定义指针数组，存储各层单位根
for(int i=1;i<=C;i++)w[i]=new plx[1<<(i-1)];: 为每层分配内存
w[C][i]=plx(cos(pi*i/l),sin(pi*i/l));: 在最深层预计算单位根 w_n = cos(2π/n) + i*sin(2π/n)
w[i][j]=w[i+1][j<<1];: 从深层到浅层传递单位根，利用倍增性质
if(i>rev[i])swap(f[i],f[rev[i]]);: 按位逆序重新排列数组
mid=1: 当前段长度的一半
l=1: 层数索引
for(int i=0;i<lim;i+=mid<<1): 遍历每一对长度为mid的子段
a0=f[i+j],a1=f[i+j+mid]*w[l][j]: 蝴蝶操作的两个输入
f[i+j]=a0+a1,f[i+j+mid]=a0-a1: 蝴蝶操作公式
如果是逆变换，先反转数组（除了第一个元素）
再除以长度lim
static: 静态数组，只分配一次内存
将整数A[i]和B[i]分成高低两部分
A[i]&M: 低15位
A[i]>>15: 高15位
将超出范围的位置零

这部分实现共轭对称的优化
j=(lim-i)&(lim-1): 获取对称位置
通过共轭对称性质同时处理两个点
计算卷积结果的实部和虚部

将浮点数结果转回整数
重新组合高低位得到最终结果
将数组a的第i项乘以2^(i*ii)，使用快速幂计算2的幂

初始化单位根和阶乘
设置初始数组为阶乘的逆元
计算FFT需要的长度
lim<<=1: 左移一位，相当于乘以2
初始化位逆序数组
快速幂的迭代过程
n>>=1: n除以2
n&1: 检查n的最低位
如果n是奇数，就将当前的a乘到结果res中
i<<=1: i乘以2
将结果乘以相应的阶乘
计算最终结果，使用组合数进行线性组合
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int mod = 1e9+7;
inline int mul(int a,int b){static ll r;r=1ll*a*b;return r>=mod ? r%mod :r; }
inline void Add(int &a,int b){(a+=b)>=mod?(a-=mod):0;}
inline void Mul(int &a,int b){static ll r;r=1ll*a*b;a=(r>=mod)? r%mod : r; }
inline int ksm(int a,int b,int res=1){for(;b;b>>=1,Mul(a,a)) b&1&&(Mul(res,a),1);return res;}
inline int Inv(int x){return ksm(x,mod-2);}
struct plx{
	double x,y;
	plx(double x=0, double y=0) : x(x), y(y) {}
	friend plx operator+(const plx& a, const plx& b) {
		return {a.x + b.x, a.y + b.y};
	}
	friend plx operator-(const plx& a, const plx& b) {
		return {a.x - b.x, a.y - b.y};
	}
	friend plx operator*(const plx& a, const plx& b) {
		return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x};
	}
	friend plx operator/(const plx& a, const int& b) {
		return {a.x / b, a.y / b};
	}
	plx conj() const { return {x, -y}; }
	void operator/=(const int& b) { *this = *this / b; }
};
constexpr int N=30005,C=16,M=(1<<15)-1,L=(1<<C)+1;
int fac[N],ifac[N];
inline void init_inv(int len=N-5){
	fac[0]=ifac[0]=1;
	for(int i=1;i<=len;i++)fac[i]=mul(fac[i-1],i);
	ifac[len]=Inv(fac[len]);
	for(int i=len-1;i;i--)ifac[i]=mul(ifac[i+1],i+1);
}
inline int c(int n,int m){return n<m?0:mul(fac[n],mul(ifac[m],ifac[n-m]));}
double pi=acos(-1);
int rev[L],lim;
ll n;int k;
inline void init_rev(int lim){
	for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)*(lim>>1));
}
plx *w[C+1];
inline void init_w(){
	for(int i=1;i<=C;i++)w[i]=new plx[1<<(i-1)];
	for(int i=0,l=(1<<(C-1));i<l;i++)w[C][i]=plx(cos(pi*i/l),sin(pi*i/l));
	for(int i=C-1;i;i--)
	for(int j=0,l=1<<(i-1);j<l;j++)w[i][j]=w[i+1][j<<1];
}
inline void fft(plx *f,int lim,int kd){
	for(int i=0;i<lim;i++)if(i>rev[i])swap(f[i],f[rev[i]]);
	plx a0,a1;
	for(int mid=1,l=1;mid<lim;mid<<=1,l++)
	for(int i=0;i<lim;i+=mid<<1)
	for(int j=0;j<mid;j++)
	a0=f[i+j],a1=f[i+j+mid]*w[l][j],f[i+j]=a0+a1,f[i+j+mid]=a0-a1;
	if(kd==-1){
		reverse(f+1,f+lim);
		for(int i=0;i<lim;i++)f[i]/=lim;
	}
}
inline void mul(int *A,int *B,int *ret){
	static plx a[L],b[L],c[L],d[L],da,db,dc,dd;
	for(int i=0;i<=k;i++)a[i]=plx(A[i]&M,A[i]>>15),b[i]=plx(B[i]&M,B[i]>>15);
	for(int i=k+1;i<=lim;i++)a[i]=b[i]=plx();//将超出范围的位置零
	fft(a,lim,1),fft(b,lim,1);//对两个多项式分别进行FFT
	for(int i=0;i<lim;i++){
		int j=(lim-i)&(lim-1);
		da=(a[i]+a[j].conj())*plx(0.5,0);
		db=(a[j].conj()-a[i])*plx(0,0.5);
		dc=(b[i]+b[j].conj())*plx(0.5,0);
		dd=(b[j].conj()-b[i])*plx(0,0.5);
		c[i]=(da*dc)+((da*dd)*plx(0,1));
		d[i]=(db*dd)+((db*dc)*plx(0,1));
	}
	fft(c,lim,-1),fft(d,lim,-1);//对结果进行逆FFT
	for(int i=0;i<=k;i++){
		ll da=(ll)(d[i].x+0.5)%mod,db=(ll)(d[i].y+0.5)%mod,dc=(ll)(c[i].y+0.5)%mod,dd=(ll)(c[i].x+0.5)%mod;
		ret[i]=((da<<30)+((db+dc)<<15)+dd)%mod;
	}
}
int tmp[N];
inline void init(int *a,int ii){
	for(int i=0;i<=k;i++)tmp[i]=mul(a[i],ksm(2,1ll*i*ii%(mod-1)));
}
int a[N],res[N];
int main(){
	fast;
	cin>>n>>k;
	if(n>k)return puts("0"),0;
	init_w(),init_inv();
	for(int i=1;i<=k;i++)res[i]=a[i]=ifac[i];
	lim=1,n--;
	while(lim<(k+1)*2)lim<<=1;init_rev(lim);
	for(int i=1;n;init(a,i),mul(tmp,a,a),i<<=1,n>>=1)if(n&1){
		init(res,i),mul(tmp,a,res);
	}
	for(int i=0;i<=k;i++)Mul(res[i],fac[i]);
	int ret=0;
	for(int i=0;i<=k;i++)Add(ret,mul(c(k,i),res[i]));
	cout<<ret;
	return 0;
}