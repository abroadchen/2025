use std::io;

fn main() {
    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer).unwrap();
    let n: i32 = buffer.trim().parse().unwrap();//将输入的字符串转换为整数
    let mut x = 0i32;
    for _ in 0..n {
        let mut buffer = String::new();//在循环内部创建一个新的可变字符串变量，用于存储每一行输入
        io::stdin().read_line(&mut buffer).unwrap();
        let s = buffer.trim();
        //检查字符串的第二个字符（索引为1）是否为'+'号
        if s.chars().nth(1).unwrap() == '+' { x += 1; } else { x -= 1; }
    }
    println!("{}", x);
}