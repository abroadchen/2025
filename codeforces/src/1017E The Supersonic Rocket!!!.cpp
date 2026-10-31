//
// Created by Psy.C on 2026/10/31.
//

/**
真正学会的起点..
(x,y) 坐标
返回 -1/0/1：|x|<eps 视为 0，否则按符号返回
向量加减、数乘、数除
绕原点旋转 rad 弧度（本代码未使用，属预留）
坐标近似相等
两向量点积、叉积。
以 O 为起点的点积/叉积重载：dot(O,A,B) = 向量 OA 与 OB 的点积；det(O,A,B) = 叉积
按 x 升序，x 相同按 y 升序
f[] 存第一个多边形原始点；(下标从 1 起)
c[] 存第二个多边形原始点；
ch[][0] 存第一个凸包；ch[][1] 存第二个凸包；
top1/top2 凸包顶点数；L1/L2 拉直后序列长度
第一段（下凸壳）‍：从左到右扫，用 det 判断转向；当当前位置相对前两点是顺时针或共线（det<=0）时弹栈，保证构建的是逆时针凸包（这里取 <=0 会去掉共线点）。

逐个加入点时，若新点使栈顶两点构成的转向不满足逆时针，就弹出栈顶。
第二段（上凸壳）‍：从右往左再扫一遍（从 n-1 到 1），补齐上侧，ttop 记录下凸壳长度作分界。最终 ch[1..top] 是完整凸包（首尾都回到最左点，形成闭合回路）。

⚠️ 注意：top 结束时最后一个点会重复（下凸壳起点 a[1] 被上下各算一次可能导致末端重复点），代码后续循环用 i<top1、i<top2 来跳过重复的边缘，说明它利用了"凸包序列首尾有一点重复"的特性
a[] 存第一个多边形拉直的特征序列（长度 L1）；
b[] 存第二个（长度 L2）；
nxt[] 是 KMP 的失败/next 数组
第一段：构建 b 的 next 表（经典 KMP next 构造，下标从 1 开始）。

b[i] 与 b[k+1] 比较，匹配则 k++，否则回溯 k=nxt[k]，记录 nxt[i]=k。
第二段：在 a 上寻找 b。

在 a 上从头到尾跑 KMP（i 到 L1+L1，因为主串已被复制成两倍，见 main），匹配到完整 b（k==L2）即返回 true

读入两个多边形的点数与坐标（下标从 1 开始）
分别求两个凸包，暂存到 ch[][0] 和 ch[][1]，点数分别记录到 top1/top2
点数不同 → 无法全等，直接输出 NO
对凸包上每个顶点 i（跳过 i==top1，因为有重复尾部点）提取两个特征值依次压入 a[]：

特征1（角度）‍ dot(ch[i], ch[i-1], ch[i+1])：以顶点 i 为起点、向量 (ch[i-1]-ch[i]) 与 (ch[i+1]-ch[i]) 的点积。这是"该顶点夹角的余弦 × 两邻边长度乘积"，即旋转不变的角特征。
特别地，i-1==0 时用 top1-1 包回（环上处理前驱）。
特征2（边长）‍：(ch[i+1]-ch[i]) 的长度平方（即 dx²+dy²），即该顶点到下一点的边长的平方。这也是平移/旋转不变的。
这样每个顶点贡献"角、边"两个数值，整个凸包被编码成一条数值序列
与上面完全相同，只是用第二个凸包 ch[][1]
把 a[] 序列复制一份接在自己后面（长度翻倍到 L1+L1），这样 b 可以从 a 的任意一个"旋转起点"开始匹配，从而正确判断两个多边形是否可以通过旋转/平移/镜像重合（循环匹配）
KMP 在双倍 a 中找到 b → 全等，否则不等
*/
#include <bits/stdc++.h>
#define eps 1e-12
using namespace std;

constexpr int N = 4e5+5;

struct point{
    double x,y;
    point(double a=0,double b=0):x(a),y(b){}
};
int dcmp(double x){ return fabs(x)<eps?0:(x<0?-1:1);}
point operator +(point A,point B) { return point(A.x+B.x,A.y+B.y);}
point operator -(point A,point B) { return point(A.x-B.x,A.y-B.y);}
point operator *(point A,double p){ return point(A.x*p,A.y*p);}
point operator /(point A,double p){ return point(A.x/p,A.y/p);}
point rotate(point A,double rad){
    return point(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}
bool operator ==(const point& a,const point& b) {
    return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;
}
double dot(point A,point B){ return A.x*B.x+A.y*B.y;}
double det(point A,point B){ return A.x*B.y-A.y*B.x;}
double dot(point O,point A,point B){ return dot(A-O,B-O);}
double det(point O,point A,point B){ return det(A-O,B-O);}

bool cmp(point a,point b){ return a.x==b.x?a.y<b.y:a.x<b.x; }
point f[N],c[N],ch[N][2]; int top1,top2,L1,L2;
void convexhull(point *a,int n,int &top,int opt) {
    sort(a+1,a+n+1,cmp); top=0;
    for(int i=1;i<=n;i++) {
        while(top>=2&&det(ch[top-1][opt],ch[top][opt],a[i])<=0) top--;
        ch[++top][opt]=a[i];
    }
    int ttop=top;
    for(int i=n-1;i>=1;i--) {
        while(top>ttop&&det(ch[top-1][opt],ch[top][opt],a[i])<=0) top--;
        ch[++top][opt]=a[i];
    }
}
double a[N],b[N]; int nxt[N];
bool KMP()
{
    nxt[1]=0;
    for(int i=2,k=0;i<=L2;i++){
        while(k&&b[i]!=b[k+1]) k=nxt[k];
        if(b[i]==b[k+1]) k++; nxt[i]=k;
    }
    for(int i=1,k=0;i<=L1+L1;i++){
        while(k&&a[i]!=b[k+1]) k=nxt[k];
        if(a[i]==b[k+1]) k++;
        if(k==L2) return true;
    }
    return false;
}

int main() {
    int N,M,i;
    scanf("%d%d",&N,&M);
    for(i=1;i<=N;i++) scanf("%lf%lf",&f[i].x,&f[i].y);
    for(i=1;i<=M;i++) scanf("%lf%lf",&c[i].x,&c[i].y);
    convexhull(f,N,top1,0);
    convexhull(c,M,top2,1);
    if(top1!=top2) return puts("NO"),0;
    for(i=1;i<top1;i++){
        a[++L1]=dot(ch[i][0],ch[i-1==0?top1-1:i-1][0],ch[i+1][0]);
        a[++L1]=(ch[i+1][0].x-ch[i][0].x)*(ch[i+1][0].x-ch[i][0].x)+(ch[i+1][0].y-ch[i][0].y)*(ch[i+1][0].y-ch[i][0].y);
    }
    for(i=1;i<top2;i++){
        b[++L2]=dot(ch[i][1],ch[i-1==0?top2-1:i-1][1],ch[i+1][1]);
        b[++L2]=(ch[i+1][1].x-ch[i][1].x)*(ch[i+1][1].x-ch[i][1].x)+(ch[i+1][1].y-ch[i][1].y)*(ch[i+1][1].y-ch[i][1].y);
    }
    for(i=1;i<=L1;i++) a[i+L1]=a[i];
    if(KMP()) puts("YES"); else puts("NO");
    return 0;
}