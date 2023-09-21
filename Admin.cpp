#define _CRT_SECURE_NO_WARNINGS
#include "Admin.h"
#include <direct.h>
#include <Algorithm>
#include <ctime>

Admin::Admin() : key{255}
{
    std::ofstream fout;
    fout.open("D:\\Exam#1Files\\Users\\Users.txt", std::fstream::out);
    // «ащита в случае отсутстви€ на устройстве диска D
    if (!fout) {
        exit(-1);
    }
    fout.close();
    int i;
    std::cout << "0 - Register new Admin | 1 - Log in existent account";
    do {
        std::cout << std::endl;
        std::cin >> i;
    } while (i != 0 && i != 1);
    switch (i)
    {
    case 0:
        reg();
        return;
    case 1:
        *this = Admin(true);
        return;
    }
}

void Admin::reg()
{
    using std::cout;
    using std::cin;
    _mkdir("D:\\Exam#1Files"); 
    _mkdir("D:\\Exam#1Files\\Users");
    _mkdir("D:\\Exam#1Files\\TestingData"); 
    _mkdir("D:\\Exam#1Files\\TestingData\\Sections");
    _mkdir("D:\\Exam#1Files\\TestingData\\Tests");
    _mkdir("D:\\Exam#1Files\\TestingData\\Results");
    cout << "Enter the Admin's login - ";
    cin >> login;
    cout << "Enter the Admin's password - ";
    cin >> password;
    cout << "Enter the secret key of files encrypt (integer number) - ";
    do {
        std::cin >> key;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cin >> key;
        }
    } while (!std::cin);
    std::ofstream fout;
    fout.open("D:\\Exam#1Files\\TestingData\\Sections\\Sections.txt", std::fstream::out);
    fout.close();
    fout.open("D:\\Exam#1Files\\TestingData\\Tests\\Tests.txt", std::fstream::out);
    fout.close();
    fout.open("D:\\Exam#1Files\\Admin.txt", std::fstream::out);
    char c;
    int i = 0;
    fout << static_cast<char>('e' + key);
    fout << '\n';
    while (login[i])
    {
        c = (login[i++] + key);
        fout << c;
    }
    fout << '\n';
    i = 0;
    while (password[i])
    {
        c = (password[i++] + key);
        fout << c;
    }
    fout.close();
}

Admin::Admin(bool)
{
    std::ifstream fin;
    fin.open("D:\\Exam#1Files\\Admin.txt", std::fstream::in);
    if (fin) {
        std::cout << "Enter the key of encrypt - ";
        rightCinCheck(key);
        char c;
        fin.get(c);
        if (static_cast<char>(c - key) == 'e') {
            fin.get(c);
            fin.get(c);
            while (c != '\n' && !fin.eof())
            {
                login += (c - key);
                fin.get(c);
            }
            fin.get(c);
            while (!fin.eof())
            {
                password += (c - key);
                fin.get(c);
            }
            int i = 3;
            do
            {
                std::string log;
                std::string pass;
                std::cout << "\nEnter the login - ";
                std::cin >> log;
                std::cout << "\nEnter the password - ";
                std::cin >> pass;
                if (log != login || pass != password) {
                    std::cout << "\nError...(" << --i << " tries left)\n";
                    if (i == 0) {
                        std::cout << "\nYou dont have more tries. Moving to registration...\n";
                        reg();
                    }
                }
                else {
                    sectionsFromFile();
                    break;
                }
            } while (true);
        }
        else {
            std::cout << "Wrong key! Moving to registration...\n";
            reg(); 
        }
    }
    else {
        std::cout << "The File didn`t exist. Moving to registration...\n";
        reg(); 
    }
    fin.close();
}

void Admin::addSection() {
    std::cout << "\nEnter the section - "; 
    std::string sec; 
    std::getline(std::cin >> std::ws, sec);
    if (db.sections.size() == 0) {
        db.sections.push_back(sec);
        return;
    }
    for (auto& el : db.sections) {
        if (el == sec) {
            break;
        }
        if (el == db.sections.back()) {
            db.sections.push_back(sec);
        }
    }
}


void Admin::addTest()
{
    int answ;
    if (db.sections.size() == 0) {
        std::cout << "\nYou have no sections!\n0 - Exit adding\n1 - Create a new one\n";
        std::string quest;
        do
        {
            rightCinCheck(answ);
        } while (answ>1 || answ<0);
        switch (answ)
        {
        case 0:
            return;
        case 1:
            std::cout << "\nOk, enter your section - ";
            std::getline(std::cin >> std::ws, quest);
            db.sections.push_back(quest);
            break;
        }
    }
    if(db.sections.size()!=0) {
        int count = 0;
        std::cout << "---------------\n";
        for (auto& el : db.sections) {
            std::cout << "Section " << ++count << "# " << el << std::endl;
            std::cout << "---------------\n";
        }
        std::cout << "\nChoose the number of section for the test:\n";
        do
        {
            rightCinCheck(answ);
        } while (answ<1 || answ>count);
        std::string name;
        std::cout << "\nEtner the title of the test - ";
        std::getline(std::cin >> std::ws, name);
        db.tests.push_back(Test(name, db.sections.at(answ - 1)));
        std::cout << "\nHow much questions does this test should have?(2 - MIN, 50 - MAX)\n";
        do
        {
            rightCinCheck(answ);
        } while (answ<2 || answ>50);
        for (int i = 0; i < answ; i++)
        {
            db.tests.back().addQuestion();
        }
    }
}

void Admin::changeMyLoginData()
{
    std::cout << "\nEnter ther new login - ";
    std::cin >> login;
    std::cout << "\nEnter ther new password - ";
    std::cin >> password;
    std::ofstream fout;
    fout.open("D:\\Exam#1Files\\Admin.txt", std::fstream::out);
    char c;
    int i = 0;
    fout << static_cast<char>('e' + key);
    fout << '\n';
    while (login[i])
    {
        c = (login[i++] + key);
        fout << c;
    }
    fout << '\n';
    i = 0;
    while (password[i])
    {
        c = (password[i++] + key);
        fout << c;
    }
    fout.close();
}

char* Admin::toChar(int num) {
    int temp = num;
    int len = 0;

    while (temp > 0) {
        len++;
        temp /= 10;
    }
    if (len != 0) {
        char result[100];
        for (int i = len - 1; i >= 0; i--) {
            result[i] = num % 10 + '0';
            num /= 10;
        }
    result[len] = '\0';
    return result;
    }
    else {
        char result[3];
        result[0] = '0';
        result[1] = '1';
        result[2] = '\n';
        return result;
    }
}

void Admin::showResults()
{
    std::cout << "\nView test results in general\n1 - by category\n2 - by specific tests\n3 - by specific users\n";
    int count = 0;
    int answ;
    std::vector<Result> results;
    do
    {
        rightCinCheck(answ);
    } while (answ > 3 || answ < 1);
    switch (answ)
    {
    case 1:
        if (db.sections.size()) {
            std::cout << "---------------\n";
            for (auto& el : db.sections) {
                std::cout << "Section " << ++count << "# " << el << std::endl;
                std::cout << "---------------\n";
            }
            std::cout << "\nChoose the number of tests section to filter the results:\n";
            do
            {
                rightCinCheck(answ);
            } while (answ > count || answ < 1);
            for (auto& us : db.users) {
                for (auto& res : us->myResults) {
                    if (res.atributes.section == db.sections.at(answ - 1)) {
                        std::cout << "\nTestee - " << us->login;
                        results.push_back(res);
                        results.back().showResults();
                    }
                }
            }
        }
        else {
            std::cout << "\nWe haven`t any section yet!\n";
        return;
        }
        break;
    case 2:
        if (db.tests.size()) {
            std::cout << "---------------\n";
            for (auto& el : db.tests) {
                std::cout << "Test " << ++count << "# " << el.atributes.title << std::endl;
                std::cout << "---------------\n";
            }
            std::cout << "\nChoose the number of test to filter the results:\n";
            do
            {
                rightCinCheck(answ);
            } while (answ > count || answ < 1);
            for (auto& us : db.users) {
                for (auto& res : us->myResults) {
                    if (res.atributes.title == db.tests.at(answ - 1).atributes.title) {
                        std::cout << "\nTestee - " << us->login;
                        results.push_back(res);
                        results.back().showResults();
                    }
                }
            }
        }
        else {
            std::cout << "\nWe have no tests yet!\n";
        return;
        }
        break;
    case 3:
        if (db.users.size()) {
            std::vector<TestedUser> vec;
            std::cout << "---------------\n";
            for (auto& el : db.users) {
                vec.push_back(*el);
                std::cout << "User " << ++count << "# " << el->login << std::endl;
                std::cout << "---------------\n";
            }
            std::cout << "\nChoose the number of user to filter the results:\n";
            do
            {
                rightCinCheck(answ);
            } while (answ > count || answ < 1);
            for (auto& us : db.users) {
                if (us->login == vec.at(answ - 1).login) {
                    for (auto& res : us->myResults) {
                        results.push_back(res);
                        results.back().showResults();
                    }
                    break;
                }
            }
        }
        else {
            std::cout << "\nWe have no users yet!\n";
        return;
        }
        break;
    }
    if (results.size() == 0) {
        std::cout << "\nWe haven`t any results for you yet\n";
        return;
    }
    std::cout << "\nDo you wanna save those results to file?\n1 - Yes\n0 - No\n";
    do
    {
        rightCinCheck(answ);
    } while (answ > 1 || answ < 0);
    if (answ == 1) {
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        std::string way = "D:\\Exam#1Files\\TestingData\\Results\\Result_";
        way += toChar(now->tm_hour);
        way += 'h';
        way += toChar(now->tm_min);
        way += 'm';
        way += toChar(now->tm_sec);
        way += 's_';
        way += toChar(now->tm_mday);
        way += '.';
        way += toChar(now->tm_mon + 1);
        way += '.';
        way += toChar(now->tm_year + 1900);
        way += ".txt";
        std::ofstream fout(way, std::ios::out);
        if (fout) {
            for (auto& el : results) {
                fout << "Results of the test \"" << el.atributes.title << "\":\nSection - " << el.atributes.section << "\nGrade - " << el.grade << " / 12\nPercentage of right answers - "
                    << el.percentage << "%\nNumber of right answers - " << el.rightAnswers << "/" << el.numberOfQuestions << "\n\n";
            }
        }
        else {
            std::cout << "\nError with files!\n";
        }
    }
}

void Admin::editUser()
{
    if (db.users.size()) {
        int count = 0, answ, asnwlp;
        std::cout << "---------------\n";
        for (auto& us : db.users) {
            std::cout << "\nUser " << ++count << "#\tLogin -\t" << us->login << "\n\tPass -\t" << us->password << std::endl;
            std::cout << "---------------\n";
        }
        std::cout << "\nEnter the number of the user you want to change:\n";
        do
        {
            rightCinCheck(answ);
        } while (answ > count || answ < 1);
        std::cout << "\n What do you wanna edit?\n1 - Login\n0 - Password\n";
        do
        {
            rightCinCheck(asnwlp);
        } while (asnwlp > 1 || asnwlp < 0);
        count = 0;
        for (auto& el : db.users) {
            ++count;
            if (count == answ) {
                if (asnwlp == 0) {
                    std::cout << "\nEnter the new password - ";
                    std::cin >> el->password;
                }
                if (asnwlp == 1) {
                    std::cout << "\nEnter the new login - ";
                    std::cin >> el->login;
                }
                break;
            }
        }
        usersToFile();
    }
    else {
        std::cout << "\nWe have no users yet!\n";
    }
}

void Admin::usersToFile()
{
    if (db.users.size()) {
        std::ofstream fout;
        fout.open("D:\\Exam#1Files\\Users\\Users.txt", std::fstream::out);
        char c;
        int i;
        for (auto& us : db.users) {
            fout << '\n';
            i = 0;
            while (us->login[i])
            {
                c = (us->login[i++] + key);
                fout << c;
            }
            fout << '\n';
            i = 0;
            while (us->password[i])
            {
                c = (us->password[i++] + key);
                fout << c;
            }
            fout << '\n';
        }
        fout.close();
    }
    else {
        std::cout << "\nError! We have no users yet!\n";
    }
}

void Admin::removeUser()
{
    if (db.users.size()) {
        int count = 0, answ;
        std::cout << "---------------\n";
        for (auto& us : db.users) {
            std::cout << "\nUser " << ++count << "#\tLogin -\t" << us->login << "\n\tPass -\t" << us->password << std::endl;
            std::cout << "---------------\n";
        }
        std::cout << "\nEnter the number of the user you want to remove:\n";
        do
        {
            rightCinCheck(answ);
        } while (answ > count || answ < 1);
        count = 0;
        for (auto& el : db.users) {
            ++count;
            if (count == answ) {
                db.users.erase(el);
                break;
            }
        }
    }
    else {
        std::cout << "\nWe have no users yet!\n";
    }
}

void Admin::sectionToFile()
{
    if (db.sections.size()) {
        std::ofstream fout;
        fout.open("D:\\Exam#1Files\\TestingData\\Sections\\Sections.txt", std::fstream::app);
        if (fout) {
            fout << db.sections.back() << '\n';
        }
        else {
            std::cout << "\nError with file!\n";
        }
        fout.close();
    }
    else {
        std::cout << "\nWe have no sections!\n";
    }
}

void Admin::sectionsToFile()
{
    if (db.sections.size()) {
        std::ofstream fout;
        fout.open("D:\\Exam#1Files\\TestingData\\Sections\\Sections.txt", std::fstream::out);
        if (fout) {
            for (auto& el : db.sections) {
                fout << el << '\n';
            }
        }
        else {
            std::cout << "\nError with file!\n";
        }
        fout.close();
    }
    else {
        std::cout << "\nWe have no sections!\n";
    }
}

void Admin::sectionsFromFile()
{
    std::ifstream fin;
    fin.open("D:\\Exam#1Files\\TestingData\\Sections\\Sections.txt", std::fstream::in);
    if (fin) {
        std::string sec;
        char c;
        while (!fin.eof())
        {
            c = fin.get();
            while (c != '\n' && c!=EOF) {
                sec += c;
                c = fin.get();
            }
            if (sec.size()>1) {
                db.sections.push_back(sec);
                sec.clear();
            }
        }
    }
    else {
        std::cout << "\nFile didt exist!\n";
    }
}

void Admin::testToFile()
{
    if (db.tests.size()) {
        std::ofstream fout;
        fout.open("D:\\Exam#1Files\\TestingData\\Tests\\Tests.txt", std::fstream::app);
        if (fout) {
            fout << "T-" << db.tests.back().atributes.title << '\n'
                << "S-" << db.tests.back().atributes.section << '\n'
                << db.tests.back().questions.size() << '\n';
            int count = 0;
            for (auto& el : db.tests.back().questions) {
                fout << "q-" << el.question << '\n'
                    << el.possibleAnswers.size() << '\n';
                for (auto& ans : el.possibleAnswers) {
                    fout << ans;
                    for (auto& cor : el.rightAnswers) {
                        if (ans == cor) {
                            fout << " ++";
                            break;
                        }
                    }
                    fout << '\n';
                }
            }
        }
        else {
            std::cout << "\nError with file!\n";
        }
        fout.close();
    }
    else {
        std::cout << "\nWe have no tests!\n";
    }
}

void Admin::testsToFile()
{
    if (db.tests.size()) {
        std::ofstream fout;
        fout.open("D:\\Exam#1Files\\TestingData\\Tests\\Tests.txt", std::fstream::out);
        if (fout) {
            for (auto& test : db.tests) {
                fout << "T-" << test.atributes.title << '\n'
                    << "S-" << test.atributes.section << '\n'
                    << test.questions.size() << '\n';
                int count = 0;
                for (auto& el : test.questions) {
                    fout << "q-" << el.question << '\n'
                        << el.possibleAnswers.size() << '\n';
                    for (auto& ans : el.possibleAnswers) {
                        fout << ans;
                        for (auto& cor : el.rightAnswers) {
                            if (ans == cor) {
                                fout << " ++";
                                break;
                            }
                        }
                        fout << '\n';
                    }
                }
            }
        }
        else {
            std::cout << "\nError with file!\n";
        }
        fout.close();
    }
    else {
        std::cout << "\nWe have no tests!\n";
    }
}

void Admin::testsFromFile() 
{
    std::ifstream fin;
    fin.open("D:\\Exam#1Files\\TestingData\\Tests\\Tests.txt", std::fstream::in);
    if (fin) {
        std::string tit;
        std::string sec;
        std::string quest;
        std::string answ;
        std::vector<std::string> pa;
        std::list <std::string> ra;
        std::vector<Question> quests;
        char c = fin.get();
        while (!fin.eof())
        {
            if (c == 'T') {
                c = fin.get();
                c = fin.get();
                while (c!='\n')
                {
                    tit += c;
                    c = fin.get();
                }
                c = fin.get();
                if (c == 'S') {
                    c = fin.get();
                    c = fin.get();
                    while (c != '\n')
                    {
                        sec += c;
                        c = fin.get();
                    }
                    char cap[2];
                    int size;
                    cap[0] = (c = fin.get());
                    c = fin.get();
                    if (c != '\n') {
                        cap[1] = c;
                        size = (cap[0] - '0') * 10 + (cap[1] - '0');
                        c = fin.get();
                    }
                    else {
                        size = cap[0] - '0';
                    }
                    c = fin.get();
                    for (int i = 0; i < size; i++)
                    {
                        if (c == 'q') {
                            c = fin.get();
                            c = fin.get();
                            while (c!='\n')
                            {
                                quest += c;
                                c = fin.get();
                            }
                            c = fin.get();
                            int size2 = c - '0';
                            c = fin.get();
                            c = fin.get();
                            for (int i = 0; i < size2; i++)
                            {
                                while (c!='\n')
                                {
                                    answ += c;
                                    c = fin.get();
                                    if (c == ' ') {
                                        c = fin.get();
                                        if (c == '+') {
                                            c = fin.get();
                                            if (c == '+'){
                                                ra.push_back(answ);
                                                c = fin.get();
                                            }
                                            else {
                                                answ += ' ';
                                                answ += '+';
                                                if (c != '\n') {
                                                    answ += c;
                                                    c = fin.get();
                                                }
                                            }
                                        }
                                        else {
                                            answ += ' ';
                                            if (c != '\n') {
                                                answ += c;
                                                c = fin.get();
                                            }
                                        }
                                    }
                                }
                                pa.push_back(answ);
                                answ = "";
                                c = fin.get();
                            }
                            quests.push_back(Question(quest, pa, ra));
                            quest = "";
                            pa.clear();
                            ra.clear();
                        }

                    }
                    db.tests.push_back(Test(tit, sec, quests));
                    std::cout << "\nTest with title \"" << tit << "\" was read\n";
                    tit = "";
                    sec = "";
                    quests.clear();
                }
                else {
                    break;
                }
            }
            else {
                break;
            }

        }
    }
    else {
        std::cout << "\nFile didt exist!\n";
    }
    fin.close();
}

void DataBase::userToFile(const TestedUser& tu, const int key)
{
    if (users.size()) {
        std::ofstream fout;
        fout.open("D:\\Exam#1Files\\Users\\Users.txt", std::fstream::app);
        char c;
        int i = 0;
        while (tu.login[i])
        {
            c = (tu.login[i++] + key);
            fout << c;
        }
        fout << '\n';
        i = 0;
        while (tu.password[i])
        {
            c = (tu.password[i++] + key);
            fout << c;
        }
        fout << "\n\n";
        fout.close();
    }
    else {
        std::cout << "\nError! We have no users yet!\n";
    }
}

bool DataBase::isUser(const std::string log, const std::string pas) const
{
    for (auto& el : users) {
        if (el->login == log && el->password == pas) {
            return true;
        }
    }
    return false;
}

void Admin::addTest(const Test& test)
{
    for (auto& el : db.sections ) {
        if ( el == test.atributes.section) {
            db.tests.push_back(test);
            return;
        }
    }
    db.sections.push_back(test.atributes.section);
    db.tests.push_back(test);
}

TestedUser* DataBase::giveUser(const std::string log, const std::string pas)
{
    for (auto& el : users) {
        if (el->login == log && el->password == pas) {
            return el;
        }
    }
    return nullptr;
}

bool DataBase::usersLoginCheck(const std::string& log) const
{
    for (auto& el : users) {
        if (el->login == log) {
            return false;
        }
    }
    return true;
}

const std::vector<Test> DataBase::getTestsBySection(const std::string section) const
{
    std::vector<Test> tmp;
    for (auto& el : tests)
    {
        if (el.getSection() == section) {
            tmp.push_back(el);
        }
    }
    return tmp;
}