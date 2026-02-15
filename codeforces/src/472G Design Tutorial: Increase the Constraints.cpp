//
// Created by Psy.C on 2026/2/14.
//
/**
N：数组大小（200010）
B：块大小（5000）
C：块的数量（N/B+10）
pi：圆周率
TOP=20：最大位数
N=(1<<18)+10：FFT数组大小
A[],B[]：FFT的输入数组
rev[]：位逆序置换数组
vis[]：访问标记数组
len：FFT的长度

n,m：两个字符串的长度
sq：块大小
q：查询次数
numa,numb：块的数量

 */
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
const int N=2e5+10,B=5000,C=N/B+10;
const double pi=acos(-1);
struct cmplx{
	double a,b;
	cmplx(){}
	cmplx(double a1,double b1){a=a1; b=b1;}
	void init(){a=b=0;}
	friend cmplx operator + (cmplx x,cmplx y)
	{return cmplx(x.a+y.a,x.b+y.b);}
	friend cmplx operator - (cmplx x,cmplx y)
	{return cmplx(x.a-y.a,x.b-y.b);}
	//(a+bi)(c+di) = (ac-bd) + (ad+bc)i
	friend cmplx operator * (cmplx x,cmplx y)
	{return cmplx(x.a*y.a-x.b*y.b,x.a*y.b+x.b*y.a);}
};
namespace FFT{
	const int TOP=20,N=(1<<18)+10;
	cmplx A[N],B[N];
	int rev[N],vis[TOP+1];
	int len;
	void get_len(int n){
		for (int i=0;i<len;++i) A[i].init(),B[i].init();
		int bit=0;//位数计数器
		for (len=1;len<=n;++bit,len<<=1);//大于等于n的最小2的幂
		rev[0]=0;//第一位逆序为0
		for (int i=1;i<len;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	}
	void clr(int op){
		for (int i=0;i<len;++i) if (op) B[i].init();else A[i].init();
	}
	void fft(cmplx *a,int op){
		for (int i=0;i<len;++i)
			//位逆序大于当前索引
			if (rev[i]>i) swap(a[rev[i]],a[i]);
		//w为当前旋转因子，u,v为临时计算值，w_n为步长旋转因子
		cmplx w,u,v,w_n;
		for (int step=2,k=0;step<=len;step<<=1,++k){//k为层数
			w_n=cmplx(cos(2*pi/step),op*sin(2*pi/step));
			for (int st=0;st<len;st+=step){
				w=cmplx(1,0);//当前旋转因子初始化为1
				for (int i=0;i<(step>>1);++i){//处理步长一半的元素
					v=a[st+i+(step>>1)]*w;//计算蝴蝶操作的第二个项
					u=a[st+i];//获取第一个项
					a[st+i]=u+v;//蝶形变换上半部分
					a[st+i+(step>>1)]=u-v;//蝶形变换下半部分
					w=w*w_n;//更新旋转因子
				}
			}
		}
		if (op==1) return;//正向FFT
		for (int i=0;i<len;++i) a[i].a/=len;//逆变换需要除以长度
	}
}
char a[N],b[N];//存储输入的两个字符串
ll dis[C][N];//距离数组，存储预计算的结果
int n,m,sq,q,numa,numb;
ll get_val(cmplx x){return 1LL*round(x.a);}//从复数中提取实部并四舍五入
int Id(int x){return (x-1)/sq+1;}//x属于第几个块
int St(int x){return (x-1)*sq+1;}//第x个块的起始位置
int Ed(int x){return x*sq;}//第x个块的结束位置
void prework(){
	sq=B;

	int l,r,len;
	numa=Id(n);//字符串a需要分成几块
	numb=Id(m);//字符串b需要分成几块
	FFT::get_len(B+m);
	//字符'1'转为复数(1,0)，字符'0'转为复数(-1,0)
	for (int i=1;i<=m;++i) FFT::B[i]=cmplx(b[i]=='1'?1:-1,0);
	FFT::fft(FFT::B,1);//对B数组执行正向FFT
	for (int i=1;i<=numa;++i){
		l=St(i); r=min(Ed(i),n);//第i块的起始和结束位置（不超过字符串长度）
		FFT::clr(0);
		//从右到左遍历块内的字符
		///将字符转换为复数并存入A数组（翻转顺序）
		for (int j=r;j>=l;--j) FFT::A[r-j+1]=cmplx(a[j]=='1'?1:-1,0);
		FFT::fft(FFT::A,1);
		//频域相乘（对应时域卷积）
		for (int j=0;j<FFT::len;++j) FFT::A[j]=FFT::A[j]*FFT::B[j];
		FFT::fft(FFT::A,-1);//执行逆向FFT
		len=r-l+1;//当前块的长度
		for (int j=1;j<=m;++j)
			//len是相同字符数，A[j+len]是相似度，相减除以2得到差
			dis[i][j]=(len-get_val(FFT::A[j+len]))/2;
	}
}
int query(int p1,int p2,int len){
	int ret=0;
	int num1=Id(p1),num2=Id(p1+len-1);//起始和结束位置所属的块
	if (num1==num2){//查询区间完全在同一个块内
		for (int i=0;i<len;++i)//直接逐个比较字符
			ret+=a[p1+i]!=b[p2+i];
	}
	else{//跨多个块
		for (int i=p1;i<=Ed(num1);++i)//开头部分（从p1到第一个块的结束）
			ret+=a[i]!=b[p2+i-p1];
		for (int i=num1+1;i<num2;++i)//处理中间的整块
			ret+=dis[i][p2+St(i)-p1];
		for (int i=St(num2);i<=p1+len-1;++i)//结尾部分（从最后一个块的开始到p1+len-1）
			ret+=a[i]!=b[p2+i-p1];
	}
	return ret;
}

int main(){
	int p1,p2,len;
	scanf("%s",a+1);
	scanf("%s",b+1);
	n=strlen(a+1); m=strlen(b+1);
	prework();
	scanf("%d",&q);
	for (int i=1;i<=q;++i){
		scanf("%d%d%d",&p1,&p2,&len);
		++p1; ++p2;//下标从0-indexed转为1-indexed
		printf("%d\n",query(p1,p2,len));
	}
}