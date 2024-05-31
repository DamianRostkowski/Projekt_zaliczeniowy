#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
using namespace std;

void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void toDoList(vector<string>& taskList)
{
    if(!taskList.empty())
        cout << "To do list:\n";
    for (int i = 0; i < taskList.size(); i++)
    {
        cout << to_string(i + 1) + ". " + taskList[i] + "\n";
    }
    if (!taskList.empty())
        cout << "\n";
}

void addTask(vector<string>& taskList)
{
    clear();
    string task;
    cout << "Enter a new task: ";
    cin.ignore();
    try {
        getline(cin, task);
        if (task == "")
        {
            cout << "Task can't be empty.";
            return;
        }
        if (task[0] >= 'a' && task[0] <= 'z')
        {
            task[0] = task[0] - 32;
        }
        taskList.push_back(task);
        clear();
    }
    catch(...) {
        cout << "There is a problem with the task.\n";
    }
}

void completeTask(vector<string>& taskList, vector<string>& taskListDone) {
    clear();
    toDoList(taskList);
    cout << "Which task do you want complete?: ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > taskList.size()) {
        cout << "Invalid task number.\n";
        return;
    }
    try {
        string task = taskList[choice - 1];
        taskList.erase(taskList.begin() + choice - 1);
        taskListDone.push_back(task);
        clear();
    }
    catch (...)
    {
        cout << "There is an error.\n";
    }
}

void uploadList(vector<string>& taskList)
{
    ofstream file("ToDoList.txt");
    if (!file.is_open())
    {
        cout << "Can't open a file.\n";
    }
    else 
    {
        for (int i = 0; i < taskList.size(); i++)
        {
            file << to_string(i + 1) + ". " + taskList[i] + "\n";
        }
        file.close();
        clear();
    }
}
void importList(vector<string>& taskList, vector<string>& taskListDone) {
    ifstream file("ToDoList.txt");
    if (!file.is_open())
    {
        cout << "Can't open a file.\n";
    }
    else 
    {
        taskList.clear();
        taskListDone.clear();
        string line;
        while (getline(file, line)) {
            taskList.push_back(line.substr(3, line.size() - 3));
        }
        clear();
    }
}

void toDoMenu(vector<string>& taskList, vector<string>& taskListDone)
{
    int choice;
    while (true)
    {
        toDoList(taskList);
        cout << "1 - Add task.\n";
        cout << "2 - Complete task.\n";
        cout << "3 - Upload my list to txt file.\n";
        cout << "4 - Import list from txt file(it will overwrite existing list).\n";
        cout << "5 - Clear console\n";
        cout << "6 - Go back.\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addTask(taskList);
            break;
        case 2:
            completeTask(taskList, taskListDone);
            break;
        case 3:
            uploadList(taskList);
            break;
        case 4:
            importList(taskList, taskListDone);
            break;
        case 5:
            clear();
            break;
        case 6:
            return;
        default:
            cout << "Wrong number, try again.\n";
        }
    }
}

void toDoListDone(vector<string>& taskListDone)
{
    if (!taskListDone.empty())
        cout << "Complete tasks:\n";
    for (int i = 0; i < taskListDone.size(); i++)
    {
        cout << to_string(i + 1) + ". " + taskListDone[i] + "\n";
    }
    if (!taskListDone.empty())
        cout << "\n";
}

void bringBackTask(vector<string>& taskList, vector<string>& taskListDone)
{
    clear();
    toDoListDone(taskListDone);
    cout << "Which task do you want to bring back?: ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > taskListDone.size()) {
        cout << "Invalid task number.\n";
        return;
    }
    string task = taskListDone[choice - 1];
    taskListDone.erase(taskListDone.begin() + choice - 1);
    taskList.push_back(task);
    clear();
}
void removeOneTask(vector<string>& taskListDone)
{
    clear();
    toDoListDone(taskListDone);
    cout << "Which task do you want to remove?: ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > taskListDone.size()) {
        cout << "Invalid task number.\n";
        return;
    }
    try {
        taskListDone.erase(taskListDone.begin() + choice - 1);
        clear();
    }
    catch (...)
    {
        cout << "There is an error.\n";
    }
}
void removeAllTasks(vector<string>& taskListDone)
{
    taskListDone.clear();
    clear();
}
void completedMenu(vector<string>& taskList, vector<string>& taskListDone)
{
    while (true)
    {
        toDoListDone(taskListDone);
        int choice;
        cout << "Completed Menu \n\n";
        cout << "1 - Move completed task to ToDoList.\n";
        cout << "2 - Remove one completed task.\n";
        cout << "3 - Remove whole completed list\n";
        cout << "4 - Clear console\n";
        cout << "5 - Go back\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            clear();
            bringBackTask(taskList, taskListDone);
            break;
        case 2:
            clear();
            removeOneTask(taskListDone);
            break;
        case 3:
            clear();
            removeAllTasks(taskListDone);
            break;
        case 4:
            clear();
            break;
        case 5:
            return;
        default:
            cout << "Wrong number, try again.\n";
        }
    }
}

void bubbleSort(vector<int>& myNumbers) {
    for (int i = 0; i < myNumbers.size() - 1; i++) {
        for (int j = 0; j < myNumbers.size() - i - 1; j++) {
            if (myNumbers[j] > myNumbers[j + 1]) {
                swap(myNumbers[j], myNumbers[j + 1]);
            }
        }
    }
}

void selectionSort(vector<int>& myNumbers) {
    for (int i = 0; i < myNumbers.size() - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < myNumbers.size(); j++) {
            if (myNumbers[j] < myNumbers[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(myNumbers[i], myNumbers[minIdx]);
        }
    }
}

void sortingMenu()
{
    vector <int> myNumbers = { 2,1,4,9,0,7,8,3,6,5 };
    while (true)
    {
        cout << "Your lucky numbers: ";
        for (int i = 0; i < myNumbers.size(); i++)
        {
            cout << to_string(myNumbers[i]) + " ";
        }
        cout << "\n";
        int choice;
        cout << "1. Roll numbers\n";
        cout << "2. Bubblesort.\n";
        cout << "3. selectionSort\n";
        cout << "4. Clear console\n";
        cout << "5. Go back\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            clear();
            generate(myNumbers.begin(), myNumbers.end(), []() { return rand() % 100; });
            break;
        case 2:
            clear();
            bubbleSort(myNumbers);
            break;
        case 3:
            clear();
            selectionSort(myNumbers);
            break;
        case 4:
            clear();
            break;
        case 5:
            clear();
            return;
        default:
            cout << "Wrong number, try again.\n";
        }
    }
}
void mainMenu() 
{
    vector<string> taskListDone = {};
    vector<string> taskList = {};
    while (true)
    {
        int choice;
        system("cls");
        cout << "1. To do list\n";
        cout << "2. Completed tasks.\n";
        cout << "3. Sorting methods\n";
        cout << "4. Clear Console\n";
        cin >> choice;
        switch (choice) 
        {
        case 1:
            clear();
            toDoMenu(taskList, taskListDone);
            break;
        case 2:
            clear();
            completedMenu(taskList, taskListDone);
            break;
        case 3:
            clear();
            sortingMenu();
            break;
        case 4: 
            clear();
            break;
        default:
            cout << "Wrong number, try again.\n";
        }
    }
}

int main()
{
    mainMenu();
}
