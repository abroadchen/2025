use std::env;
use trust_dns_resolver::config::{ResolverConfig, ResolverOpts};
use trust_dns_resolver::proto::rr::RecordType;
use trust_dns_resolver::Resolver;

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        println!("Usage: dns <ip>");
        std::process::exit(1);
    }
    let query = format!("{}", args[1]);
    let resolver = Resolver::new(ResolverConfig::default(), ResolverOpts::default()).unwrap();
    let response = resolver.lookup_ip(query.as_str());
    for ans in response.iter() {
        println!("{:?}", ans);
    }
    let resolver = Resolver::from_system_conf().unwrap();
    let ns = resolver.lookup(query.as_str(), RecordType::NS);
    println!("Hello, world!");
}
