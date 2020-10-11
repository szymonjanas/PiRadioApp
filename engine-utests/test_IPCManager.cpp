#include <gtest/gtest.h>
#include <string>
#include "json.hpp"
#include "ipc/IPCRoutes.hpp"
#include "ipc/IPCMessage.hpp"

using namespace nlohmann;

void test_func(ipc::message::IPCRecived& recv, ipc::message::IPCReply& rep)
{
    rep.setState(true);
    rep.setMessage(recv.getRoute());   
}

TEST(add_function_and_execute, ipc_IPCManager) {
    json jData;
    jData["route"] = "test/route";
    jData["value"] = "testValue";
    ipc::message::IPCRecived recv (jData.dump());
    ipc::message::IPCReply rply (true, jData["route"].get<std::string>(), jData["value"]);

    ipc::IPCRoutes manager;
    manager.add("test/route", test_func);    
    
    ipc::message::IPCReply got;
    manager.execute(recv, got);
    ASSERT_EQ(got.toJson(), rply.toJson());
}
