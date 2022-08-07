all: recv_udp send_udp net_client net_server nslookup sink source gateway wget testparse 

recv_udp:
	gcc -o recv_udp recv_udp.c -Wall -g

send_udp:
	gcc -o send_udp send_udp.c -Wall -g

net_client:
	gcc -o net_client net_client.c -Wall -g

net_server:
	gcc -o net_server net_server.c -Wall -g

sink:
	gcc -o sink sink.c -Wall -g

source:
	gcc -o source source.c -Wall -g

gateway:
	gcc -o gateway gateway.c -Wall -g

wget:parseurl
	gcc -Wall wget.c -o wget parseurl.o -Wextra -g

parseurl: parseurl.c
	gcc -c parseurl.c -Wall 

testparse: parseurl testparseurl.c
	gcc -o testparse parseurl.o testparseurl.c -Wall 


task1: recv_udp send_udp 

task2: sink source gateway

task3: net_client net_server wget testparse 

clean:
	rm -f recv_udp send_udp net_client net_server sink source gateway send recv nslookup wget parseurl *.o testparse