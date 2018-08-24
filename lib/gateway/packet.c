#include "packet.h"

// Private Function


PHY_HEADER  get_phy_haeder (const char* buf) 
{
    PHY_HEADER header;
    
    buf += PHY_HEADER_POINTER;
    header.preamble = *(uint32_t *)(buf);
    buf += sizeof header.preamble;

    header.sync = *(uint8_t *)(buf);
    buf += sizeof header.sync;

    header.length = *(uint8_t *)(buf);

    return header;
}

MAC_HEADER  get_mac_haeder (const char* buf)
{
    MAC_HEADER header;

    buf += MAC_HEADER_POINTER;
    
    header.fcf = *(uint16_t *)(buf);
    buf += sizeof header.fcf;
    
    header.dsn = *(uint8_t *)(buf);
    buf += sizeof header.dsn;
    
    header.destpan = *(uint16_t *)(buf);
    buf += sizeof header.destpan;

    header.dst_addr = *(uint16_t *)(buf);
    buf += sizeof header.dst_addr;
    
    header.src_addr = *(uint16_t *)(buf);
    
    
    return header;
}

NET_HEADER  get_net_haeder (const char* buf)
{
    NET_HEADER header;

    buf += NET_HEADER_POINTER;
    
    header.protocol_type = *(uint8_t *)buf;
    buf += sizeof header.protocol_type;

    header.protocol_version = *(uint8_t *)buf;
    buf += sizeof header.protocol_version;

    header.dst_addr = *(uint16_t *)buf;
    buf += sizeof header.dst_addr;

    header.src_addr = *(uint16_t *)buf;
    buf += sizeof header.src_addr;

    header.message_type = *(uint8_t *)buf;
    buf += sizeof header.message_type;

    header.message_seqno = *(uint8_t *)buf;
    buf += sizeof header.message_seqno;
    
    header.ttl = *(uint8_t *)buf;
    buf += sizeof header.ttl;

    header.payload_len = *(uint8_t *)buf;
    

    return header;
}

APP_BODY    get_app_body   (const char* buf)
{
    APP_BODY header;

    return header;
}