//
// Created by Psy.C on 2026/1/23.
//
/**
* n: 操作次数
m: 删除参数数量
opt: 每次操作的值
a[1000005]: 存储删除参数的数组
*ans[1000005]: 存储入栈的元素
vised[1000005]: 标记数组，记录哪些位置被删除
t[1000005]: 树状数组（Binary Indexed Tree）
 *tot: 当前栈中元素总数
 */
#include<iostream>
#include<vector>
using namespace std;
int n,m,opt,a[1000005];
int ans[1000005],vised[1000005],t[1000005];
int tot;
template <typename T> void read(T &x){
    x = 0;
    bool f = 0;
    char c = getchar();
    while (c < '0' || c > '9') f |= c == '-', c = getchar();//跳过非数字字符: 直到遇到数字或负号
    while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    if (f) x = -x;
}
template <typename T> void write(T x){
    if (x < 0) putchar('-'), x = -x;//先输出负号，再转为正数
    if (x < 10) putchar(x + '0');//个位数: 直接输出
    else write(x / 10), putchar(x % 10 + '0');//递归输出高位，然后输出个位
}
void add(int id,int num){
    while(id<=1e6){
        t[id]+=num;
        id+=id&-id;
    }
}
vector<int> v;//存储需要删除的位置
int empty(int id){// 查询1到id位置的前缀和 1到mid的未删除元素数量
    int size_=0;
    while(id){
        //cout<<id<<" "<<size_<<"\n";
        size_+=t[id];//累计和
        id-=id&-id;// 移动到下一个区间
    }
    return size_;
}
int cheak(int num){//找到第num小的未删除元素位置
    int l=1,r=1000000;
    //int res;
    int mid=l+r>>1;
    while(l<r){
        //int mid=l+r>>1;
        //res=mid;
        if(empty(mid)>=num){//找到第一个前缀和≥num的位置
            r=mid;
        }
        else l=mid+1;
        mid=l+r>>1;
        //cout<<mid<<" yep!!\n";
    }
    return mid;
}
int main(){
    for(int i=1;i<=1000000;i++){
        add(i,1);//所有位置初始为1（表示未删除）
    }
    read(n);
    read(m);
    for(int i=0;i<m;i++){
        read(a[i]);
    }
    for(int j=0;j<n;j++){
        cin>>opt;
        if(opt>=0){
            ans[++tot]=opt;//将其加入栈中
        }
        else{
            v.clear();
            for(int i=0;i<m;i++){
                int ch=cheak(a[i]);//找到第a[i]小的未删除位置
                if(ch>tot){//位置超过当前栈大小
                    break;
                }
                //cout<<ch<<" yexo!\n";
                v.push_back(ch);
            }
            for(int i=0;i<v.size();i++){//标记位置为已删除，更新树状数组
                vised[v[i]]=1;
                add(v[i],-1);
            }
        }
    }
    if(empty(tot)!=0){//如果还有未删除元素，输出它们
        for (int i=1;i<=tot;i++){
            if(!vised[i]){
                write(ans[i]);
            }
        }
    }
    else cout<<"Poor stack!\n";
    return 0;
}