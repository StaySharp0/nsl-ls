#include "packet.h"

// Private Function


PHY_HEADER  get_phy_haeder (const char* buf) 
{
    PHY_HEADER header;
    
    buf += PHY_HEADER_POINTER;

    memcpy(& header.preamble, buf, sizeof header.preamble );
    buf += sizeof header.preamble;
    header.preamble = ntohl( header.preamble );

    memcpy(& header.sync, buf, sizeof header.sync );
    buf += sizeof header.sync;

    memcpy(& header.length, buf, sizeof header.length );
    buf += sizeof header.length;

    return header;
}

MAC_HEADER  get_mac_haeder (const char* buf)
{
    MAC_HEADER header;

    buf += MAC_HEADER_POINTER;
    
    memcpy(& header.fcf, buf, sizeof header.fcf );
    buf += sizeof header.fcf;
    header.fcf = ntohl( header.fcf );

    memcpy(& header.dsn, buf, sizeof header.dsn );
    buf += sizeof header.dsn;
    
    memcpy(& header.destpan, buf, sizeof header.destpan );
    buf += sizeof header.destpan;
    header.destpan = ntohl( header.destpan );

    memcpy(& header.dst_addr, buf, sizeof header.dst_addr );
    buf += sizeof header.dst_addr;
    header.dst_addr = ntohl( header.dst_addr );

    memcpy(& header.src_addr, buf, sizeof header.src_addr );
    buf += sizeof header.src_addr;
    header.src_addr = ntohl( header.src_addr );
    
    return header;
}

NET_HEADER  get_net_haeder (const char* buf)
{
    NET_HEADER header;

    buf += NET_HEADER_POINTER;
    
    memcpy(& header.protocol_type, buf, sizeof header.protocol_type );
    buf += sizeof header.protocol_type;

    memcpy(& header.protocol_version, buf, sizeof header.protocol_version );
    buf += sizeof header.protocol_version;

    memcpy(& header.dst_addr, buf, sizeof header.dst_addr );
    buf += sizeof header.dst_addr;
    header.dst_addr = ntohl( header.dst_addr );

    memcpy(& header.src_addr, buf, sizeof header.src_addr );
    buf += sizeof header.src_addr;
    header.src_addr = ntohl( header.src_addr );

    memcpy(& header.message_type, buf, sizeof header.message_type );
    buf += sizeof header.message_type;

    memcpy(& header.message_seqno, buf, sizeof header.message_seqno );
    buf += sizeof header.message_seqno;
    
    memcpy(& header.ttl, buf, sizeof header.ttl );
    buf += sizeof header.ttl;
    
    memcpy(& header.payload_len, buf, sizeof header.payload_len );
    buf += sizeof header.payload_len;

    return header;
}

APP_BODY    get_app_body   (const char* buf)
{
    APP_BODY header;

    return header;
}