//
// Created by Psy.C on 2026/2/14.
//
/**
BIT 29：最高位数（0到29，共30位）
M=BIT+2：定义M为31（29+2），为线性基预留空间
x[N]：输入数组x，存储原始数值
y[N]：输入数组y，目标数值
base[M]：线性基数组，base[i]存储第i位的基向量在x数组中的索引
is_base[N]：标记数组，is_base[i]表示第i个数是否为基础向量，-1表示不是，其他值表示在第几位
b[M]：存储基础向量的索引数组
sx[M]：记录x数组中基向量的线性组合系数
sy[N]：记录y数组中向量的线性组合系数
ans：存储最终答案操作序列
opt：存储高斯消元过程中的操作序列

时间复杂度：O(n * 30)，空间复杂度：O(n)
 */
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define BIT 29
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
const int N=10005,M=BIT+2;

int x[N],y[N],base[M],is_base[N],b[M],sx[M],sy[N];
std::vector<pr> ans,opt;

inline int read()
{
    int now=0; char c=gc();
    for(;!isdigit(c);c=gc());
    for(;isdigit(c);now=now*10+c-48,c=gc());
    return now;
}

int main()
{
    int n=read();
    for(int i=1; i<=n; ++i) x[i]=read();
    for(int i=1; i<=n; ++i) y[i]=read();
    for(int i=1; i<=n; ++i)
    {
        is_base[i]=-1;//i不是基础向量
        for(int j=BIT,s=0; ~j; --j)//s初始化为0（记录线性组合） j为-1时为0，循环结束
            if(x[i]>>j&1)//第j位为1
                //第j位已经有基向量，用它消除当前数的第j位
                if(base[j]) x[i]^=x[base[j]], s^=sx[j];//更新线性组合系数
                else
                {
                    //标记i为基础向量，位于第j位
                    ///第j位的基向量是x[i]
                    ///更新线性组合系数，设置第j位为1
                    is_base[i]=j, base[j]=i, sx[j]=s|(1<<j);//添加到基
                    break;
                }
    }
    int cnt=0;//基础向量计数器
    for(int i=1; i<=n; ++i)
    {
        int s=0;
        for(int j=BIT; ~j; --j)
            if(y[i]>>j&1)//消去y[i]的第j位
                if(base[j]) y[i]^=x[base[j]], s^=sx[j];
                else return puts("-1"),0;
        ///i是基础向量
        ///将i存储到基础向量数组
        ///存储线性组合系数，cnt自增
        if(~is_base[i]) {b[cnt]=i, sy[cnt++]=s; continue;}
        ans.emplace_back(i,i);//非基础向量直接添加自身操作
        ///遍历所有位，如果线性组合系数的第j位为1
        ///添加操作i对base[j]的影响
        for(int j=BIT; ~j; --j) if(s>>j&1) ans.emplace_back(i,base[j]);//添加依赖关系
    }
    for(int i=0; i<cnt; ++i)
    {//将sy数组从原始编号转换为重新编号
        int s=sy[i]; sy[i]=0;
        ///s的第is_base[b[j]]位为1
        ///将sy[i]的第j位置为1
        for(int j=0; j<cnt; ++j) if(s>>is_base[b[j]]&1) sy[i]|=1<<j;
    }
    for(int i=0; i<cnt; ++i)
    {
        if(!(sy[i]>>i&1))//第i位不为1
            for(int j=i+1; j<cnt; ++j)
                if(sy[j]>>i&1)//找到第i位为1的行j
                {
                    opt.emplace_back(b[i],b[j]);
                    opt.emplace_back(b[j],b[i]);
                    opt.emplace_back(b[i],b[j]);
                    std::swap(sy[i],sy[j]);//交换行
                    break;
                }
        if(sy[i]>>i&1)//第i位为1
            for(int j=i+1; j<cnt; ++j)
                if(sy[j]>>i&1)//第j行的第i位也为1
                    ///添加消除操作
                    opt.emplace_back(b[j],b[i]), sy[j]^=sy[i];//执行消元操作
    }
    for(int i=0; i<cnt; ++i)
    {
        if(!(sy[i]>>i&1))//对角线上第i位为0
            ans.emplace_back(b[i],b[i]);//添加自操作
        for(int j=i+1; j<cnt; ++j)
            if(sy[i]>>j&1)//第i行第j位为1
                ans.emplace_back(b[i],b[j]);//添加依赖关系
    }
    std::ranges::reverse(opt);//高斯消元是反向的
    for(auto v:opt) ans.push_back(v);//将操作添加到答案
    printf("%d\n",ans.size());//操作总数
    for(auto [fst, snd]:ans) printf("%d %d\n",fst,snd);//每对操作

    return 0;
}