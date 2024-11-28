#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Dish { // Блюдо
public:
    string name;
    double price;

    Dish(string n, double p) : name(n), price(p) {}
};

class Cuisine { // это не кузина, это кухня
private:
    string cuisineName;
    vector<Dish> dishes;

public:
    Cuisine(string name) : cuisineName(name) {}

    void addDish(const Dish& dish) {
        dishes.push_back(dish);
    }

    void displayMenu() const {
        cout << cuisineName << ":\n";
        for (size_t i = 0; i < dishes.size(); ++i) {
            cout << i + 1 << ". " << dishes[i].name << " - "
                << fixed << setprecision(2) << dishes[i].price << " руб.\n";
        }
    }

    const Dish& getDish(size_t index) const {
        return dishes[index];
    }

    size_t getMenuSize() const {
        return dishes.size();
    }
};

class Check { // чек
private:
    vector<Dish> orderedDishes;
    double tips;

public:
    Check() : tips(0.0) {}

    void addDish(const Dish& dish) {
        orderedDishes.push_back(dish);
    }

    void addTips(double tip) {
        tips += tip;
    }

    void printCheck() const {
        cout << "\nЧек:\n";
        double total = 0.0;
        for (const auto& dish : orderedDishes) {
            cout << dish.name << " - "
                << fixed << setprecision(2) << dish.price << " руб.\n";
            total += dish.price;
        }
        total += tips;
        cout << "Чаевые: " << fixed << setprecision(2) << tips << " руб.\n";
        cout << "Итого: " << fixed << setprecision(2) << total << " руб.\n";
    }
};

int main() {

    setlocale(LC_ALL, "Rus");

    // Создание кухонь и добавление блюд
    Cuisine russianCuisine("Русская кухня");
    russianCuisine.addDish(Dish("Борщ", 150.0));
    russianCuisine.addDish(Dish("Блины", 170.0));
    russianCuisine.addDish(Dish("Пельмени", 200.0));
    russianCuisine.addDish(Dish("Сырники", 160.5));
    russianCuisine.addDish(Dish("Щи", 150.0));
    russianCuisine.addDish(Dish("РОЛТОН С КУРИЦЕЙ", 100000.0));

    Cuisine japaneseCuisine("Японская кухня");
    japaneseCuisine.addDish(Dish("Суши", 300.0));
    japaneseCuisine.addDish(Dish("Рамен", 250.0));
    japaneseCuisine.addDish(Dish("Тяхан", 550.0));
    japaneseCuisine.addDish(Dish("Удон", 250.0));
    japaneseCuisine.addDish(Dish("Сашими", 800.0));
    japaneseCuisine.addDish(Dish("Якинику", 250.0));

    Cuisine frenchCuisine("Французская кухня");
    frenchCuisine.addDish(Dish("Круассан", 100.0));
    frenchCuisine.addDish(Dish("Рататуй", 400.0));
    frenchCuisine.addDish(Dish("Луковый суп", 500.0));
    frenchCuisine.addDish(Dish("Киш с грибами", 1250.0));
    frenchCuisine.addDish(Dish("Петух в вине", 400.0));

    Cuisine italianCuisine("Итальянская кухня");
    italianCuisine.addDish(Dish("Паста", 250.0));
    italianCuisine.addDish(Dish("Пицца", 500.0));
    italianCuisine.addDish(Dish("Ризотто", 1250.5));
    italianCuisine.addDish(Dish("Минимтроне", 340.6));


    Check check;

    while (true) {
        // Отображение меню всех кухонь
        cout << "\nВыберите кухню:\n";
        cout << "1. Русская кухня\n";
        cout << "2. Японская кухня\n";
        cout << "3. Французская кухня\n";
        cout << "4. Итальянская кухня\n";
        cout << "0. Завершить выбор\n";

        int choice;
        cin >> choice;

        if (choice == 0) break;

        // Выбор кухни и отображение меню
        Cuisine* selectedCuisine = nullptr;
        switch (choice) {
        case 1: selectedCuisine = &russianCuisine; break;
        case 2: selectedCuisine = &japaneseCuisine; break;
        case 3: selectedCuisine = &frenchCuisine; break;
        case 4: selectedCuisine = &italianCuisine; break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            continue;
        }

        selectedCuisine->displayMenu();

        // Множественный выбор блюд
        cout << "Введите номера блюд для добавления в чек (например, 1,2,3) или 0 для завершения: ";

        string input;
        cin.ignore(); // игнорируем предыдущий ввод
        getline(cin, input);

        if (input == "0") break;

        size_t pos = 0;
        while ((pos = input.find(',')) != string::npos) {
            int dishChoice = stoi(input.substr(0, pos));
            if (dishChoice > 0 && dishChoice <= selectedCuisine->getMenuSize()) {
                Dish selectedDish = selectedCuisine->getDish(dishChoice - 1);
                check.addDish(selectedDish);
                cout << "Блюдо добавлено: " << selectedDish.name << "\n";
            }
            else {
                cout << "Неверный номер блюда: " << dishChoice << "\n";
            }
            input.erase(0, pos + 1);
        }

        // Обработка последнего блюда
        if (!input.empty()) {
            int dishChoice = stoi(input);
            if (dishChoice > 0 && dishChoice <= selectedCuisine->getMenuSize()) {
                Dish selectedDish = selectedCuisine->getDish(dishChoice - 1);
                check.addDish(selectedDish);
                cout << "Блюдо добавлено: " << selectedDish.name << "\n";
            }
            else {
                cout << "Неверный номер блюда: " << dishChoice << "\n";
            }
        }
    }

    // Запрос чаевых
    double tip;
    cout << "Введите чаевые: ";
    cin >> tip;
    check.addTips(tip);

    // Печать чека
    check.printCheck();

    return 0;
}