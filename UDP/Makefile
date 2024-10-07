.PHONY:all
all:udpserver udpclient

udpserver:UdpServerMain.cc
	g++ -o $@ $^ -std=c++11
udpclient:UdpClient.cc
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -rf udpserver udpclient
