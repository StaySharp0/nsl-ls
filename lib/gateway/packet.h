/*
 * gatway/packet.h
 *
 * Copyright (c) 2018.
 * YongJun Kim <StaySharp0@gmail.com>
 *
 */

#include <stdint.h>     // uint
#include <arpa/inet.h>  // ntohl

// Network header address
#define NET_ADDR_RESERVED   0x0000
#define NET_ADDR_BROADCAST  0xFFFF
#define NET_ADDR_INVALID    0xFFFE
#define NET_ADDR_MULTICAST  0xFFFD
#define NET_ADDR_ROOT       0xFFFC

// NSL Network layer message type
#define NSL_MSG_TYPE_DATA                               0x10
#define NSL_MSG_TYPE_CONTROL                            0x30
#define NSL_MSG_TYPE_CONTROL_RESPONSE                   0x40
#define NSL_MSG_TYPE_ROUTING_BEACON                     0x50    // DIO
#define NSL_MSG_TYPE_ROUTING_BEACON_REQUEST             0x60	// DIS
#define NSL_MSG_TYPE_ROUTE_NOTIFICATION                 0x70	// DAO
#define NSL_MSG_TYPE_ROUTE_NOTIFICATION_REQUEST         0x80
#define NSL_MSG_BCAST                                   0x00
#define NSL_MSG_UPLINK                                  0x01
#define NSL_MSG_DOWNLINK                                0x02


#define PHY_HEADER_POINTER 0
#define PHY_HEADER_LEN 6
#define MAC_HEADER_POINTER 6
#define MAC_HEADER_LEN 9
#define NET_HEADER_POINTER 15
#define NET_HEADER_LEN 10
#define APP_BODY_POINTER 25

typedef struct _PHY_HEADER {
    uint32_t preamble;
    uint8_t sync;
    uint8_t length;
} PHY_HEADER;
// CC2650 will take care of this ⇒ no need to worry

typedef struct _MAC_HEADER {
    uint16_t    fcf;			// see IEEE 802.15.4 MAC header FCF setting page
    uint8_t     dsn;			// sequence number
    uint16_t    destpan;		// panid (group id in tinyos)
    uint16_t    dst_addr;
    uint16_t    src_addr;
} MAC_HEADER;
// 중간에 홀수 바이트 있으므로 alignment/packed 주의할 것

typedef struct _NET_HEADER {
    uint8_t     protocol_type;          // 0x77 - const defined by NSL
    uint8_t     protocol_version;		// 0x01	- 1st version of 0x77 protocol
    uint16_t    dst_addr;
    uint16_t    src_addr;
    uint8_t     message_type;			// DATA, CONTROL, ROUTING-*, etc.
    uint8_t     message_seqno;          // src당 seqno 관리. Mcast filtering에 특별히 중요.
    uint8_t     ttl;
    uint8_t     payload_len;
} NET_HEADER;
// 중간에 홀수 바이트 있으므로 alignment/packed 주의할 것


typedef struct _APP_BODY {
    // 미정
} APP_BODY;

PHY_HEADER  get_phy_haeder (const char*);
MAC_HEADER  get_mac_haeder (const char*);
NET_HEADER  get_net_haeder (const char*);
APP_BODY    get_app_body   (const char*);