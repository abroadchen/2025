use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<usize> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    let n = parts[0];
    let q = parts[1];
    let mut pos = 0i32;//正数计数器
    let mut neg = 0i32;
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let mums: Vec<i32> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    for i in 0..n {
        let m = mums[i];
        if m > 0 { pos += 1; } else { neg += 1; }
    }
    for _ in 0..q {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<i32> = input.trim().split_whitespace()
            .map(|x| x.parse().unwrap()).collect();
        let a = parts[0];//区间左端点
        let b = parts[1];
        if (b - a + 1) % 2 == 1 { println!("0"); }
        else if (b - a + 1) / 2 <= pos.min(neg) { println!("1"); }//正数和负数数量的最小值
        else { println!("0"); }
    }
}