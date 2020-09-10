#include "catch.hpp"

#include "json.hpp"
#include "RadioCommMessage.hpp"

SCENARIO ("test of RadioCommMessage", "[RadioCommMessage]") {

    GIVEN("create test message") {
        radio::Message message (radio::Message::Type::INFO, "test message");

        THEN ("check message") {
            nlohmann::json jmsg = message.toJson();
            REQUIRE(jmsg["type"] == "INFO");
            REQUIRE(jmsg["message"] == "test message");
        }

        GIVEN("add json value") {
            nlohmann::json jdata;
            jdata["num"] = 1;
            jdata["name"] = "xyz";
            message.putValue(jdata);

            THEN("check json value") {
                nlohmann::json jmsg = message.toJson()["value"];
                REQUIRE(jmsg["num"] == 1);
                REQUIRE(jmsg["name"] == "xyz");
            }
        }

        GIVEN("add multiple json values") {
            nlohmann::json jdata;
            jdata["num"] = 1;
            jdata["name"] = "xyz";
            message.putValue(jdata).putValue(R"({"surname": "zyx"})"_json);

            THEN("check multiple json values"){
                nlohmann::json jmsg = message.toJson()["value"];
                REQUIRE(jmsg["num"] == nullptr);
                REQUIRE(jmsg["name"] == nullptr);
                REQUIRE(jmsg["surname"] == "zyx");
            }
        }
    
    }
}
