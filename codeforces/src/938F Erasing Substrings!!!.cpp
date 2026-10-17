//
// Created by Psy.C on 2026/10/17.
//
/**
fr[N][N]：回溯/转移来源表，记录 DP 时从哪个状态转移而来（用于最后构造答案）。取值：-2=终点/起点，-1=沿主对角线（取当前字符），或 2^l=沿某一位的转移。
dp[N][N]：动态规划表，存每个状态对应的字典序排名（rank）。
tmp[N]：临时数组，存 (排名, 字符) 的 pair，用于排序/比较。
vc[N][26]：按 (dp值, 字符) 分桶的桶数组，用于对每个状态统计和赋名次 cnt
读入字符串，n 是其长度，s = " " + s：在串首前面加一个空格，使下标从 1 开始（方便后续 s[i] 用 1-based 下标
求不超过 n 的最大 2 的幂：t = 2^k，k 是幂次。例如 n=20 → t=16, k=4。这是"倍增"的块大小，DP 按这个块长处理
对所有 0..2^k-1 的 i：
fr[i][i] = -2：标记对角线上的状态为"终点"（回溯终止条件）。
dp[i][i] = 1：对角线的排名初始为 1
外层循环按对角线 d 推进。d 从 1 到 n-2^k+1，对应 "起点位置" 依次后移，处理所有起点 d、长度 2^k 的窗口
for i=d, j=0...：沿对角线移动，i 是真实下标（串内位置），j 是掩码（0..2^k-1）。
tmp[i] = make_pair(dp[i-1][j], s[i]-'a')：临时值 = (上一行的 dp 排名, 当前字符的序号)。这是"默认方向"（取当前字符，从上往下走）。
fr[i][j] = -1：先把来源标记为"默认方向 -1"。
for l in 0..k-1，if ((j>>l)&1)：遍历 j 的每个设位 bit l。
if (tmp[i-(1<<l)] < tmp[i])：若从"减去 2^l 的位置"转移能得到更小的 tmp，则更新。
tmp[i] = min(tmp[i], tmp[i-(1<<l)]); fr[i][j] = (1<<l)：取较小者，并把来源记录为 2^l —— 即记录这次用的跳步。
vc[ tmp[i].first ][ tmp[i].second ].push_back(i)：把当前位置按 (排名, 字符) 放进桶，用于下一步统计名次。
这段实质是：对每个 (i,j)，求所有可达前继中字典序最小的 (dp 排名, 字符) 组合，作为该状态的"最优来源"，并记录到 fr 供回溯。
cnt=0：初始名次。
双层循环遍历桶 vc[rank][char]：
若某个桶非空，cnt++：每个非空桶名次 +1（字典序：按排名从小到大、同排名按字符从小到大，排好名次）。
对桶内每个元素 v，dp[v][v-d] = cnt：把该位置的状态 dp[行=v][列=v-d] 赋成当前名次。
这一步给所有状态打上"字典序排名"（rank），供下一轮对角线比较用。列下标 v-d 即对应的掩码 j（因为 i=v 时 j=v-d）。
沿同一对角线，把刚才 push_back 进去的位置从对应桶里清空，避免跨 d 轮之间互相污染。
用 tmp[i] 的 (rank, char) 定位到对应桶再 clear
x=n, y=2^k-1：从最终状态（串尾、全 1 掩码）开始回溯。
while (fr[x][y] != -2)：没到终点就一直回溯。
若 fr[x][y] == -1（默认方向）：输出当前字符 s[x]，然后 x--（上移一行，位置前移）。
否则（fr[x][y] 是某个 2^l）：取出跳步 tp=fr[x][y]，然后 x -= tp; y -= tp（沿该 bit 回退）。
ranges::reverse(ans)：回溯是倒序，输出前反转为正序。
输出所有字符。
整体回溯就是顺着 fr 记录的"最优转移链"走，碰到 -1 就取一个字符、碰到 2^l 就跨越一整个 2^l 块，最终还原构造出的答案字符串
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

constexpr int N = 5005;

int fr[N][N], dp[N][N];
ii tmp[N];
vector<int> vc[N][26];
int main() {
    fast;
    string s; cin >> s;
    int n = s.size(); s = " " + s;
    int t=1,k=0;
    while(t*2<=n) t*=2,k++;
    for(int i=0;i<(1<<k);i++){
        fr[i][i]=-2;
        dp[i][i]=1;
    }
    for(int d=1;d<=n-(1<<k)+1;d++){
        for(int i=d,j=0;j<(1<<k);i++,j++){
            tmp[i]=make_pair(dp[i-1][j],s[i]-'a');
            fr[i][j]=-1;
            for(int l=0;l<k;l++) if((j>>l)&1)
                if(tmp[i-(1<<l)]<tmp[i]) tmp[i]=min(tmp[i],tmp[i-(1<<l)]),fr[i][j]=(1<<l);
            vc[tmp[i].first][tmp[i].second].push_back(i);
        }
        int cnt=0;
        for(int i=1;i<=(1<<k);i++){
            for(int j=0;j<26;j++){
                if(!vc[i][j].empty()) cnt++;
                for(auto v:vc[i][j]){
                    dp[v][v-d]=cnt;
                }
            }
        }
        for(int i=d,j=0;j<(1<<k);i++,j++){
            vc[tmp[i].first][tmp[i].second].clear();
        }
    }
    int x=n,y=(1<<k)-1;
    vector<char> ans;
    while(fr[x][y]!=-2){
        if(fr[x][y]==-1){
            ans.push_back(s[x]);
            x--;
        }
        else{
            int tp=fr[x][y];
            x-=tp,y-=tp;
        }
    }
    ranges::reverse(ans);
    for(auto v:ans) cout<<v;
    return 0;
}