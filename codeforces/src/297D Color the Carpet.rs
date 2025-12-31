// (i & 1) ^ 1 是异或操作，将奇偶性取反
/*
1. 基本约束
a[i][j] ^ a[i - 1][j]：检查相邻行元素是否满足某种关系
如果相邻行元素相同，结果为0；如果不同，结果为1
2. 约束调整
a[i][j] ^ a[i - 1][j] ^ y[i - 1][j]：结合约束矩阵y进行调整
这个值表示当前状态与约束的匹配程度
3. 取反操作
最后的 ^ 1：对结果取反
目的是将"满足约束"变为1，"不满足约束"变为0
*/
use std::io::{self, BufRead};

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<usize> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let mut n = parts[0];
    let mut m = parts[1];
    let k = parts[2];
    let mut s = vec![String::new(); 2010];//处理后的字符串
    let mut s2 = vec![String::new(); 2010];//原始输入字符串
    let mut a = vec![vec![0; 1010]; 1010];
    let mut x = vec![vec![0; 1010]; 1010];
    let mut y = vec![vec![0; 1010]; 1010];
    let mut ans = 0;//统计字符'E'的数量
    let mut flg = false;//跟踪是否进行了转置操作
    for i in 1..2*n {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        s2[i] = input.trim().to_string();
    }
    if m < n {//交换行列
        for i in 1..2*n {
            for (j, c) in s2[i].chars().enumerate() {//遍历字符串中的每个字符及其索引
                let idx = 2*(j+1) - ((i&1)^1);//计算目标索引
                if idx < s.len() { s[idx].push(c); }//确保索引不越界 c添加到s[idx]字符串的末尾
            }
        }
        std::mem::swap(&mut m, &mut n);//交换m和n的值
        flg = true;//设置转置标志
    } else {
        for i in 1..2*n {//遍历每一行
            s[i] = s2[i].clone();//将s2[i]复制到s[i]
        }
    }
    for i in 1..2*n {
        if i & 1 == 1 {
            for (j, c) in s[i].chars().enumerate() {
                x[i/2+1][j+1] = if c == 'E' { 0 } else { 1 };//将字符转换为数字：'E' -> 0，其他 -> 1
                ans += if c == 'E' { 1 } else { 0 };//统计字符'E'的数量
            }
        } else {
            for (j, c) in s[i].chars().enumerate() {
                y[i/2][j+1] = if c == 'E' { 0 } else { 1 };
                ans += if c == 'E' { 1 } else { 0 };
            }
        }
    }
    if k == 1 {
        if ans*4 >= 3 * n * (m - 1) + 3 * m * (n - 1) {
            println!("YES");
            for i in 1..=n {
                for j in 1..=m {//每行m个元素
                    print!("1 ");
                }
                println!();
            }
        } else {
            println!("NO");
        }
        return;
    }
    println!("YES");
    for i in 1..=n { a[i][1] = 1; }//第一列全部设置为1
    for i in 1..=n {
        for j in 2..=m {
            a[i][j] = a[i][j - 1] ^ x[i][j - 1];//用XOR操作填充a数组
        }
    }
    for i in 2..=n {
        let mut cnt = 0;//统计需要调整的元素数量
        for j in 1..=m { cnt += (a[i][j] ^ a[i - 1][j] ^ y[i - 1][j] ^ 1) as i32; }
        //需要调整的元素数量小于不需要调整的数量，则翻转当前行
        if cnt < (m as i32) - cnt { for j in 1..=m { a[i][j] ^= 1; } }//每个元素取反
    }
    if !flg {
        for i in 1..=n {
            for j in 1..=m { print!("{} ", a[i][j] + 1); }
            println!();
        }
    } else {//按转置后的行列顺序输出
        for i in 1..=m {
            for j in 1..=n { print!("{} ", a[j][i] + 1); }
        }
        println!();
    }
}