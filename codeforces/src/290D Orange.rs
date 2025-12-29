///
/// to_lowercase()返回一个迭代器，用.next().unwrap()获取第一个（也是唯一一个）字符
///将小写字符转换为ASCII码值（u8类型）
// b'a'是字符'a'的ASCII码值（97）
// 检查小写字符的ASCII值是否小于'a'的ASCII值加上边界值
// 如果是，则该字符在前bound个字母范围内（如前14个字母：a到n）

use std::io;

fn main() {
    let mut input = String::new();//存储第一行输入（字符串）
    io::stdin().read_line(&mut input).unwrap();//从标准输入读取一行数据到input变量中
    let input = input.trim_end();//去除字符串末尾的换行符，避免影响后续处理
    let mut buffer = String::new();//存储第二行输入（边界值）
    io::stdin().read_line(&mut buffer).unwrap();//从标准输入读取第二行数据（边界值）
    let b: usize = buffer.trim().parse().unwrap();
    let mut ans = String::new();
    for ch in input.chars() {//遍历输入字符串的每个字符
        let lch = ch.to_lowercase().next().unwrap();//将当前字符转换为小写
        if (lch as u8) < (b'a' + b as u8) {
            ans.push(ch.to_uppercase().next().unwrap());//转换为大写并添加到结果字符串
        } else {
            ans.push(lch);
        }
    }
    println!("{}", ans);
}