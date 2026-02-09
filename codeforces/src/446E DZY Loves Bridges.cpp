//
// Created by Psy.C on 2026/2/9.
//
/**
p是模数，inv2是2在模p下的逆元，phi是欧拉函数值
S、T数组：存储中间计算结果
a、b数组：长度为2^25，用于FWT变换
n：输入的n值
D：输入的大指数值

计算以2为底的对数，使用内置函数__builtin_clz计算前导零的个数
n（集合大小）、D（指数）、s（已知项数）
D大于等于phi，则使用欧拉定理优化：当指数很大时，可以取模phi再加phi
T[i] = (2^i - 2^(i-1)) % p = 2^(i-1) % p
如果D大于等于phi，应用欧拉定理进行指数降幂
欧拉定理：如果gcd(a,m)=1，则 a^φ(m) ≡ 1 (mod m)
所以 a^D ≡ a^(D mod φ(m)) (mod m)，当D ≥ φ(m)时
这里加phi是为了保证指数仍足够大以避免边界问题

i^lowbit(i) 是去掉i的最低位1得到的数
逐步构建所有子集的贡献

mylog(lowbit(i)) 找到i的最低位1的位置

对于每一对 (a[i], a[i+w])：
x=a[i], y=a[i+w] 保存原始值
a[i] = x+y，如果≥p则减p
a[i+w] = x-y，为避免负数先加p再减y，如果≥p则减p

调整X：X = (X + p - Y) % p
X = X * inv2^log(w) % p，进行相应的缩放
计算S为a[w]到a[2w-1]的和
更新a[w]到a[2w-1]：每个元素乘Y，再加上S*X的贡献
执行逆FWT变换
a[i] = (x+y) * inv2 % p
a[i+w] = (x-y) * inv2 % p，同样避免负数

 */
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
template <class t>
void read(t& s){
    s=0; signed f=1;char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1;c=getchar(); }
    while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();
    s*=f;
}
inline int lowbit(int x) { return x&(-x); }
constexpr int p=1051131, inv2=525566, phi=700752;
int S[30],T[30],a[1<<25],b[1<<25],n;
long long D;
//x的最高位1的位置（从0开始计数）
inline int mylog(int x){return 31-__builtin_clz(x);}
inline int fpow(int a,int b) {
    int ret=1;
    for(;b;b>>=1,a=1LL*a*a%p) if(b&1) ret=1LL*ret*a%p;
    return ret;
}

inline void readin() {
    int s;read(n),read(D),read(s);
    if(D>=phi) D=D%phi+phi;
    T[0]=1;
    rep(i,1,n) T[i]=((1<<i)-(1<<~-i))%p;
    rep(i,0,n-1) (b[0]+=S[i])>=p&&(b[0]-=p);
    rep(i,1,(1<<n)-1) (b[i]+=b[i^lowbit(i)]+p-S[mylog(lowbit(i))])>=p&&(b[i]-=p);
    b[0]=1;
    rep(i,1,n-1) (T[i]+=T[i-1])>=p&&(T[i]-=p);
    rep(i,1,(1<<n)-1) (b[i]+=T[mylog(lowbit(i))])>=p&&(b[i]-=p);
    rep(i,0,s-1) read(a[i]);
    rep(i,s,(1<<n)-1) a[i]=(101LL*a[i-s]+10007)%p;//线性同余生成器
}

inline void fwt(int n) {
    if(n==1) return a[0]=1LL*a[0]*fpow(b[0],D)%p,void();
    int w=n>>1,x,y,X,Y,S=0;
    rep(i,0,w-1)
        x=a[i],y=a[i+w],(a[i]=x+y)>=p&&(a[i]-=p),(a[i+w]=x+p-y)>=p&&(a[i+w]-=p),
        x=b[i],y=b[i+w],(b[i]=x+y)>=p&&(b[i]-=p),(b[i+w]=x+p-y)>=p&&(b[i+w]-=p);
    fwt(w);//递归处理前w个元素
    x=b[w],y=b[w+1],X=fpow((1LL*w*y+x-y+p)%p,D),Y=fpow((x+p-y)%p,D);
    (X+=p-Y)>=p&&(X-=p),X=1LL*X*fpow(inv2,mylog(w))%p;
    rep(i,0,w-1) (S+=a[i+w])>=p&&(S-=p);
    rep(i,0,w-1) a[i+w]=(1LL*a[i+w]*Y+1LL*S*X)%p;
    rep(i,0,w-1) x=a[i],y=a[i+w],a[i]=1LL*(x+y)*inv2%p,a[i+w]=1LL*(x+p-y)*inv2%p;
}
int main() {
    readin();
    fwt(1<<n);
    unsigned int ans=0;
    rep(i,0,(1<<n)-1) ans^=a[i];
    std::printf("%u\n",ans);
    return 0;
}