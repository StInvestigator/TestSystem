#include "TestedUser.h"
#include <thread>
int main()
{
    using std::cout;
    // Обязательное определение админа
    Admin admin;
    // Переменные для сохранения ответов из консоли
    int answ;
    int answ2;
    do
    {
        system("cls");
        cout << "______|[System]|_________________\n\nChoose how you would like to continue:\n2 - Admin\n1 - Tested User\n0 - Close the system\n";
        do
        {
            rightCinCheck(answ);
        } while (answ > 2 || answ < 0);
        if (answ == 2) {
            system("cls");
            cout << "______|[Admin]|_________________\n\nWhat should we do?\n1 - Create a new test\n2 - Change admin`s login data\n3 - Show filtered results of the tests\n4 - Add a new test`s section\n5 - Edit the user from Data Base\n6 - Remove the user from Data Base\n7 - Save the last section to file\n8 - Save all of the sections to file\n9 - Save all of the users to file\n10- Save the last test to file\n11- Save all of the tests to file\n12- Scan the tests from file\n-1- Back to login method screen\n0 - Close the system\n";
            do
            {
                rightCinCheck(answ2);
            } while (answ2 > 12 || answ2 < -1);
            switch (answ2)
            {
            case 1:
                admin.addTest();
                break;
            case 2:
                admin.changeMyLoginData();
                break;
            case 3:
                admin.showResults();
                break;
            case 4:
                admin.addSection();
                break;
            case 5:
                admin.editUser();
                break;
            case 6:
                admin.removeUser();
                break;
            case 7:
                admin.sectionToFile();
                break;
            case 8:
                admin.sectionsToFile();
                break;
            case 9:
                admin.usersToFile();
                break;
            case 10:
                admin.testToFile();
                break;
            case 11:
                admin.testsToFile();
                break;
            case 12:
                admin.testsFromFile();
                break;
            case -1:
                break;
            case 0:
                answ = answ2;
                break;
            }
        }
        if (answ == 1) {
            std::cout << "\nDo you wanna sing in(1) or register(0)?\n";
            do
            {
                rightCinCheck(answ2);
            } while (answ2 > 1 || answ2 < 0);
            system("cls");
            TestedUser* us = nullptr;
            if (answ2 == 1) {
                if (admin.getDataBase().getUsersNumber()) {
                    int i = 3;
                    do
                    {
                        std::string log;
                        std::string pas;
                        std::cout << "\nEnter your login - ";
                        std::getline(std::cin >> std::ws, log);
                        std::cout << "\nEnter your password - ";
                        std::getline(std::cin >> std::ws, pas);
                        if (admin.getDataBase().isUser(log, pas)) {
                            system("cls");
                            us = admin.getDataBase().giveUser(log, pas);
                            std::cout << "\nSuccess! Now you loged in!\n";
                            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                            break;
                        }
                        else {
                            std::cout << "\nWrong log in data! You have a " << --i << " attempts left.";
                        }
                    } while (i != 0);
                    if (i == 0) {
                        std::cout << "\nYou are out of attempts. Moving to registration...";
                        answ2 = 0;
                    }
                }
                else {
                    std::cout << "\nYour account isn`t exist. Moving to registration...\n";
                    answ2 = 0;
                }
            }
            if (answ2 == 0) us = new TestedUser(admin.getDataBase(), admin.getKey());
            system("cls");
            cout << "______|[User]|_________________\n\nWhat should we do?\n1 - Start the new test\n2 - Continue uncompleted test\n3 - End one of the ongoing tests\n4 - Check my previous tests results\n-1- Back to login method screen\n0 - Close the system\n";
            do
            {
                rightCinCheck(answ2);
            } while (answ2 > 4 || answ2 < -1);
            switch (answ2)
            {
            case 1:
                us->startTheTest(admin.getDataBase());
                break;
            case 2:
                us->continueTheTest();
                break;
            case 3:
                us->endTheTest();
                break;
            case 4:
                us->showResults();
                break;
            case 0:
                answ = answ2;
                break;
            case -1:
                break;
            }
        }
        std::cout << "\n\nLoading...";
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    } while (answ);
}