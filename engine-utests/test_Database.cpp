#include <gtest/gtest.h>
#include <string>
#include "Database.hpp"
#include "json.hpp"

struct TestValue {
    TestValue(std::string name, std::string message) : name(name), message(message) {}
    std::string name;
    std::string message;
};

class TestDatabase : public db::Database<std::string, TestValue> {

    public:
        virtual bool isLoad(){return false;}
        virtual void load(){}
        virtual void save(){}

        virtual TestValue* getNext(TestValue* record){return nullptr;}
        virtual TestValue* getPrev(TestValue* record){return nullptr;}

        virtual std::string toString(){return std::string();}
        virtual nlohmann::json toJson(){return nlohmann::json();}

};

TEST(test_database, Database) {

    TestDatabase database;
    std::string testID = "FirstTest";
    TestValue *testValue = new TestValue("FirstTest", "FirstTestMessage");
    database.put(testID, testValue);
 
    ASSERT_EQ(database.getByID(testID)->message, testValue->message);
    ASSERT_EQ( database.getDatabase()->size(), 1);
    ASSERT_EQ( database.getValues()->size(), 1);

    std::string secTestID = "SecondTest";
    TestValue *secTestValue = new TestValue("SecondTest", "SecondTestMessage");
    database.put(secTestID, secTestValue);
    ASSERT_EQ(database.getByID(secTestID)->message, secTestValue->message);
    ASSERT_EQ( database.getDatabase()->size(), 2);

    database.remove(secTestID);
    ASSERT_EQ(database.getByID(secTestID), nullptr);
    ASSERT_EQ(database.getDatabase()->size(), 1);

    TestValue *overTestValue = new TestValue("OverwrittenTest", "FirstTestMessageOver");
    database.put(testID, overTestValue);
    ASSERT_EQ(database.getByID(testID)->message, overTestValue->message); 
    ASSERT_EQ(database.getDatabase()->size(), 1);

}
