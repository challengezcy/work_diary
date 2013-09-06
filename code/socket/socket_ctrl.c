#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/if_bridge.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <string.h>
#include <net/if.h>

int main()
{
	int sock_ioctl = -1;
	int sock_ioctl2 = -1;
	int sock_ioctl3 = -1;
	int flag;
	struct ifreq ifr;

	sock_ioctl = socket(AF_LOCAL, SOCK_DGRAM, 0);
	flag = fcntl(sock_ioctl, F_GETFD);
	printf("flag 0x%x \n", flag);
	fcntl(sock_ioctl, F_SETFD, fcntl(sock_ioctl, F_GETFD) | FD_CLOEXEC);
	flag = fcntl(sock_ioctl, F_GETFD);
	printf("flag 0x%x \n", flag);
	flag = ioctl(sock_ioctl, SIOCBRDELBR, "br0");
	printf("ioctl flag 0x%x \n", flag);

	sock_ioctl2 = socket(AF_LOCAL, SOCK_DGRAM, 0);
	flag = fcntl(sock_ioctl2, F_GETFD);
	printf("flag 0x%x \n", flag);
	strncpy(ifr.ifr_name, "eth1", sizeof(ifr.ifr_name));
	ioctl(sock_ioctl2, SIOCGIFINDEX, &ifr);
	printf("ifindex: %d \n", ifr.ifr_ifindex);
	ioctl(sock_ioctl2, SIOCGIFFLAGS, &ifr);
	printf("ifr_flags: 0x%x \n", ifr.ifr_flags);
	
	sock_ioctl3 = socket(AF_LOCAL, SOCK_DGRAM, 0);
	flag = fcntl(sock_ioctl3, F_GETFD);
	printf("flag 0x%x \n", flag);
	ioctl(sock_ioctl3, SIOCGIFINDEX, &ifr);
	printf("ifindex: %d \n", ifr.ifr_ifindex);
	ioctl(sock_ioctl3, SIOCGIFFLAGS, &ifr);
	printf("ifr_flags: 0x%x \n", ifr.ifr_flags);

	printf("sock_ioctl number: %d \n", sock_ioctl);
	printf("sock_ioctl number: %d \n", sock_ioctl2);
	printf("sock_ioctl number: %d \n", sock_ioctl3);
	
	getchar();

	close(sock_ioctl);
	close(sock_ioctl2);
	close(sock_ioctl3);

}

