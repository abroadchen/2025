use std::net::{TcpListener, TcpStream};
use std::{io, thread};
use std::io::{Read, Write};
use std::time::Duration;

/**
@author: June
@since: 2025/7/25
@desc:
*/

fn handle_client(mut stream: TcpStream) -> io::Result<()> {
    let mut buf = [0; 512];
    for _ in 0..1000 {
        let bytes_read = stream.read(&mut buf)?;
        if bytes_read == 0 {
            return Ok(());
        }
        stream.write(&buf[..bytes_read])?;
        thread::sleep(Duration::from_millis(10));
    }
    Ok(())
}

fn main() -> io::Result<()> {
    let listener = TcpListener::bind("127.0.0.1:8080")?;
    let mut thread_vec: Vec<thread::JoinHandle<()>> = Vec::new();
    for stream in listener.incoming() {
        let stream = stream.expect("failed to accept");
        let handle = thread::spawn(move || handle_client(stream).unwrap_or_else(|error| eprint!("{:?}", error)));
        thread_vec.push(handle);

    }
    for handle in thread_vec {
        handle.join().unwrap();
    }
    Ok(())
}