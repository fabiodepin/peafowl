/**
 *  Test for WhatsApp protocol.
 **/
#include "common.h"

TEST(WhatsappTest, Generic) {
    std::vector<uint> protocols;
    getProtocols("./pcaps/whatsapp.pcap", protocols);
    EXPECT_EQ(protocols[PFWL_PROTOCOL_WHATSAPP], (uint) 134);
}
