#include "catch.hpp"

#include "dbStationJson.hpp"
#include "Database.hpp"
#include "Station.hpp"

SCENARIO ("json file database") {

    GIVEN ("StationJson database"){
        db::StationJson jdb ("fakePath");

        using RECORD = db::RECORD<std::string, radio::Station>;

        WHEN ("add 5 records to database"){
            jdb.put(new RECORD("first-name", new radio::Station("first-name", "first-uri")));
            jdb.put(new RECORD("second-name", new radio::Station("second-name", "second-uri")));
            jdb.put(new RECORD("thrid-name", new radio::Station("thrid-name", "thrid-uri")));
            jdb.put(new RECORD("fourth-name", new radio::Station("fourth-name", "fourth-uri")));
            jdb.put(new RECORD("fifth-name", new radio::Station("fifth-name", "fifth-uri")));

            THEN ("size must be 5"){
                REQUIRE(jdb.getDatabase()->size() == 5);
            }

            THEN ("getNext"){
                std::string nextName = jdb.getNext(jdb.getByID("second-name")->getValue())->getName();
                std::string expectedName = "thrid-name";
                REQUIRE(nextName == expectedName);
                std::string secNextName = jdb.getNext(jdb.getByID("fifth-name")->getValue())->getName();
                std::string secExpectedName = "first-name";
                REQUIRE(secNextName == secExpectedName);
            }

            THEN ("getPrev"){
                std::string nextName = jdb.getPrev(jdb.getByID("second-name")->getValue())->getName();
                std::string expectedName = "first-name";
                REQUIRE(nextName == expectedName);
                std::string secNextName = jdb.getPrev(jdb.getByID("first-name")->getValue())->getName();
                std::string secExpectedName = "fifth-name";
                REQUIRE(secNextName == secExpectedName);
            }

        }


    }







}

