/**
参数a和b表示当前游戏状态
返回布尔值，表示当前状态是否为必胜态
如果a和b都为0，当前玩家无法移动，返回false（必败态）
检查记忆化数组：如果已经计算过该状态，直接返回结果
-1表示未计算，0表示必败态，1表示必胜态
初始化变量y为true，用于记录是否所有后继状态都是必胜态

尝试从第一个数中取1到a的所有可能值
如果存在一个后继状态是必败态（返回false），则当前状态是必胜态
!dp(a - i, b, memo)：如果后继状态是必败态，则当前状态可能为必胜态
如果y仍为true（所有已尝试的后继状态都是必胜态），尝试从第二个数取值
如果y仍为true，尝试同时从a和b中取相同值

根据y的值更新记忆化数组
如果y为true（所有后继都是必胜态），则当前状态是必败态（0）
返回!y，即当前状态是否为必胜态


*/
use std::io;

fn dfs(a: usize, b: usize, memo: &mut Vec<Vec<i32>>) -> bool {
    if a == 0 && b == 0 { return false; }
    if memo[a][b] != -1 { return memo[a][b] == 1; }
    let mut y = true;
    for i in 1..=a { if !dfs(a - i, b, memo) { y = false; break; } }
    if y { for i in 1..=b { if !dfs(a, b - i, memo) { y = false; break; } } }
    if y {
        let mn = std::cmp::min(a, b);
        for i in 1..=mn {
            if !dfs(a - i, b - i, memo) { y = false; break; }
        }
    }
    memo[a][b] = if y { 0 } else { 1 };
    !y
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let mut arr = [0i32; 3]; //存储输入的数字
    input.clear();
    io::stdin().read_line(&mut input).unwrap();//读取第二行输入
    let v: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    for i in 0..n { arr[i] = v[i]; }//将输入值复制到arr数组中
    if n == 1 {//如果arr[0]不为0，先手必胜
        if arr[0] != 0 { println!("BitLGM"); } else { println!("BitAryo"); }
        return;
    }
    if n == 3 {//如果三个数的异或和不为0，先手必胜
        if (arr[0] ^ arr[1] ^ arr[2]) != 0 { println!("BitLGM"); } else { println!("BitAryo"); }
        return;
    }
    let mut memo = vec![vec![-1; 302]; 302];
    if dfs(arr[0] as usize, arr[1] as usize, &mut memo) { println!("BitLGM"); } else { println!("BitAryo"); }
}