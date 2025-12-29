use std::io;

fn main() {
    //4个空字符串
    let mut s = [String::new(), String::new(), String::new(), String::new()];
    for i in 0..4 {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        s[i] = input.trim().to_string();//将切片转换为String类型
    }
    for i in 0..=2 {//遍历所有可能的2x2子矩阵的左上角坐标(i, j)
        for j in 0..=2 {
            let mut d = 0;//统计'.'字符的数量
            let mut p = 0;
            for k in 0..2 {//2x2矩阵的行偏移
                for l in 0..2 {//2x2矩阵的列偏移
                    let chars: Vec<char> = s[i + k].chars().collect();//当前行转换为字符向量
                    if chars[j + l] == '.' { d += 1; } else { p += 1; }//当前位置的字符是否为'.'
                }
            }
            if (d == 3 && p == 1) || (d == 1 && p == 3) || (d == 4) || (p == 4) {
                println!("YES"); return;
            }
        }
    }
    println!("NO");
}