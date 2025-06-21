FROM alpine:3.18.4

#RUN mkdir /go && && cd /go \
#    && wget --no-check-certificate https://golang.google.cn/dl/go1.21.0.linux-amd64.tar.gz \
#    && tar -C /usr/local -zxf go1.21.0.linux-amd64.tar.gz \
#    && rm -rf /go/go1.21.0.linux-amd64.tar.gz \
#    && mkdir /lib64 \
#    && ln -s /lib/libc.msl-x86_64.so.1 /lib64/ld-linux-x86-64.so.2
#
#ENV GOPATH /go
#ENV PATH /usr/local/go/bin:$GOPATH/bin:$PATH

RUN mkdir /user
COPY bin/user-api /user
COPY api/etc/user.yaml /user
RUN chmod +x /user/user-api
WORKDIR /user
ENTRYPOINT ["./user-api", "-f", "user.yaml"]