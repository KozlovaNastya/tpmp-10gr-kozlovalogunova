#include <iostream>
#include "database.h"
#include <clocale>
#ifdef _WIN32
    #include "windows.h"
#endif

bool login() {
    std::string user, pass;
    std::cout << "LOGIN: "; std::cin >> user;
    std::cout << "PASS: "; std::cin >> pass;
    return (user == "admin" && pass == "admin");
}

int main() {
    setlocale(LC_ALL, "Russian");

#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    if (!login()) { std::cout << "Auth failed!"; return 1; }

    Database db("flowers.db");
    int cmd;

    while (true) {
        std::cout << "\n1. Отчет по выручке\n2. Топ композиция\n3. Расход цветов\n4. Добавить заказ\n5. Заказы на дату\n0. Выход\n> ";
        std::cin >> cmd;

        if (cmd == 1) db.getRevenue("2024-01-01", "2024-12-31");
        else if (cmd == 2) db.getTopComposition();
        else if (cmd == 3) db.getFlowerUsage("2024-01-01", "2024-12-31");
        else if (cmd == 5) {
            std::string d; std::cout << "Дата (YYYY-MM-DD): "; std::cin >> d;
            db.getOrdersByDate(d);
        }
        else if (cmd == 0) break;
    }
    return 0;
}
