/*
 * h3c.h
 *
 *  Created on: Dec 2, 2014
 *      Author: baoke
 */

#ifndef H3C_H_
#define H3C_H_

#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <net/ethernet.h>

#ifdef AF_LINK
#include <ifaddrs.h>
#include <net/if_dl.h>
#endif

#ifdef AF_PACKET
#include <netpacket/packet.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EAPOL_VERSION 1

#define EAP_TYPE_ID 1
#define EAP_TYPE_MD5 4
#define EAP_TYPE_H3C 7

#define EAPOL_EAPPACKET 0
#define EAPOL_START 1
#define EAPOL_LOGOFF 2
#define EAPOL_KEY 3
#define EAPOL_ASF 4

#define EAP_REQUEST 1
#define EAP_RESPONSE 2
#define EAP_SUCCESS 3
#define EAP_FAILURE 4

#define BUF_LEN 256
#define MD5_LEN 16

#ifndef ETH_P_PAE
#define ETH_P_PAE 0x888E
#endif

#ifndef ETH_ALEN
#define ETH_ALEN 6
#endif

const static char PAE_GROUP_ADDR[] = \
		{0x01, 0x80, 0xc2, 0x00, 0x00, 0x03};

const static char VERSION_INFO[] = \
		{0x06, 0x07, 'b', 'j', 'Q', '7', 'S', 'E', '8', 'B', 'Z', '3', \
		'M', 'q', 'H', 'h', 's', '3', 'c', 'l', 'M', 'r', 'e', 'g', \
		'c', 'D', 'Y', '3', 'Y', '=',0x20,0x20};

struct eapol{
	unsigned char version;
	unsigned char type;
	unsigned short p_len;
}__attribute__ ((packed)) eapol;

struct eap{
	unsigned char code;
	unsigned char id;
	unsigned short d_len;
	unsigned char type;
}__attribute__ ((packed)) eap;

struct packet{
	struct ether_header eth_header;
	struct eapol eapol_header;
	struct eap eap_header;
}__attribute__ ((packed)) packet;

#ifdef AF_LINK
struct sockaddr_ll{
	unsigned short int sll_family;
	unsigned short int sll_protocol;
	int sll_ifindex;
	unsigned short int sll_hatype;
	unsigned char sll_pkttype;
	unsigned char sll_halen;
	unsigned char sll_addr[8];
}__attribute__((packed)) sockaddr;
#endif

int h3c_init(char *_interface);
int h3c_start();
int h3c_logoff();
int h3c_response(int (*success_callback)(), int (*failure_callback)());
void h3c_set_username(char *_username);
void h3c_set_password(char *_password);

#endif /* H3C_H_ */
