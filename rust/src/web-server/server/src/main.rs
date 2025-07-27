use std::fmt::format;
use std::{fs, thread};
use std::io::{Read, Write};
use std::net::{TcpListener, TcpStream};
use mylib::ThreadPool;

fn handle_client(mut stream: TcpStream) {
    let mut buffer = [0; 1024];
    stream.read(&mut buffer).unwrap();
    println!("Client: {}", String::from_utf8_lossy(&buffer[..]));



    let get = b"GET / HTTP/1.1\r\n";
    // if buffer.starts_with(get) {
    //     let content = fs::read_to_string("x.html").unwrap();
    //     // let response = "HTTP/1.1 200 OK\r\n\r\n";
    //     let response = format!("HTTP/1.1 200 OK\r\n\r\n{}", content);
    //
    // } else {
    //
    // }

    let (status_line, filename) = if buffer.starts_with(get) {
        ("HTTP/1.1 200 OK\r\n\r\n", "hello.html")
    } else {
        ("HTTP/1.1 404 NOT FOUND\r\n\r\n", "404.html")
    };
    let contents = fs::read_to_string(filename).unwrap();
    let response = format!("{}{}", status_line, contents);
    stream.write(response.as_bytes()).unwrap();
    stream.flush().unwrap();





}




fn main() -> std::io::Result<()> {
    let listener = TcpListener::bind("127.0.0.1:8080")?;
    // let mut thread_vec: Vec<thread::JoinHandle<()>> = Vec::new();

    let pool = ThreadPool::new(4);



    for stream in listener.incoming().take(2) {
        let stream = stream?;
        // handle_client(stream);
        // let handle = thread::spawn(|| handle_client(stream));
        // thread_vec.push(handle);
        pool.execute(|| handle_client(stream));
    }

    // for handle in thread_vec {
    //     handle.join().unwrap();
    // }

    println!("Hello, world!");
    Ok(())
}
