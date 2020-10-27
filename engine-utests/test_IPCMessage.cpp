#include <gtest/gtest.h>
#include "json.hpp"
#include "ipc/IPCMessage.hpp"
#include <iostream>
using namespace nlohmann;

json jdata = {
    {"route","test/route/to/sth"}, 
    {"value", {"name", "fakeName"}}
    };

TEST(creating_with_value, message_IPCRecive) {
    std::string strData = jdata.dump();
    ipc::message::IPCRecived ipcMsg (strData);
    ASSERT_EQ(ipcMsg.getRoute(), jdata["route"].get<std::string>());
    ASSERT_EQ(ipcMsg.getValue(), jdata["value"]);
}

TEST(creating_without_value, message_IPCRecive) {
    json jtemp;
    jtemp["route"] = jdata["route"].get<std::string>();
    std::string strData = jtemp.dump();
    ipc::message::IPCRecived ipcMsg (strData);
    ASSERT_EQ(ipcMsg.getRoute(), jtemp["route"].get<std::string>());
    ASSERT_EQ(ipcMsg.getValue(), json());
}

TEST(creating_with_value, message_IPCReply) {
    json testMsg = {{"code", 200}, {"message", "testMessage"}, {"value", "someText"}};
    ipc::message::IPCReply ipcMsg ( testMsg["code"].get<short>(),
                                    testMsg["message"].get<std::string>(),
                                    testMsg["value"]);
    ASSERT_EQ(ipcMsg.toJson(), testMsg);
}

TEST(creating_without_value, message_IPCReply) {
    json testMsg = {{"code", 200}, {"message", "testMessage"}};
    ipc::message::IPCReply ipcMsg ( testMsg["code"].get<short>(),
                                    testMsg["message"].get<std::string>());
    testMsg["value"] = json();
    ASSERT_EQ(ipcMsg.toJson(), testMsg);
}
