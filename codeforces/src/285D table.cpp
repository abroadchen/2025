#include<iostream>
#include<cstring>
using namespace std;
int a[20],b[20];//存储排列信息
int sgn[20];//标记某个值是否已经被使用
int cnt;//满足条件的排列数量
void dfs(const int now, const int num) {//now表示当前处理的位置，num表示排列长度
    if(now == num) { cnt++; return; }//已经处理完所有位置
    for(int i=0;i<num;i++) {//尝试在当前位置放置不同的数字
        if(b[i]) { continue; }//b[i]已被使用（非0）
        const int c = (a[now]+i)%num+1;//确保c在1到num范围内
        if(sgn[c]) { continue; }//c值已经被标记过（说明已使用）
        sgn[c]=1;//标记c值为已使用
        b[i]=1;//标记位置i为已使用
        dfs(now+1, num);//递归处理下一个位置
        sgn[c]=0;//回溯：取消c值的标记
        b[i]=0;//回溯：取消位置i的标记
    }
}
int main() {
    for(int i=0;i<16;i++) { a[i] = i; }
    // a固定下来，b逐个dfs过去
    for(int i=0;i<16;i++) {
        cnt = 0;
        memset(sgn, 0, sizeof(sgn));
        memset(b, 0, sizeof(b));
        dfs(0, i+1);//对长度为i+1的排列进行深度优先搜索
        //输出当前排列长度和满足条件的排列数量
        cout << "num=" << i+1 << ' ' << "cnt=" << cnt << '\n';
    }
}
