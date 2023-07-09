#include <iostream>
#include <string>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
	const int port = 4000;
	const std::string addr = "127.0.0.1";
	struct sockaddr_in serveraddr;
	auto sockid = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockid < 0) {
		std::cerr << "Failed to create a socket." << std::endl;
		return 1;
	}
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	if (inet_pton(AF_INET, addr.c_str(), &(serveraddr.sin_addr)) != 1) {
		std::cerr << "Invalid address." << std::endl;
		return 1;
	}

	std::string message = "hello~~";
	auto len = sendto(sockid, message.c_str(), message.size(), 0,
					  (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (len < 0) {
		std::cerr << "Failed to send the data." << std::endl;
		return 1;
	}
	close(sockid);
	return 0;
}
