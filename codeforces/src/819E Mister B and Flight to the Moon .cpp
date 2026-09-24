//
// Created by Psy.C on 2026/9/23.
//
/**
loop 表示一个环（顶点序列），支持长度 3（三个点）或长度 4（四个点）两种构造。
print() 输出环的长度和顶点编号
m = n/2（因为 n 奇数，如 n=2m+1）。
顶点编号采用：1 和 2,3, 4,5, ..., 2m, 2m+1 这种「1 + 成对的偶数对」结构。即顶点 2i, 2i+1 是一对。
第一段：对每个 i，输出两次 loop(1, 2i, 2i+1)——即「顶点1、2i、2i+1」组成的长度为 3 的环，出现两次（重复两次）。
第二段：对任意 i<j，输出两次 loop(2i, 2j, 2i+1, 2j+1)——即四元环，也出现两次。
所以奇数情形构造了「三角环和四元环各成对出现」的结构
偶数情形 m = n/2 - 1，把顶点 n 单独拎出来当作特殊角色（替代奇数情形里顶点 1 对多个对象的连接）。
顶点也按 1, n, 和成对的 2i, 2i+1 分布。
第一段：对每个 i：
输出 loop(1, 2i, 2i+1) 和 loop(n, 2i, 2i+1)——顶点 1 和顶点 n 分别与该对组成三角环。
若 i==1：额外输出 loop(1,2,n) 和 loop(1,3,n)——顶点 1、2、n 和 1、3、n 两个三角环。
否则：输出 loop(1, 2i, n, 2i+1)——一个四元环。
第二段：与奇数情形相同的二元组四元环（i<j 时输出两次）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define pb push_back
using namespace std;

struct loop {
    vector<int>a;
    loop(int x,int y,int z){a.pb(x),a.pb(y),a.pb(z);}
    loop(int w,int x,int y,int z){a.pb(w),a.pb(x),a.pb(y),a.pb(z);}
    void print(){
        cout<<a.size()<<" ";
        for(int i : a)cout<<i<<" ";
    }
};

int n;
vector<loop> ans;
void solve() {
    int m=n/2;
    for(int i=1;i<=m;i++)
        ans.pb(loop(1,i*2,i*2+1)),ans.pb(loop(1,i*2,i*2+1));
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            if(i<j){
                ans.pb(loop(i*2,j*2,i*2+1,j*2+1));
                ans.pb(loop(i*2,j*2,i*2+1,j*2+1));
            }
        }
    }
}
void solve2() {
    int m=n/2-1;
    for(int i=1;i<=m;i++){
        ans.pb(loop(1,i*2,i*2+1)),ans.pb(loop(n,i*2,i*2+1));
        if(i==1)ans.pb(loop(1,i*2,n)),ans.pb(loop(1,i*2+1,n));
        else ans.pb(loop(1,i*2,n,i*2+1));
    }
    for(int i=1;i<=m;i++)for(int j=1;j<=m;j++)
        if(i<j)
            ans.pb(loop(i*2,j*2,i*2+1,j*2+1)),ans.pb(loop(i*2,j*2,i*2+1,j*2+1));
}

void print() {
    cout<<ans.size()<<endl;
    for(auto& an : ans){
        an.print();
        cout<<endl;
    }
}

signed main() {
    fast;
    cin >> n;
    if (n&1) solve(); else solve2();
    print();
    return 0;
}