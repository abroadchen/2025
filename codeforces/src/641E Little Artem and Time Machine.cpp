//
// Created by Psy.C on 2026/3/31.
//
/**
opp[i][0]表示操作类型，opp[i][1]表示位置，opp[i][2]表示值
op：以离散化后的值为索引的操作列表

add函数：在树状数组位置p处添加值x
循环更新所有相关的树状数组节点
qry函数：查询前缀和（从1到p的元素和）
p^=p&-p：相当于p -= p&-p，向上移动到父节点
返回从位置1到p的累积和
backup：备份当前修改过的树状数组位置
mdf函数：修改树状数组，同时记录修改的位置和值到backup
init函数：恢复树状数组到初始状态（撤销所有修改）
遍历backup，对每个位置减去原来的值
清空backup向量

对每组操作进行处理
清空lsh，将当前组中所有操作的位置加入lsh
排序并去重，准备对位置进行离散化

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+5;

vector<int> lsh;
int n;
int opp[N][3];
vector<int> op[N];
int ans[N];
int trr[N];
void add(int p,int x){
    while(p<=1e5) trr[p]+=x,p+=p&-p;
}
int qry(int p){
    int res=0;
    while(p) res+=trr[p],p^=p&-p;
    return res;
}
vector<pair<int,int> > backup;
void mdf(int pos,int x){
    backup.emplace_back(pos,x);
    add(pos,x);
}
void init(){
    for(auto [fst, snd]:backup) add(fst,-snd);
    backup.clear();
}
int main(){
    fast;
    cin>>n;
    for(int i=1;i<=n;++i) cin>>opp[i][0]>>opp[i][1]>>opp[i][2],lsh.emplace_back(opp[i][2]);

    sort(lsh.begin(),lsh.end());
    lsh.erase(unique(lsh.begin(),lsh.end()),lsh.end());
    //将原始值替换为其在离散化后数组中的索引
    for(int i=1;i<=n;++i) opp[i][2]=lower_bound(lsh.begin(),lsh.end(),opp[i][2])-lsh.begin();
    //按照离散化后的值分组，相同值的操作放在同一个向量中
    for(int i=1;i<=n;++i) op[opp[i][2]].emplace_back(i);

    int len=lsh.size();
    for(int i=0;i<len;++i){
        lsh.clear();
        for(auto iter:op[i]) lsh.emplace_back(opp[iter][1]);
        sort(lsh.begin(),lsh.end());
        lsh.erase(unique(lsh.begin(),lsh.end()),lsh.end());
        //对位置进行离散化（加1是为了避免索引为0的问题）
        for(auto iter:op[i]) opp[iter][1]=lower_bound(lsh.begin(),lsh.end(),opp[iter][1])-lsh.begin()+1;

        for(auto iter:op[i]){
            if(opp[iter][0]==1) mdf(opp[iter][1],1);//在对应位置加1
            else if(opp[iter][0]==2) mdf(opp[iter][1],-1);//在对应位置减1
            else ans[iter]=qry(opp[iter][1]);//查询前缀和并保存结果
        }
        init();
    }
    for(int i=1;i<=n;++i) if(opp[i][0]==3) cout<<ans[i]<<'\n';
}