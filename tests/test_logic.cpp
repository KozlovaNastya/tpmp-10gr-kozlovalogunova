#include <gtest/gtest.h>
#include "database.h"
#include <fstream>


TEST(DatabaseTest, CreateFileTest) {
    const std::string test_db = "test_run.db";

    remove(test_db.c_str());

    Database db(test_db);

    std::ifstream f(test_db.c_str());
    EXPECT_TRUE(f.good());
}

TEST(AuthTest, AdminLogin) {
    SUCCEED();
}

TEST(DatabaseTest, ExecuteValidSQL) {
    Database db("test_sql.db");
    bool result = db.execute("CREATE TABLE IF NOT EXISTS test (id INT);");
    EXPECT_TRUE(result);
}
