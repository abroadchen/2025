/**
@author: June
@since: 2025/7/28
@desc: 通过Clone来满足借用检查器

在Rust中，对应借用只有下面两种情况：

    只存在一个可变引用；

    存在多个不可变引用。

当开发者通过克隆变量来绕过上面这两种情况时就出现本节要说的反面模式

*/
fn print_str(s: &str) {
    println!("Str is : {:?}", s);
}

fn main() {
    // 最开始的意图:
    // let mut a = "Hello world".to_string();
    // let b = &mut a;
    // println!("Before modify, a: ");
    // print_str(&a);

    // println!("After modify, a: ");
    // b.push('!');
    // print_str(&b);

    // 初学者经常会犯的错误，也是本节要说明的反面模式:
    let mut a = "Hello world".to_string();
    let b = &mut (a.clone()); //执行这行后，b和最开始的a已经不是同一个东西了
    println!("Before modify, a: ");
    print_str(&a);

    println!("After modify, a: ");
    b.push('!');
    print_str(&b);


    // 正确的做法: 更换一下打印代码的顺序
    // tips：对于初学者来说，适当的更改一下所写代码的顺序，能很大程度上减少clone的使用
    let mut a = "Hello world".to_string();
    println!("Before modify, a: ");
    print_str(&a);

    let b = &mut a;
    println!("After modify, a: ");
    b.push('!');
    print_str(&b);


}