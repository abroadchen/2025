use std::io;

fn main() {
    let stdin = io::stdin();//用于从控制台读取输入
    let mut input = String::new();
    stdin.read_line(&mut input).unwrap();
    let n: i32 = input.trim().parse().unwrap();
    if n % 4 == 0 {
        for i in (1..=n/2).step_by(2) {//只遍历奇数
            print!("{} {} ", i + 1, n - i + 1);
        }
        for i in ((n/2+1)..=n).step_by(2) {//只遍历奇数
            print!("{} {} ", n - i, i);
        }
        return;
    }
    if n % 4 == 1 {
        for i in (1..=n/2).step_by(2) {
            print!("{} {} ", i + 1, n - i + 1);
        }
        print!("{} ", n/2 + 1);
        for i in ((n/2+2)..=n).step_by(2) {//只遍历偶数起点的奇数
            print!("{} {} ", n - i, i);
        }
        return;
    }
    println!("-1");//n%4既不等于0也不等于1 n%4==2或n%4==3
}