/**
s.chars() 将字符串转换为字符迭代器
.collect() 将迭代器收集为 Vec<char> 类型的字符向量

dp 有2行，每行有 n+1 列
dp[0][i] 表示处理到第i个字符时，当前位为0的最小操作数
dp[1][i] 表示处理到第i个字符时，当前位为1的最小操作数
如果第一个字符是 '1'，则 dp[0][1] = 1（要变成0需要1次操作）
如果第一个字符是 '0'，则 dp[0][1] = 0（已经是0，不需要操作）
dp[1][1] = 1 表示变成1至少需要1次操作
从第2个字符开始遍历到第n个字符（注意 Rust 中 2..=n 表示包含n）

如果当前字符是 '0'：
dp[0][i] = dp[0][i-1]：保持为0，操作数不变
dp[1][i] = min(dp[1][i-1], dp[0][i-1]) + 1：变成1需要从前面的状态转移，并加1次操作
如果当前字符是 '1'：
dp[1][i] = dp[1][i-1]：保持为1，操作数不变
dp[0][i] = min(dp[1][i-1], dp[0][i-1]) + 1：变成0需要从前面的状态转移，并加1次操作

处理完所有字符后，最后一位为0的最小操作数
*/
use std::io;
use std::cmp;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let s = input.trim_end();//去除字符串末尾的换行符等空白字符
    let chars: Vec<char> = s.chars().collect();
    let n = chars.len();
    if n == 0 { println!("0"); return }//字符串为空
    let mut dp = vec![vec![0; n + 1]; 2];
    if chars[0] == '1' { dp[0][1] = 1 } else { dp[0][1] = 0 }
    dp[1][1] = 1;
    for i in 2..=n {
        if chars[i-1] == '0' {
            dp[0][i] = dp[0][i-1];
            dp[1][i] = cmp::min(dp[1][i-1], dp[0][i-1]) + 1;
        } else {
            dp[1][i] = dp[1][i-1];
            dp[0][i] = cmp::min(dp[1][i-1], dp[0][i-1]) + 1;
        }
    }
    println!("{}", dp[0][n]);
}