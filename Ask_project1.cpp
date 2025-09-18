#include <bits/stdc++.h>
using namespace std;

// دالة تسجيل الدخول
int login()
{
    cout << "Welcome, Please Enter your Username and your Password" << endl;
    string username, password;
    cin >> username >> password;

    ifstream in("users.csv");
    if (!in.is_open())
    {
        cout << "Error: can't open users.csv\n";
        return -1;
    }

    string line;
    getline(in, line); // skip header
    while (getline(in, line))
    {
        stringstream ss(line);
        string id, fileUsername, filePassword;
        getline(ss, id, ',');
        getline(ss, fileUsername, ',');
        getline(ss, filePassword, ',');

        if (fileUsername == username && filePassword == password)
        {
            return stoi(id); // يرجع ID بتاع اليوزر
        }
    }
    return -1;
}

// دالة لتشيك إذا كان اليوزر موجود
bool userExists(const string &username)
{
    ifstream in("users.csv");
    if (!in.is_open())
        return false;

    string line;
    getline(in, line); // skip header
    while (getline(in, line))
    {
        stringstream ss(line);
        string id, fileUsername, filePassword;
        getline(ss, id, ',');
        getline(ss, fileUsername, ',');
        getline(ss, filePassword, ',');

        if (fileUsername == username)
            return true;
    }
    return false;
}

void addQuestion(int currentUserId)
{
    int toUserId;
    cout << "Enter user ID you want to ask: ";
    cin >> toUserId;
    cin.ignore();

    string questionText;
    cout << "Enter your question: ";
    getline(cin, questionText);

    ifstream in("questions.csv");
    string line;
    int lastId = 0;

    getline(in, line); // skip header
    while (getline(in, line))
    {
        stringstream ss(line);
        string id;
        getline(ss, id, ',');
        lastId = stoi(id);
    }
    in.close();

    int newId = lastId + 1;

    ofstream out("questions.csv", ios::app);
    out << newId << "," << currentUserId << "," << toUserId << "," << questionText << "," << "" << "\n";
    out.close();

    cout << "Question added successfully!\n";
}

void viewReceivedQuestions(int currentUserId)
{
    ifstream in("questions.csv");
    if (!in.is_open())
    {
        cout << "Error: can't open questions.csv\n";
        return;
    }

    string line;
    getline(in, line); // skip header
    bool found = false;

    while (getline(in, line))
    {
        stringstream ss(line);
        string questionId, fromUserId, toUserId, questionText, answer;
        getline(ss, questionId, ',');
        getline(ss, fromUserId, ',');
        getline(ss, toUserId, ',');
        getline(ss, questionText, ',');
        getline(ss, answer, ',');

        if (stoi(toUserId) == currentUserId)
        {
            found = true;
            cout << "-----------------------------\n";
            cout << "Question ID: " << questionId << "\n";
            cout << "From User: " << fromUserId << "\n";
            cout << "Text: " << questionText << "\n";
            if (answer.empty())
                cout << "Answer: Not answered yet\n";
            else
                cout << "Answer: " << answer << "\n";
        }
    }

    if (!found)
        cout << "You have no received questions.\n";

    in.close();
}

void answerQuestion(int currentUserId)
{
    ifstream in("questions.csv");
    if (!in.is_open())
    {
        cout << "Error: can't open questions.csv\n";
        return;
    }
    string line;
    getline(in, line); // skip header
    bool found = false;

    while (getline(in, line))
    {
        stringstream ss(line);
        string questionId, fromUserId, toUserId, questionText, answer;
        getline(ss, questionId, ',');
        getline(ss, fromUserId, ',');
        getline(ss, toUserId, ',');
        getline(ss, questionText, ',');
        getline(ss, answer, ',');

        if (stoi(toUserId) == currentUserId && answer.empty())
        {
            cout << "Question ID: " << questionId << "\n";
            cout << "From User: " << fromUserId << "\n";
            cout << "Text: " << questionText << "\n\n";
            found = true;
        }
    }
    in.close();

    if (!found)
    {
        cout << "No unanswered questions" << endl;
    }
    else
    {
        cout << "\nEnter Question ID you want to answer: ";
        int qid;
        cin >> qid;
        cin.ignore();

        cout << "Enter your answer: ";
        string ans;
        getline(cin, ans);

        ifstream inFile("questions.csv");
        ofstream outFile("temp.csv");
        string header;
        getline(inFile, header); // header
        outFile << header << "\n";

        while (getline(inFile, line))
        {
            stringstream ss(line);
            string questionId, fromUserId, toUserId, questionText, answer;
            getline(ss, questionId, ',');
            getline(ss, fromUserId, ',');
            getline(ss, toUserId, ',');
            getline(ss, questionText, ',');
            getline(ss, answer, ',');

            if (stoi(questionId) == qid)
            {
                outFile << questionId << "," << fromUserId << "," << toUserId << "," << questionText << "," << ans << "\n";
            }
            else
            {
                outFile << line << "\n";
            }
        }
        inFile.close();
        outFile.close();

        remove("questions.csv");
        rename("temp.csv", "questions.csv");

        cout << "Answer saved successfully!\n";
    }
}

bool userMenu(int currentUserId)
{
    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Add Question\n";
        cout << "2. View Received Questions\n";
        cout << "3. Answer Question\n";
        cout << "4. Sign Out\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            addQuestion(currentUserId);
        }
        else if (choice == 2)
        {
            viewReceivedQuestions(currentUserId);
        }
        else if (choice == 3)
        {
            answerQuestion(currentUserId);
        }
        else if (choice == 4)
        {
            cout << "You have been signed out.\n";
            return true;  // خروج نهائي
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }
}

int main()
{
    ifstream test("users.csv");
    if (!test.is_open())
    {
        ofstream out("users.csv");
        out << "id,username,password\n";
        out.close();
    }
    test.close();

    ifstream qtest("questions.csv");
    if (!qtest.is_open())
    {
        ofstream out("questions.csv");
        out << "questionId,fromUserId,toUserId,questionText,answer\n";
        out.close();
    }
    qtest.close();

    while (true)
    {
        char c;
        while (true) // لوب يسأل لحد ما يدخل إجابة صح
        {
            cout << "Do you already have an account? (y/n) or (q to quit): ";
            cin >> c;

            if (c == 'y' || c == 'n' || c == 'q')
                break;

            cout << "Invalid Answer. Please enter y, n, or q.\n";
        }

        if (c == 'q')
        {
            cout << "Goodbye!\n";
            break;
        }

        if (c == 'y')
        {
            int tries = 3;
            int currentUserId = -1;

            while (tries-- > 0)
            {
                currentUserId = login();
                if (currentUserId != -1)
                {
                    cout << "Your login succeeded\n";
                    if (userMenu(currentUserId))
                        return 0; // خروج نهائي
                }
                else
                {
                    cout << "Error, Try again please (" << tries << " left)\n";
                }
            }

            if (currentUserId == -1)
                cout << "Too many failed attempts. Let's try again from start.\n";
        }
        else if (c == 'n')
        {
            cout << "Sign Up - Please enter a new Username and Password\n";
            string newUser, newPass;
            cin >> newUser >> newPass;

            if (userExists(newUser))
            {
                cout << "Username already exists. Try another one.\n";
                continue;
            }

            ifstream in("users.csv");
            string line, lastId = "0";
            getline(in, line);
            while (getline(in, line))
            {
                stringstream ss(line);
                string id;
                getline(ss, id, ',');
                lastId = id;
            }
            in.close();

            int newId = stoi(lastId) + 1;
            ofstream out("users.csv", ios::app);
            out << newId << "," << newUser << "," << newPass << "\n";
            out.close();

            cout << "Account created successfully! Logging you in...\n";
            if (userMenu(newId))
                return 0; // خروج نهائي
        }
    }
}