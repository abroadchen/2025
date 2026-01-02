use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let mut vis = [false; 105];//0-100是否出现
    let mut a = [0; 10];//存储要输出的数字
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<usize> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    for &x in parts.iter() { vis[x] = true; }// &x 表示解引用，获取实际的数字值
    let mut num = 0;//输出数字的个数
    let mut t1 = false;//是否出现了个位数
    let mut t2 = false;//是否出现了整十的两位数
    if vis[0] { a[num] = 0; num += 1; }//如果输入中包含 0，将其加入输出数组
    if vis[100] { a[num] = 100; num += 1; }//如果输入中包含 100，将其加入输出数组
    //寻找并选择第一个出现的个位数（1-9）
    for i in 1..=9 { if vis[i] { a[num] = i; num += 1; t1 = true; break; } }
    //寻找并选择第一个出现的整十两位数（10, 20, ..., 90）
    for i in 1..=9 { if vis[i*10] { a[num] = i*10; num += 1; t2 = true; break; } }
    if !t1 && !t2 {//选择第一个出现的非整十两位数
        for i in 11..=99 {
            if i % 10 == 0 { continue; }
            if vis[i] { a[num] = i; num += 1; break; }
        }
    }
    println!("{}", num);//选择的数字个数
    if num > 0 {//避免对空数组的访问
        print!("{}", a[0]);
        for i in 1..num { print!(" {}", a[i]); }
    }
    println!();
}