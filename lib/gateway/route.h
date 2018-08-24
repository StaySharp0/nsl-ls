/*
 * gateway/route.h
 *
 * Copyright (c) 2018.
 * YongJun Kim <StaySharp0@gmail.com>
 *
 */

#include <stdint.h>

#define NSL_ROUTE_TABLE_TIMEOUT 10 * 60 * 1000

typedef struct _NODE {
    uint16_t    node_addr;
    uint16_t    next_hop_addr;		// to reach that node
    uint8_t     last_message_seqno;	// in network layer header
    uint32_t    last_timestamp;

    // If node addr == next hop addr, this is my neighbor
    uint16_t    wakeup_interval;
    uint16_t    link_cost;
    uint8_t     link_rssi;
} NODE;