//
// Created by Psy.C on 2026/9/24.
//
/**
记录 s 出现过的字符到 vis[]。
flag1：若 26 个字母全在 s 中出现，则任何字符都"合法"（flag1=1
a = * 前面的前缀，b = * 后面的后缀。
若无 *，pos==-inf
情况一：模式无 *
无 * 时，长度必须完全相等。
?：要求该位置字符是 s 里出现过的合法字符。
普通字符：要求与 t 对应字符相等
情况二：模式有 *
长度下限：字符串长度必须 ≥ a.size() + b.size()（* 至少匹配 0 个）。
flag1 特判：若 s 包含全部 26 个字母，则"所有字符都合法"，* 匹配任意长度都符合"中间不含合法字符"——但此时要求长度恰好 = a+b 长度（即 * 匹配 0 个），否则…… 实际上这个特判意味着：全字母合法时，* 只能匹配空串（长度为 0），因为若 * 匹配非空，中间会出现合法字符（这里用"长度必须相等"来强制 * 为空）。
前缀 a 匹配：从 x 开头逐字符对照 a（含 ? 与普通字符规则）。
后缀 b 匹配：zb = x.size()-b.size()+i 从 x 末尾倒数对齐 b。
中间段检查（!flag1）‍：当 s 不是全字母合法时，* 覆盖的中间部分绝不能包含任何合法字符（即必须是全非法字符），否则不匹配。
这里逻辑有点微妙：按题意，* 匹配的串只能由"非 s 字符"组成（因为 s 字符若出现在中间，没法通过 ? 覆盖）。所以中间段所有位置都必须满足 vis[] == 0。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int inf = 2e9;
string s, t, a, b;
bool vis[30];
int main() {
    fast;
    cin>>s>>t;
	for(char i : s) vis[i-'a']=1;
    bool flag1=1;
    for(int i=0;i<26;i++) {
        if(!vis[i]) {
            flag1=0; break;
        }
    }
    int pos=-inf;
    for(int i=0;i<t.size();i++){
        if(t[i]=='*'){
            pos=i;
            break;
        }
    }
    if(pos!=-inf){
        a=t.substr(0,pos);
        b=t.substr(pos+1);
    }
    int q; cin>>q;
    while(q--){
        string x; cin>>x;
        if(pos==-inf){
            if(x.size()!=t.size()){
                cout<<"NO\n";
                continue;
            }
            bool flag=1;
            for(int i=0;i<x.size();i++){
                if(t[i]=='?'){
                    if(!vis[x[i]-'a']){
                        flag=0;
                        break;
                    }
                } else{
                    if(x[i]!=t[i]){
                        flag=0;
                        break;
                    }
                }
            }
            if(flag==1) cout<<"YES\n"; else cout<<"NO\n";
        } else{
            if(x.size()<(a.size()+b.size())){
                cout<<"NO\n";
                continue;
            }
            if(flag1&&x.size()!=(a.size()+b.size())){
                cout<<"NO\n";
                continue;
            }
            bool flag=1;
            for(int i=0;i<a.size();i++){
                if(a[i]=='?'){
                    if(!vis[x[i]-'a']){
                        flag=0;
                        break;
                    }
                } else{
                    if(x[i]!=a[i]){
                        flag=0;
                        break;
                    }
                }
            }
            if(!flag){
                cout<<"NO\n";
                continue;
            }
            for(int i=0;i<b.size();i++) {
                int zb=x.size()-b.size()+i;
                if(b[i]=='?') {
                    if(!vis[x[zb]-'a']) {
                        flag=0;
                        break;
                    }
                } else {
                    if(x[zb]!=b[i]) {
                    	flag=0;
                        break;
                    }
                }
            }
            if(!flag) {
                cout<<"NO\n";
                continue;
            }
            if(!flag1) {
                for(int i=a.size();i<x.size()-b.size();i++) {
                    if(vis[x[i]-'a']){
                        flag=0;
                        break;
                    }
                }
            }
            if(flag==1) cout<<"YES\n"; else cout<<"NO\n";
        }
    }
    return 0;
}