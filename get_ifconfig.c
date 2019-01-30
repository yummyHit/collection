#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>

#define ETHER_ADDR_LEN 6

const int flag_list[] = {
	IFF_UP,
	IFF_BROADCAST,
	IFF_DEBUG,
	IFF_LOOPBACK,
	IFF_POINTOPOINT,
	IFF_NOTRAILERS,
	IFF_RUNNING,
	IFF_NOARP,
	IFF_PROMISC,
	IFF_ALLMULTI,
	IFF_MASTER,
	IFF_SLAVE,
	IFF_MULTICAST,
	IFF_PORTSEL,
	IFF_AUTOMEDIA,
	IFF_DYNAMIC
};

char * const flag_str[] = {
	"UP",
	"BROADCAST",
	"DEBUG",
	"LOOPBACK",
	"POINTOPOINT",
	"NOTRAILERS",
	"RUNNING",
	"NOARP",
	"PROMISC",
	"ALLMULTI",
	"MASTER",
	"SLAVE",
	"MULTICAST",
	"PORTSEL",
	"AUTOMEDIA",
	"DYNAMIC"
};

int main(int argc, char *argv[]) {
	int fd = 0, i = 0, j = 0, len = 0, flag_num = 0;
	struct ifreq *ifr;
	struct ifconf ifcfg;
	size_t nic_cnt = 32;
	bool lo_flag = false;
	char *save_flag = (char*)malloc(sizeof(char) * sizeof(flag_str));
	char *platform = NULL;

	if(argc != 2) {
		printf("Usage: %s <Redhat or Debian>\n", argv[0]);
		exit(1);
	} else {
		platform = (char*)malloc(sizeof(char) * strlen(argv[1]));
		strncpy(platform, argv[1], strlen(argv[1]));
	}

	if(!save_flag) {
		fprintf(stderr, "save_flag malloc() Error\n");
		exit(1);
	}

	if((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		fprintf(stderr, "socket() Error\n");
		exit(1);
	}

	memset(&ifcfg, 0, sizeof(ifcfg));
	memset(&ifr, 0, sizeof(ifr));

	ifcfg.ifc_len = sizeof(struct ifreq) * nic_cnt;
	ifcfg.ifc_buf = malloc(ifcfg.ifc_len);

	if(!ifcfg.ifc_buf) {
		fprintf(stderr, "ifcfg.ifc_buf malloc() Error\n");
		exit(1);
	}

	if(ioctl(fd, SIOCGIFCONF, &ifcfg) < 0) {
		fprintf(stderr, "ioctl() Error\n");
		exit(1);
	}

	ifr = ifcfg.ifc_req;

	while(i < ifcfg.ifc_len) {
		len = sizeof(ifr);
		memset(save_flag, 0, sizeof(flag_str));
		lo_flag = false;

		if(!ioctl(fd, SIOCGIFADDR, ifr)) {
			if(!strncasecmp(platform, "Debian", 6)) {
				fprintf(stdout, "%-10s", ifr->ifr_name);

				fprintf(stdout, "Link encap:");
				if(!ioctl(fd, SIOCGIFFLAGS, ifr)) {
					flag_num = ifr->ifr_flags;

					if(flag_num & IFF_LOOPBACK) {
						fprintf(stdout, "Local Loopback  ");
						lo_flag = true;
					}
					else 
						fprintf(stdout, "Ethernet  ");

					for(j = 0; j < 16; j++)
						if(flag_num & flag_list[j]) {
							strncat(save_flag, flag_str[j], strlen(flag_str[j]));
							strncat(save_flag, " ", 1);
						}
				}

				if(!ioctl(fd, SIOCGIFHWADDR, ifr) && !lo_flag) {
					fprintf(stdout, "HWAddr ");
					for(j = 0; j < ETHER_ADDR_LEN; j++)
						if(j == ETHER_ADDR_LEN - 1)
							fprintf(stdout, "%02x\n", ((u_char*)ifr->ifr_hwaddr.sa_data)[j]);
						else 
							fprintf(stdout, "%02x:", ((u_char*)ifr->ifr_hwaddr.sa_data)[j]);
				}

				if(lo_flag)
					fprintf(stdout, "\n%10sinet addr:127.0.0.1  ", " ");
				else if(!ioctl(fd, SIOCGIFADDR, ifr))
					fprintf(stdout, "%10sinet addr:%s  ", " ", inet_ntoa(((struct sockaddr_in *)&ifr->ifr_addr)->sin_addr));

				if(!ioctl(fd, SIOCGIFBRDADDR, ifr) && !lo_flag)
					fprintf(stdout, "Bcast:%s  ", inet_ntoa(((struct sockaddr_in *)&ifr->ifr_addr)->sin_addr));

				if(!ioctl(fd, SIOCGIFNETMASK, ifr))
					fprintf(stdout, "Mask:%s\n", inet_ntoa(((struct sockaddr_in *)&ifr->ifr_addr)->sin_addr));

				fprintf(stdout, "%10s%s", " ", save_flag);	// flags

				if(!ioctl(fd, SIOCGIFMTU, ifr))
					fprintf(stdout, " MTU:%d  ", ifr->ifr_mtu);

				if(!ioctl(fd, SIOCGIFMETRIC, ifr)) {
					if(ifr->ifr_metric == 0) 
						fprintf(stdout, "Metric:%d\n", ifr->ifr_metric + 1);
					else 
						fprintf(stdout, "Metric:%d\n", ifr->ifr_metric);
				}

				if(!ioctl(fd, SIOCGIFTXQLEN, ifr))
					fprintf(stdout, "%10stxqueuelen %d\n\n", " ", ifr->ifr_qlen);
			} else if(!strncasecmp(platform, "Redhat", 6)) {
				int flag_sum = 0;
				fprintf(stdout, "%s: ", ifr->ifr_name);
				if(!ioctl(fd, SIOCGIFFLAGS, ifr)) {
					flag_num = ifr->ifr_flags;

					if(flag_num & IFF_LOOPBACK) lo_flag = true;

					for(j = 0; j < 16; j++)
						if(flag_num & flag_list[j]) {
							strncat(save_flag, flag_str[j], strlen(flag_str[j]));
							strncat(save_flag, ",", 1);
							flag_sum += flag_list[j];
						}

					fprintf(stdout, "flags=%d<%s\b> ", flag_sum, save_flag);
				}

				if(!ioctl(fd, SIOCGIFMTU, ifr))
					fprintf(stdout, " mtu:%d\n\t", ifr->ifr_mtu);

				if(lo_flag)
					fprintf(stdout, "inet 127.0.0.1  ");
				else if(!ioctl(fd, SIOCGIFADDR, ifr))
					fprintf(stdout, "inet %s  ", inet_ntoa(((struct sockaddr_in *)&ifr->ifr_addr)->sin_addr));

				if(!ioctl(fd, SIOCGIFNETMASK, ifr))
					fprintf(stdout, "netmask %s  ", inet_ntoa(((struct sockaddr_in *)&ifr->ifr_addr)->sin_addr));

				if(!ioctl(fd, SIOCGIFBRDADDR, ifr) && !lo_flag)
					fprintf(stdout, "broadcast %s\n\t", inet_ntoa(((struct sockaddr_in *)&ifr->ifr_addr)->sin_addr));
				else
					fprintf(stdout, "\n\t");

				if(!ioctl(fd, SIOCGIFHWADDR, ifr) && !lo_flag) {
					fprintf(stdout, "ether ");
					for(j = 0; j < ETHER_ADDR_LEN; j++)
						if(j == ETHER_ADDR_LEN - 1)
							fprintf(stdout, "%02x  ", ((u_char*)ifr->ifr_hwaddr.sa_data)[j]);
						else 
							fprintf(stdout, "%02x:", ((u_char*)ifr->ifr_hwaddr.sa_data)[j]);
				}
				else
					fprintf(stdout, "loop  ");

				if(!ioctl(fd, SIOCGIFTXQLEN, ifr))
					fprintf(stdout, "txqueuelen %d  ", ifr->ifr_qlen);

				if(lo_flag)
					fprintf(stdout, "(Local Loopback)\n\n");
				else
					fprintf(stdout, "(Ethernet)\n\n");
			}
		}

		i += len;
		ifr++;
	}

	if(ifcfg.ifc_buf) 
		free(ifcfg.ifc_buf);
	close(fd);
}
