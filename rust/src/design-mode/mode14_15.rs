/**
@author: June
@since: 2025/7/28
@desc: 简单的文档初始化
*/
struct Connection {    name: String,    stream: TcpStream,}
impl Connection {
    /// Sends a request over the connection.
    ///
    /// # Example
    /// ```
    /// # fn call_send(connection: Connection, request: Request) {
    /// let response = connection.send_request(request);
    /// assert!(response.is_ok());
    /// # }
    /// ```
    fn send_request(&self, request: Request) {
        // ...
    }
}

//对于临时可变的变量，在可变之后进行重绑定来明确为不可变的变量
fn main() {
    let mut data = vec![2, 1, 4, 10, 3, 5];
    data.sort();
    let data = data; // 进行重新绑定，data变为不可变的变量
    println!("{:?}", data[2]);
    // data.push(4); // error, data is immutable
    // 也可以使用如下使用嵌套块，和上面等价
    let data = {
        let mut data = vec![2, 1, 4, 10, 3, 5];
        data.sort();
        data
    };
    println!("{:?}", data[2]);
    // data.push(4); // error, data is immutable
}