///
/// j 从1到m：表示矩阵的列号（1-based）
// j-1 从0到m-1：对应向量的索引（0-based）
///向量使用从0开始的索引
use std::io;
const N: usize = 110;
const D: usize = 10010;
fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let n = parts[0] as usize;//矩阵行数n
    let m = parts[1] as usize;
    let d = parts[2] as i32;//模数
    let mut a = [[0i32; N]; N];
    let mut cnt = [0i32; D];//统计各余数出现次数
    for i in 1..=n {
       input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let v: Vec<i32> = input
            .trim()
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        for j in 1..=m {//遍历当前行的m个元素
            a[i][j] = v[j - 1];
            cnt[(a[i][j] % d) as usize] += 1;//统计a[i][j]除以d的余数出现次数
        }
    }
    for i in 0..(d as usize) {//遍历所有可能的余数
        if cnt[i] != 0 && cnt[i] != (n * m) as i32 {//不是所有元素都有相同余数
            println!("-1");
            return;
        }
    }
    let mut ans = 1_000_000_000i32;
    for i in 1..=n {//遍历矩阵中的每个位置(i,j)作为目标值
        for j in 1..=m {
            let mut sum = 0i32;
            for k in 1..=n {//遍历矩阵中的每个元素a[k][l]
                for l in 1..=m {
                    sum += (a[k][l] - a[i][j]).abs() / d;//将a[k][l]变换到与a[i][j]同余所需的最小操作数
                }
            }
            ans = ans.min(sum);//更新ans为当前最小值
        }
    }
    println!("{}", ans);
}