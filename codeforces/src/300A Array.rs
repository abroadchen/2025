/**
res[0] 存储负数，res[1] 存储正数，res[2] 存储零

如果元素是 0，将其放入 res[2] 数组
res[2][0] 存储 res[2] 中元素的个数
res[2][res[2][0]] 存储实际的元素值
同样的逻辑适用于正数（res[1]）和负数（res[0]）
as usize 将 i32 转换为 usize，因为数组索引必须是 usize 类型

如果没有正数（res[1][0] == 0）
从负数数组中取出两个元素放入正数数组
每次取出一个元素后，负数数组计数减1

如果负数个数为偶数且大于0
将一个负数移到零数组中（保证负数数组中保持奇数个元素）

如果是最后一个元素（j == res[i][0]），输出换行符  实际元素的个数也是最后一个元素的索引
*/
use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let a: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let mut res = vec![vec![0i32; 120]; 3];
    for i in 0..n {
        if a[i] == 0 {
            res[2][0] += 1; let p = res[2][0] as usize;
            res[2][p] = a[i];
        } else if a[i] > 0 {
            res[1][0] += 1; let p = res[1][0] as usize;
            res[1][p] = a[i];
        } else {
            res[0][0] += 1; let p = res[0][0] as usize;
            res[0][p] = a[i];
        }
    }
    if res[1][0] == 0 {
        res[1][0] += 1;
        let p1 = res[1][0] as usize;
        let p2 = res[0][0] as usize;
        res[1][p1] = res[0][p2];
        res[0][0] -= 1;
        res[1][0] += 1;
        let p3 = res[1][0] as usize;
        let p4 = res[0][0] as usize;
        res[1][p3] = res[0][p4];
        res[0][0] -= 1;
    }
    if res[0][0] % 2 == 0 {
        res[2][0] += 1;
        let p1 = res[2][0] as usize;
        let p2 = res[0][0] as usize;
        res[2][p1] = res[0][p2];
        res[0][0] -= 1;
    }
    for i in 0..3 {
        for j in 0..=res[i][0] as usize {
            print!("{}", res[i][j]);
            if j == res[i][0] as usize { print!("\n"); } else { print!(" "); }
        }
    }
}
