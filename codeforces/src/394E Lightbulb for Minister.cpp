//
// Created by Psy.C on 2026/1/30.
//
/**
* con[]：存储多边形顶点
gen[]：存储生成点
n, m：点的数量和多边形顶点数
xsum2, xsum, ysum2, ysum：坐标统计值
 *
*计算三点的叉积，用于判断点的位置关系
叉积 > 0：p1在p0p2的逆时针方向
叉积 < 0：p1在p0p2的顺时针方向
 *
*判断点 best 是否在三角形 abc 内
a1：三角形 abc 的面积
a2, a3, a4：点 best 与各边形成的三角形面积
如果三个小三角形面积和等于大三角形面积，则点在内部
 *
*初始化统计变量
读入 n 个生成点
计算 x²和、2x和、y²和、2y和
*读入多边形顶点数 m
读入 m 个多边形顶点
*计算重心坐标
X = (Σx_i)/n，Y = (Σy_i)/n
best 存储重心点
*遍历多边形的所有三角形划分
检查重心是否在某个三角形内（判断是否在多边形内）
*如果重心在多边形内，直接计算最小方差
公式：Σ(x_i²) - (Σx_i)²/n + Σ(y_i²) - (Σy_i)²/n
这是到重心距离平方和的最小值
 *
 *重心在多边形外的情况
*遍历多边形的每条边
s, t：边的起点和终点索引
计算直线方程系数
使用二次函数极值公式找到线上最近点
限制参数 k 在 [0,1] 范围内（线段上）
计算到这条边的最小距离平方和
取所有边的最小值
 */
#include <cmath>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


struct Point{
    double x,y;
}con[100000+5],gen[100000+5];
int n,m;
double xsum2,xsum;
double ysum2,ysum;

inline double xmulti(Point p1, Point p2, Point p0)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}
inline bool in(Point best,Point a,Point b,Point c){
    double a1=fabs(xmulti(a,b,c))/2;
    double a2=fabs(xmulti(a,b,best))/2;
    double a3=fabs(xmulti(a,c,best))/2;
    double a4=fabs(xmulti(b,c,best))/2;
    double s=a2+a3+a4;
    if(fabs(s-a1)<=1e-3) return 1;
    return 0;
}

int main(){
    while(~scanf("%d",&n)){
        xsum2=xsum=ysum2=ysum=0.0;
        for(int i=0;i<n;i++){
            scanf("%lf%lf",&gen[i].x,&gen[i].y);
            xsum2+=gen[i].x*gen[i].x,xsum+=gen[i].x*2;
            ysum2+=gen[i].y*gen[i].y,ysum+=gen[i].y*2;
        }
        scanf("%d",&m);
        for(int i=0;i<m;i++){
            scanf("%lf%lf",&con[i].x,&con[i].y);
        }
        double X=xsum/(n*2.0);
        double Y=ysum/(n*2.0);
        bool ok=0;
        Point best;
        best.x=X,best.y=Y;
        for(int i=1;i+1<m;i++){
            if(in(best,con[0],con[i],con[i+1])){
                ok=1;break;
            }
        }
        if(ok){
            double ans=xsum2-(xsum*xsum)/(4.0*n)+ysum2-(ysum*ysum)/(4.0*n);
            printf("%.8lf\n",ans);
        }
        else{
            double ans=1000000000000000000.00;

            for(int i=0;i<m;i++){
                int s=i,t=(i+1)%m;
                double dx=con[t].x-con[s].x,dy=con[t].y-con[s].y;
                double a=con[s].x,b=con[s].y;
                double A=dx*dx+dy*dy,B=2*a*dx+2*b*dy-xsum/n*dx-ysum/n*dy;

                double k=(-B)/(2*A);
                if(k<0) k=0;
                else if(k>1) k=1;
                double x=a+dx*k,y=b+dy*k;
                double ss=n*(x-xsum/(2.0*n))*(x-xsum/(2.0*n))+xsum2-(xsum*xsum)/(4.0*n)+
                    n*(y-ysum/(2.0*n))*(y-ysum/(2.0*n))+ysum2-(ysum*ysum)/(4.0*n);

                ans=min(ans,ss);
            }
            printf("%.8lf\n",ans);
        }
    }
    return 0;
}