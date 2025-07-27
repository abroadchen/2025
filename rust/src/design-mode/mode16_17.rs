/** !!!!!!!!!!!!!!!!!!!!
@author: June
@since: 2025/7/28
@desc: 将行动分离成它自己的对象，并将它们作为参数传递
*/

//考虑数据库操作create table和add field两个命令
pub trait Migration {
    fn execute(&self) -> &str;
    fn rollback(&self) -> &str;
}

pub struct CreateTable;
impl Migration for CreateTable {
    fn execute(&self) -> &str {
        ...
    }
    fn rollback(&self) -> &str {
        ...
    }
}

pub struct AddField;
impl Migration for AddField {
    fn execute(&self) -> &str {
        ...
    }
    fn rollback(&self) -> &str {
        ...
    }
}

struct Schema {
    commands: Vec<Box<dyn Migration>>,
}

impl Schema {
    //...
    fn add_migration(&mut self, cmd: Box<dyn Migration>) {
        ...
    }

}

//将每个命令的操作创建为函数，并存储函数指针 使用函数指针是静态分发
type FnPtr = fn() -> String;
struct Command {
    execute: FnPtr,
    rollback: FnPtr,
}
struct Schema {
    commands: Vec<Command>,
}
impl Schema {
    //...

    fn execute(&self) -> Vec<String> {
        self.commands.iter().map(|cmd| (cmd.execute)()).collect()
    }
    fn rollback(&self) -> Vec<String> {
        self.commands
            .iter()
            .rev()
            .map(|cmd| (cmd.rollback)())
            .collect()
    }
}
fn add_field() -> String {
    "add field".to_string()
}
fn remove_field() -> String {
    "remove field".to_string()
}
fn main1() {
    let mut schema = Schema::new();
    schema.add_migration(|| "create table".to_string(), || "drop table".to_string());
    schema.add_migration(add_field, remove_field);
    ...
}



//使用Fn trait对象，将实现Fn trait的每个命令分别存储在向量中
type Migration<'a> = Box<dyn Fn() -> &'a str>;

struct Schema<'a> {
    executes: Vec<Migration<'a>>,
    rollbacks: Vec<Migration<'a>>,
}
//...

fn main() {
    let mut schema = Schema::new();
    schema.add_migration(|| "create table", || "drop table");
    schema.add_migration(add_field, remove_field);
    ...
}










