FROM ubuntu:latest

RUN apt update -y && apt upgrade -y
RUN apt install build-essential git make apt-utils -y
RUN apt install librestbed-dev -y 

ADD ./server /opt/server

WORKDIR /opt/server

RUN make release

CMD ./build/release/server --port $PORT