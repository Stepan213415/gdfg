#include <iostream>
#include <iomanip>
#include "lift.hpp"
#include <windows.h>
#include <locale>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#endif
}

template <typename T>
void printLiftState(const Lift<T>& lift) {
    cout << "---------------------------------\n";
    cout << "           СТАН ЛІФТА          \n";
    cout << "---------------------------------\n";
    cout << " Загальний стан: " << lift.GetGeneralStateName() << "\n";
    cout << " Стан двигуна:   " << lift.GetEngineStateName() << "\n";
    cout << " Стан дверей:    " << lift.GetDoorStateName() << "\n";
    cout << " Поточний поверх: " << lift.GetCurrentFloor() << "\n";
    cout << " Цільовий поверх: " << lift.GetTargetFloor() << "\n";
    cout << fixed << setprecision(1);
    cout << " Навантаження:   " << lift.GetCurrentLoad() << " кг\n";
    cout << "---------------------------------\n\n";
}

void printMenu() {
    cout << "         ПУЛЬТ КЕРУВАННЯ         \n";
    cout << "1. Старт виклику (на поверх)\n";
    cout << "2. Кінець виклику (прибуття)\n";
    cout << "3. Завантаження кабіни (вказати вагу)\n";
    cout << "4. Запуск (з кабіни на поверх)\n";
    cout << "5. Стоп (прибуття)\n";
    cout << "0. Скинути стан (Reset)\n";
    cout << "t. Тестування шаблону (float, short)\n";
    cout << "q. Вихід\n\n";
    cout << "Ваш вибір: ";
}

int main() {
    setlocale(LC_ALL, "Ukrainian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Lift<int> myLift;
    char choice;

    do {
        clearScreen();
        printLiftState(myLift);
        printMenu();

        cin >> choice;

        int floor;
        double load;

        switch (choice) {
            case '1':
                cout << "Введіть цільовий поверх (1-24): ";
                cin >> floor;
                myLift.StartCall(floor);
                break;
            case '2':
                myLift.EndCall();
                break;
            case '3':
                cout << "Введіть навантаження (кг): ";
                cin >> load;
                myLift.LoadCabin(load);
                break;
            case '4':
                cout << "Введіть цільовий поверх (1-24): ";
                cin >> floor;
                myLift.Start(floor);
                break;
            case '5':
                myLift.Stop();
                break;
            case '0':
                myLift.Reset();
                break;
            case 't': case 'T': {
                clearScreen();
                cout << "     ТЕСТУВАННЯ ШАБЛОНУ З ІНШИМИ ТИПАМИ    \n\n";

                cout << "1. Тип координат 'short' (Маленький ліфт):\n";
                Lift<short> shortLift(2, 50.0);
                printLiftState(shortLift);

                cout << "2. Тип координат 'float' (Високоточний ліфт):\n";
                Lift<float> floatLift(1.5f, 100.0, 0.0f, 10.0f);
                floatLift.StartCall(2.5f);
                printLiftState(floatLift);

                cout << "   Завершення виклику для float ліфта:\n";
                floatLift.EndCall();
                printLiftState(floatLift);

                cout << "\nНатисніть Enter для продовження...";
                cin.clear();
                cin.ignore(10000, '\n');
                cin.get();
                break;
            }
            case 'q': case 'Q':
                cout << "Завершення роботи.\n";
                break;
            default:
                cout << "Некоректний вибір. Натисніть Enter.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                cin.get();
                break;
        }
    } while (choice != 'q' && choice != 'Q');

    return 0;
}
