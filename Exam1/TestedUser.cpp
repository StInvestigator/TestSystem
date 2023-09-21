#include "TestedUser.h"
#include <thread>
#include <Algorithm>


TestedUser::TestedUser(DataBase& db, const int key): User(),fullName{""},adress{""},phoneNumber{1234567890}
{
  

        do
        {
            std::cout << "\nEnter your login - ";
            std::getline(std::cin >> std::ws, login);
            if (!db.usersLoginCheck(login)) {
                std::cout << "\nYour login is already taken!\n";
            }
        } while (!db.usersLoginCheck(login));
        std::cout << "\nEnter your password - ";
        std::getline(std::cin >> std::ws, password);
        std::cout << "\nEnter your full name - ";
        std::getline(std::cin >> std::ws, fullName);
        std::cout << "\nEnter your home adress - ";
        std::getline(std::cin >> std::ws, adress);
        std::cout << "\nEnter your phone number - ";
        do {
            std::cin >> phoneNumber; 
            if (!std::cin) {
                std::cin.clear(); 
                std::cin.ignore(32767, '\n');
                std::cin >> phoneNumber;
            }
        } while (!std::cin);
        db.addUser(*this,key);
}

bool TestedUser::operator<(const TestedUser& us) const
{
	if (login < us.login) return true;
	else return false;
}

void TestedUser::startTheTest(const DataBase& db)
{
    if (reminder()) {
        if (db.getTests().size() && db.isUser(login,password)) {
            using std::cout;
            using std::cin;
            int count = 0;
            int answ;
            cout << "\nChoose the section of the test:\n";
            std::cout << "---------------\n";
            for (auto& el : db.getSections()) {
                cout << "Section " << ++count << "# " << el << std::endl;
                std::cout << "---------------\n";
            }
            cout << "\nEnter the number of choosen section - ";
            do
            {
                rightCinCheck(answ);
            } while (answ > count || answ < 1);
            cout << "\nChoose the test:\n";
            count = 0;
            std::cout << "---------------\n";
            for (auto& el : db.getTestsBySection(db.getSections().at(answ - 1))) {
                cout << "Test " << ++count << "# " << el.getTitle() << " | " << el.getQuestionsNumber() << " Questions" << std::endl;
                std::cout << "---------------\n";
            }
            cout << "\nEnter the number of choosen test - ";
            do
            {
                rightCinCheck(answ);
            } while (answ > count || answ < 1);
            ongoingTests.push_back(db.getTests().at(answ - 1));
            cout << "\nStarting the test...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            bool isComplete = ongoingTests.back().startTheTest();
            if (isComplete) { 
                endTheTest(ongoingTests.back()); 
            }
        }
        else {
            std::cout << "\nSorry we have no tests yet!\n";
        }
    }
    else {
        continueTheTest();
    }
}

bool TestedUser::reminder() const
{
    if (ongoingTests.size()) {
        int answ;
        std::cout << "\nYou still have " << ongoingTests.size()
            << " uncompleted tests, are you sure want to start another one?\n1 - Yes, start another test\n0 - No, lets finish the past tests\n";
        do
        {
            rightCinCheck(answ);
        } while (answ > 1 || answ < 0);
        return answ;
    }
    return true;
}

void TestedUser::continueTheTest()
{
    if (ongoingTests.size()) {
        std::cout << "\nYou have " << ongoingTests.size() << " ongoing tests.\n"; \
        int count = 0;
        int answ;
        std::cout << "---------------\n";
        for (auto& el : ongoingTests)
        {
            std::cout << "Test " << ++count << "# " << el.getTitle() << " | " << el.getQuestionsNumber() << " Questions" << std::endl;
            std::cout << "---------------\n";
        }
        std::cout << "\nEnter the number of the test which you wanna continue - ";
        do
        {
            rightCinCheck(answ);
        } while (answ > count || answ <= 0);
        if (ongoingTests.at(answ - 1).startTheTest()) {
            endTheTest(ongoingTests.at(answ - 1));
        }
    }
    else {
        std::cout << "\nYou haven`t ongoing tests!\n";
    }
}

void TestedUser::endTheTest()
{
    if (ongoingTests.size()==0) {
        std::cout << "\nYou have no ongoing tests\n";
    }
    else if (ongoingTests.size() == 1) {
        myResults.push_back(ongoingTests.back().getResult());
        ongoingTests.clear();
        myResults.back().showResults();
    }
    else {
        std::cout << "\nYou have " << ongoingTests.size() << " ongoing tests.\n"; \
        int count = 0;
        int answ;
        std::cout << "---------------\n";
        for  (auto& el : ongoingTests)
        {
            std::cout << "Test " << ++count << "# " << el.getTitle() << " | " << el.getQuestionsNumber() << " Questions" << std::endl;
            std::cout << "---------------\n";
        }
        std::cout << "\nEnter the number of the test which you wanna end - ";
        do
        {
            rightCinCheck(answ);
        } while (answ > count || answ <= 0);
        endTheTest(ongoingTests.at(answ - 1));
    }
}

void TestedUser::endTheTest(const Test& t)
{
    if (ongoingTests.size()) {
        auto it = std::find(ongoingTests.begin(), ongoingTests.end(), t);
        if (it != ongoingTests.end()) {
            myResults.push_back(it->getResult());
            myResults.back().showResults();
            ongoingTests.erase(it);
        }
    }
    else {
        std::cout << "\nYou haven`t ongoing tests!\n";
    }
}

void TestedUser::showResults()
{
    if (myResults.size()) {
        std::cout << "---------------";
        for (auto& el : myResults) {
            el.showResults();
            std::cout << "---------------\n";
        }
    }
    else {
        std::cout << "\nYou have no results yet!\n";
    }
}