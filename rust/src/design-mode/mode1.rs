/**
@author: June
@since: 2025/7/28
@desc:
*/

/*
编码时应该总是倾向于使用借用类型而不是借用所有类型
对于String类型来说，应该倾向于使用使用&str，而不是&String
对于T类型来说，应该倾向于 使用&[T]而不是&Vec[T]
应该倾向于使用&T而不是&Box<T>

String类型具有一层间接，因为String类型的本质是一个具有三个字段的胖指针（三个字段分别是ptr、cap、len，ptr指向在堆上的具体的内容
&String具有两层引用，是因为是String的基础上，加了&，所以b实际上指向的是a，而不是堆上的内容
&str类型也是一个胖指针，直接指向栈上的内容
*/

fn main1() {
    let a: String = "content".to_string();
    let b: &String = &a;
    let c: &str = a.as_str();
}

fn print_use_string(word: String) { println!("{:?}", word); }
fn print_use_string1(word: &String) { println!("{:?}", word); }
fn print_use_str(word: &str) { println!("{:?}", word); }
fn main() {
    let a = "content".to_string();
    print_use_string(a);    // println!("a: {:?}", a);   //This will error
    let b = "content".to_string();
    print_use_string1(&b);
    println!("b: {:?}", b);    // print_use_string1("content");  //This will error    print_use_string1(&"content".to_string());
    let c = "content".to_string();
    print_use_str(&c);
    println!("c: {:?}", c);
    print_use_str("content");
}