//
// Created by Psy.C on 2026/4/15.
//
/**
n：当前测试用例中的点数
x, y, z：存储三维坐标，使用__int128防止溢出
read函数：读取long long类型并转为__int128
自定义max宏：避免标准库冲突
abss函数：计算绝对值
根据奇偶性要求调整坐标值
tp2参数：决定返回奇数还是偶数

坐标变换：将三维曼哈顿距离问题转化为四维空间中的约束问题
四种变换：
x+y+z
x+y-z
x-y+z
-x+y+z
 */
#include <bits/stdc++.h>
#define ll long long
#define sc scanf
#define pr printf
using namespace std;
constexpr int N = 1e5+5;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;

int n;
__int128 x[N],y[N],z[N];
__int128 read() {
    ll xx;sc("%lld",&xx);return xx;
}
#define max(a,b) (((a)>(b))?(a):(b))
__int128 abss(__int128 x) {
    return max(x,-x);
}
__int128 up(__int128 x,bool tp2) {
    if (!x)return tp2;
    __int128 tp=(x)/abss(x);
    x=abss(x);
    if (tp>0) {
        if (tp2)return (x/2*2+1);
        return (x+1)/2*2;
    }
    if (tp2)return -((x+1)/2*2)+1;
    return -(x/2*2);
}
bool judge(__int128 d,bool tp) {
    //计算四个变换坐标系的边界
    __int128 mx1=(__int128)INF*100000000,mn1=-(__int128)INF*100000000;
    __int128 mx2=(__int128)INF*100000000,mn2=-(__int128)INF*100000000;
    __int128 mx3=(__int128)INF*100000000,mn3=-(__int128)INF*100000000;
    __int128 mx4=(__int128)INF*100000000,mn4=-(__int128)INF*100000000;
    for (int i=1; i <= n; i++) {
        mx1=min(mx1,d+x[i]+y[i]+z[i]),mn1=max(mn1,-d+x[i]+y[i]+z[i]);
        mx2=min(mx2,d+x[i]+y[i]-z[i]),mn2=max(mn2,-d+x[i]+y[i]-z[i]);
        mx3=min(mx3,d+x[i]-y[i]+z[i]),mn3=max(mn3,-d+x[i]-y[i]+z[i]);
        mx4=min(mx4,d-x[i]+y[i]+z[i]),mn4=max(mn4,-d-x[i]+y[i]+z[i]);
    }
    //尝试偶数解
    __int128 a=up(mn2,0),b=up(mn3,0),c=up(mn4,0);
    __int128 del=mn1-a-b-c;
    if (del>=0&&a<=mx2&&b<=mx3&&c<=mx4) {
        //调整使满足约束
        if ((mx2-a)/2*2>=del) a=(del+1)/2*2+a,del=0;
        else del-=(mx2-a)/2*2,a=(mx2-a)/2*2+a;
        if ((mx3-b)/2*2>=del) b=(del+1)/2*2+b,del=0;
        else del-=(mx3-b)/2*2,b=(mx3-b)/2*2+b;
        if ((mx4-c)/2*2>=del) c=(del+1)/2*2+c,del=0;
        else del-=(mx4-c)/2*2,c=(mx4-c)/2*2+c;
    }
    //验证解是否可行
    if (mn1<=a+b+c&&a+b+c<=mx1&&mn2<=a&&a<=mx2&&mn3<=b&&b<=mx3&&mn4<=c&&c<=mx4) {
        if (tp)pr("%lld %lld %lld\n",(ll)((a+b)/2),(ll)((a+c)/2),(ll)((b+c)/2));
        return 1;
    }
    a=up(mn2,1),b=up(mn3,1),c=up(mn4,1);
    del=mn1-a-b-c;
    if (del>=0&&a<=mx2&&b<=mx3&&c<=mx4) {
        if ((mx2-a)/2*2>=del) a=(del+1)/2*2+a,del=0;
        else del-=(mx2-a)/2*2,a=(mx2-a)/2*2+a;
        if ((mx3-b)/2*2>=del) b=(del+1)/2*2+b,del=0;
        else del-=(mx3-b)/2*2,b=(mx3-b)/2*2+b;
        if ((mx4-c)/2*2>=del) c=(del+1)/2*2+c,del=0;
        else del-=(mx4-c)/2*2,c=(mx4-c)/2*2+c;
    }
    if (mn1<=a+b+c&&a+b+c<=mx1&&mn2<=a&&a<=mx2&&mn3<=b&&b<=mx3&&mn4<=c&&c<=mx4) {
        if (tp)pr("%lld %lld %lld\n",(ll)((a+b)/2),(ll)((a+c)/2),(ll)((b+c)/2));
        return 1;
    }
    return 0;
}
int main() {
    int t;
    sc("%d",&t);
    while (t--) {
        sc("%d",&n);
        for (int i=1; i <= n; i++)
            x[i]=read(),y[i]=read(),z[i]=read();
        __int128 l=0,r=(__int128)INF*2;
        while (l<r) {
            __int128 mid=(l+r)/2;
            if (judge(mid,0))
                r=mid;
            else l=mid+1;
        }
        judge(l,1);
    }
    return 0;
}