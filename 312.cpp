#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Класс модели компьютера
class Model {
public:
    string brand;           // марка компьютера
    string processorType;   // тип процессора
    double processorFrequency; // частота процессора (в ГГц)
    int memorySize;         // объем памяти (в ГБ)
    int diskSize;           // объем жесткого диска (в ГБ)
    int videoMemorySize;    // объем видеопамяти (в ГБ)
    double price;           // цена (в условных единицах)
    int stock;              // количество в наличии

    Model() {}  // Конструктор по умолчанию

    Model(string b, string pt, double pf, int ms, int ds, int vms, double p, int s)
        : brand(b), processorType(pt), processorFrequency(pf),
          memorySize(ms), diskSize(ds), videoMemorySize(vms),
          price(p), stock(s) {}
};

// Базовый класс для хранения моделей
class Array {
protected:
    vector<Model> items;  // вектор для хранения моделей

public:
    void add(const Model& model) {
        items.push_back(model);
    }

    bool remove(const string& brand) {
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].brand == brand) {
                items.erase(items.begin() + i);
                return true;  // Успешное удаление
            }
        }
        return false;  // Модель не найдена
    }

    const Model* findByBrand(const string& brand) const { // Изменение: const указатель
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].brand == brand) {
                return &items[i];  // Найдена модель
            }
        }
        return nullptr;  // Модель не найдена
    }

    double totalValue() const { // Изменение: добавлен const
        double total = 0;
        for (size_t i = 0; i < items.size(); ++i) {
            total += items[i].price * items[i].stock;
        }
        return total;
    }

    const vector<Model>& getItems() const {
        return items;
    }
};

// Производный класс для прайс-листа
class Pricelist : public Array {
private:
    double unitValue;  // условная единица в рублях

public:
    Pricelist(double value) : unitValue(value) {}

    void addModel(const Model& model) {
        if (findByBrand(model.brand) == nullptr) {
            add(model);  // Добавляем модель, если она не найдена
        } else {
            cout << "Модель с маркой " << model.brand << " уже существует." << endl;
        }
    }

    void updateModel(const Model& model) {
        Model* foundModel = const_cast<Model*>(findByBrand(model.brand)); // Приведение к неконстантному указателю
        if (foundModel) {
            *foundModel = model;  // Обновляем модель
        } else {
            cout << "Модель с маркой " << model.brand << " не найдена." << endl;
        }
    }

    // Объединение двух прайс-листов
    Pricelist unionWith(const Pricelist& other) {
        Pricelist result(unitValue);  // Создаем новый прайс-лист с той же условной единицей
        for (const auto& model : this->getItems()) {
            result.addModel(model); // Добавляем модели из текущего прайс-листа
        }
        for (const auto& model : other.getItems()) {
            result.addModel(model); // Добавляем модели из другого прайс-листа
        }
        return result;
    }

    // Пересечение двух прайс-листов
    Pricelist intersectionWith(const Pricelist& other) {
        Pricelist result(unitValue);  // Создаем новый прайс-лист с той же условной единицей
        for (const auto& model : this->getItems()) {
            if (other.findByBrand(model.brand) != nullptr) {
                result.addModel(model); // Добавляем модели, которые есть в обоих прайс-листах
            }
        }
        return result;
    }
};

// Пример использования классов
int main() {
    Pricelist pricelist1(1.0);  // Создаем первый прайс-лист
    Pricelist pricelist2(1.0);  // Создаем второй прайс-лист


    Model model1("BrandA", "i5", 2.5, 8, 512, 2, 50000, 10);
    Model model2("BrandB", "i7", 3.0, 16, 1024, 4, 90000, 5);
    Model model3("BrandC", "Ryzen 5", 3.2, 16, 512, 4, 60000, 7);

    // Добавляем модели в первый прайс-лист
    pricelist1.addModel(model1);
    pricelist1.addModel(model2);

    // Добавляем модели во второй прайс-лист
    pricelist2.addModel(model2);
    pricelist2.addModel(model3);

    // Объединение прайс-листов
    Pricelist united = pricelist1.unionWith(pricelist2);
    cout << "Общая стоимость объединенного прайс-листа: " << united.totalValue() << " условных единиц." << endl;

    // Пересечение прайс-листов
    Pricelist intersection = pricelist1.intersectionWith(pricelist2);
    cout << "Общая стоимость пересекающегося прайс-листа: " << intersection.totalValue() << " условных единиц." << endl;

    return 0;
}
