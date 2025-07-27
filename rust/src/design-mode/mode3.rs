/**
@author: June
@since: 2025/7/28
@desc:
*/

struct Person {
    name: String,
    age: u32,
}

impl Person {
    // 使用new函数创建对象
    fn new(name: &str, age: u32) -> Self {
        Person { name: name.to_string(), age }
    }

    fn print(&self) {
        println!("Name: {:?}", self.name);
        println!("Age: {:?}", self.age);
    }
}

// 为Person实现Default trait
impl Default for Person {
    fn default() -> Self {
        Self { name: "".to_string(), age: 0 }
    }
}

fn main() {
    let alice = Person::new("alice", 20);
    alice.print();

    let default = Person::default();
    default.print();
}

//如果每个成员都实现了Default Trait，则我们可以直接使用#[derive(Default)]来实现Default，而不必显式的实现
// #[derive(Default))]
// struct Person {
//     name: String,
//     age: u32,
// }