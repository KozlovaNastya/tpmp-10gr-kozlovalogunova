#include <gtest/gtest.h>
#include "database.h"
#include <fstream>

TEST(DatabaseTest, Initialization) {
    const std::string db_name = "test_flowers.db";
    remove(db_name.c_str());
    Database db(db_name);
    
    std::ifstream f(db_name.c_str());
    EXPECT_TRUE(f.good());
}

TEST(DatabaseTest, SchemaExecution) {
    Database db("test_schema.db");
    bool result = db.execute("CREATE TABLE IF NOT EXISTS FLOWERS (id INT, flower TEXT, price REAL);");
    EXPECT_TRUE(result);
}

TEST(ReportTest, RevenueReport) {
    Database db("flowers.db");
    // Проверяем, что функция не падает при вызове с датами
    EXPECT_NO_THROW(db.getRevenue("2024-01-01", "2024-12-31"));
}

TEST(ReportTest, TopCompositionReport) {
    Database db("flowers.db");
    EXPECT_NO_THROW(db.getTopComposition());
}

TEST(ReportTest, FlowerUsageReport) {
    Database db("flowers.db");
    EXPECT_NO_THROW(db.getFlowerUsage("2024-01-01", "2024-12-31"));
}

TEST(ReportTest, OrdersByDate) {
    Database db("flowers.db");
    EXPECT_NO_THROW(db.getOrdersByDate("2024-03-31"));
}

TEST(OrderTest, InsertOrderProcess) {
    Database db("test_orders.db");
    db.execute("CREATE TABLE IF NOT EXISTS \"ORDER\" (id INTEGER PRIMARY KEY, KOMPOS_id INT, customer TEXT, date_get DATE, date_set DATE, count INT);");
    EXPECT_NO_THROW(db.insertOrder(1, "Тестовый Покупатель", "2024-03-31", "2024-04-01", 5));
}

TEST(SystemTest, DatabaseInvalidPath) {
    Database db("/invalid/path/to/db");
    SUCCEED();
}

