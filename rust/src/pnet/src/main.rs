use std::env;
use pnet::datalink;
use pnet::datalink::Channel::Ethernet;
use pnet::packet::ethernet::{EtherTypes, EthernetPacket};
use pnet::packet::ip::{IpNextHeaderProtocol, IpNextHeaderProtocols};
use pnet::packet::ipv4::Ipv4Packet;
use pnet::packet::Packet;
use pnet::packet::tcp::TcpPacket;

fn main() {
    let interface_name = env::args().nth(1).unwrap();
    let interfaces = datalink::interfaces();
    let interface = interfaces.into_iter().filter(|iface| iface.name == interface_name).next().unwrap();
    let (_tx, mut rx) = match datalink::channel(&interface, Default::default()) {
        Ok(Ethernet(tx, rx)) => (tx, rx),
        Ok(_) => panic!("Unknown channel type"),
        Err(e) => panic!("Error happened {}", e),
    };

    loop {
        match rx.next() {
            Ok(packet) => {
                let packet = EthernetPacket::new(packet).unwrap();
                handle_packet(&packet);
            },
            Err(e) => panic!("Error happened {}", e),
        }
    }
    println!("Hello, world!");
}

fn handle_packet(ethernet: &EthernetPacket) {
    match ethernet.get_ethertype() {
        EtherTypes::Ipv4 => {
            let header = Ipv4Packet::new(ethernet.payload());
            if let Some(header) = header {
                match header.get_next_level_protocol() {
                    IpNextHeaderProtocols::Tcp => {
                        let tcp = TcpPacket::new(header.payload());
                        if let Some(tcp) = tcp {
                            println!("Got TCP packet from {}", tcp.get_source());
                        }
                    },
                    _ => println!("ignore"),
                }
            }
        },
        _ => println!("Unknown ethertype"),
    }
}