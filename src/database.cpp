#include "database.h"

Database::Database(const std::string& path) {
    if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия базы!" << std::endl;
    }
}

Database::~Database() { sqlite3_close(db); }

int Database::callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
    }
    std::cout << "\n-------------------------------------------------\n";
    return 0;
}

bool Database::execute(const std::string& sql) {
    char* err = 0;
    if (sqlite3_exec(db, sql.c_str(), callback, 0, &err) != SQLITE_OK) {
        std::cerr << "Ошибка: " << err << std::endl;
        sqlite3_free(err);
        return false;
    }
    return true;
}

void Database::insertOrder(int comp_id, std::string customer, std::string d_get, std::string d_set, int qty) {
    std::string sql = 
        "INSERT INTO \"ORDER\" (KOMPOS_id, customer, date_get, date_set, count) "
        "VALUES (" + std::to_string(comp_id) + ", '" + customer + "', '" + d_get + "', '" + d_set + "', " + std::to_string(qty) + ");";

    std::cout << "Заказ добавлен. Расчет стоимости производится триггером или отдельным SELECT.\n";
    execute(sql);
}

void Database::getRevenue(const std::string& s, const std::string& e) {
    std::cout << "\nВЫРУЧКА ЗА ПЕРИОД:\n";
    std::string sql = "SELECT SUM(count) as total_units FROM \"ORDER\" WHERE date_get BETWEEN '" + s + "' AND '" + e + "';";
    execute(sql);
}

void Database::getTopComposition() {
    std::cout << "\nСАМАЯ ПОПУЛЯРНАЯ КОМПОЗИЦИЯ:\n";
    execute("SELECT k.name, SUM(o.count) as sales FROM \"ORDER\" o JOIN KOMPOS k ON o.KOMPOS_id = k.id GROUP BY k.id ORDER BY sales DESC LIMIT 1;");
}

void Database::getFlowerUsage(const std::string& s, const std::string& e) {
    std::cout << "\nИСПОЛЬЗОВАНИЕ ЦВЕТОВ ПО СОРТАМ:\n";
    std::string sql = "SELECT f.flower, f.sort, SUM(ki.count * o.count) as total_flowers "
                      "FROM \"ORDER\" o "
                      "JOIN KOMPOS_IN ki ON o.KOMPOS_id = ki.KOMPOS_id "
                      "JOIN FLOWERS f ON ki.FLOWERS_id = f.id "
                      "WHERE o.date_get BETWEEN '" + s + "' AND '" + e + "' GROUP BY f.id;";
    execute(sql);
}

void Database::getOrdersByDate(const std::string& date) {
    execute("SELECT * FROM \"ORDER\" WHERE date_get = '" + date + "';");
}

