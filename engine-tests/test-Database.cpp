#include "catch.hpp"
#include "Database.hpp"

class testDatabase : public db::Database<std::string, std::string> 
{
    public:
        virtual bool isLoad(){}
        virtual void load(){}
        virtual void save(){}

        virtual std::string* getNext(std::string* record){}
        virtual std::string* getPrev(std::string* record){}
};


SCENARIO ("testDatabase", "[Database]") {
    GIVEN ("testDatabase create") {
        testDatabase tdb;

        using RECORD = db::RECORD<std::string, std::string>;

        WHEN ("add 5 record to testDatabase") {
            tdb.put(new RECORD("first-name", new std::string("first-value")));
            tdb.put(new RECORD("second-name", new std::string("second-value")));
            tdb.put(new RECORD("thrid-name", new std::string("third-value")));
            tdb.put(new RECORD("fourth-name", new std::string("fourth-value")));
            tdb.put(new RECORD("fifth-name", new std::string("fifth-value")));

            THEN ("size must be 5"){
                REQUIRE(tdb.getDatabase()->size() == 5);
            }

            THEN ("can find second name value"){
                REQUIRE (tdb.getByID("second-name") != nullptr);
                REQUIRE (*(tdb.getByID("second-name"))->getValue() == "second-value");
            }

            THEN ("can remove thrid name record"){
                tdb.remove(tdb.getByID("thrid-name"));
                REQUIRE(tdb.getDatabase()->size() == 4);

                THEN ("thrid unavaliable"){
                    REQUIRE(tdb.getByID("thrid-name") == nullptr); 
                }
            }

            THEN ("compare values") {
                std::vector<std::string> testVals = {"first-value", "third-value", "second-value", "fourth-value", "fifth-value"};
                std::vector<std::string*>* vals = tdb.getValues();
                REQUIRE(vals->size() == testVals.size());
                for (int iter = 0; iter < vals->size(); ++iter){
                    int comp = testVals[iter].compare((*(*vals)[iter]));
                    REQUIRE((comp != 0 ? comp : true));
                }
            }

            THEN ("compare bad test values"){
                std::vector<std::string> testVals = {"third-vxlue", "second-vauue", "fourth-vaaue", "fiftt-value", "first-value"};
                std::vector<std::string*>* vals = tdb.getValues();
                REQUIRE(vals->size() == testVals.size());
                for (int iter = 0; iter < vals->size(); ++iter){
                    int comp = testVals[iter].compare((*(*vals)[iter]));
                    REQUIRE((comp != 0 ? true : false));
                }
            }

            THEN ("put new record with same name but diff value"){
                tdb.put(new RECORD("fourth-name", new std::string("fake-value")));
                REQUIRE(tdb.getDatabase()->size() == 5);
                int comp = tdb.getByID("fourth-name")->getValue()->compare("fake-value");
                int compTrue = tdb.getByID("fourth-name")->getValue()->compare("fourth-value");
                REQUIRE((comp != 0 ? comp : true));
                REQUIRE((compTrue == 0 ? comp : true));
            }
        }

    }
}
