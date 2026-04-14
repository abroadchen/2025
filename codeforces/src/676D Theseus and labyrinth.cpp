//
// Created by Psy.C on 2026/4/13.
//
/**
n,m: 地图的行数和列数
sx,sy: 起始坐标
tx,ty: 目标坐标
s: 临时字符串
mp: 地图，用位掩码表示方向
vis: 访问标记数组，vis[x][y][st]表示在位置(x,y)、状态st时是否访问过

x,y: 坐标
time: 当前时间
st: 方向状态（0-3，对应四个方向）
将字符转换为位掩码表示的方向
位掩码：第0位=左，第1位=下，第2位=右，第3位=上
例如：'-'(左右) = 5 = 0101₂，表示可以向左(1)和向右(4)
检查坐标是否在地图范围内

清空访问标记
设置起始状态
将起始节点加入队列
取出队首元素
如果到达目标位置，返回时间
原地旋转：时间+1，方向状态+1（循环）
检查旋转后的状态是否访问过
尝试四个方向移动
nex.x=now.x+dir[i][0]; nex.y=now.y+dir[i][1]: 计算新位置
mp[now.x][now.y]&(1<<(i+now.st)%4): 检查当前位置是否允许向指定方向移动
mp[nex.x][nex.y]&(1<<(i+2+nex.st)%4): 检查目标位置是否允许从相反方向进入
(i+2)表示相反方向（左对右，上对下）
如果无法到达目标，返回-1

 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1005, dir[4][2] = {
    {0,-1},{1,0},{0,1},{-1,0}
};

int n,m;
int sx,sy,tx,ty;
char s[N];
int mp[N][N];
int vis[N][N][4];

struct node {
    int x,y,time,st;
}now,nex;

int change(char x) {
    if(x=='*') return 0;
    if(x=='<') return 1;
    if(x=='v') return 2;
    if(x=='>') return 4;
    if(x=='^') return 8;
    if(x=='-') return 5;
    if(x=='|') return 10;
    if(x=='U') return 7;
    if(x=='R') return 11;
    if(x=='D') return 13;
    if(x=='L') return 14;
    if(x=='+') return 15;
}

bool inbound(const node &a) {
    return a.x>=1&&a.x<=n&&a.y>=1&&a.y<=m;
}

int bfs()
{
    memset(vis,0,sizeof(vis));
    now.x=sx; now.y=sy; now.time=0; now.st=0;
    queue<node>q; q.push(now);
    vis[now.x][now.y][now.st]=1;
    while(!q.empty()) {
        now=q.front();
        q.pop();
        if(now.x==tx&&now.y==ty) { return now.time; }
        if(vis[now.x][now.y][(now.st+1)%4]==0) {
            q.push(node{now.x,now.y,now.time+1,(now.st+1)%4});
            vis[now.x][now.y][(now.st+1)%4]=1;
        }
        for(int i=0;i<4;i++) {
            nex.x=now.x+dir[i][0]; nex.y=now.y+dir[i][1];
            if(mp[nex.x][nex.y]!=0) {
                nex.st=now.st;
                if(inbound(nex)&&(mp[now.x][now.y]&(1<<(i+now.st)%4))&&(mp[nex.x][nex.y]&(1<<(i+2+nex.st)%4))) {
                    if(vis[nex.x][nex.y][nex.st]==0) {
                        nex.time=now.time+1;
                        vis[nex.x][nex.y][nex.st]=1;
                        q.push(nex);
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    while(~scanf("%d%d",&n,&m)) {
        for(int i=1;i<=n;i++) {
            scanf("%s",s+1);
            for(int j=1;j<=m;j++) {
                mp[i][j]=change(s[j]);
            }
        }
        scanf("%d%d",&sx,&sy);
        scanf("%d%d",&tx,&ty);
        int ans=bfs();
        printf("%d\n",ans);
    }
    return 0;
}