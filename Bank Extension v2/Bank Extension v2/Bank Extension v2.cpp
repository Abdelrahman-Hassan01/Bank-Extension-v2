#include "menus.h"

sUser CurrentUser;


int ReadInt(string Message, int Min, int Max)
{
    int Number;
    while (true)
    {
        cout << Message;
        cin >> Number;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input! Please enter a valid number.\n";
        }
        else if (Number < Min || Number > Max)
        {
            cout << "Please enter a number between " << Min << " and " << Max << ".\n";
        }
        else
            return Number;
    }
}

double ReadPositiveDouble(string Message)
{
    double Amount;
    while (true)
    {
        cout << Message;
        cin >> Amount;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input! Please enter a number.\n";
        }
        else if (Amount <= 0)
        {
            cout << "Amount Must Be Greater Than Zero.\n";
        }
        else
            return Amount;
    }
}

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;
    while ((pos = S1.find(Delim)) != string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1);
    }
    return vString;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

string ReadClientNumber()
{
    string FindClient;
    cout << "\n\tEnter Client ID: ";
    getline(cin >> ws, FindClient);
    return FindClient;
}

// ====================== clients ======================
bool FindClientByAccountNumber(string AccountNumber, vector<sClient>& vClient, sClient& Client)
{
    for (sClient C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool ClientExists(string AccountNumber, vector<sClient>& vClients)
{
    sClient Client;
    return FindClientByAccountNumber(AccountNumber, vClients, Client);
}

sClient ConvertLinetoRecord(string Line, string Seperator)
{
    sClient Client;
    vector<string> vClientData = SplitString(Line, Seperator);
    if (vClientData.size() >= 5)
    {
        Client.AccountNumber = vClientData[0];
        Client.PinCode = vClientData[1];
        Client.Name = vClientData[2];
        Client.Phone = vClientData[3];
        Client.AccountBalance = stod(vClientData[4]);
    }
    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator)
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

vector<sClient> LoadCleintsDataFromFile(string FileName)
{
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {
            if (Line != "")
            {
                sClient Client = ConvertLinetoRecord(Line);
                vClients.push_back(Client);
            }
        }
        MyFile.close();
    }
    return vClients;
}

void SaveClientDataToFile(string FileName, vector<sClient>& vClient)
{
    fstream ClientFile;
    string DataLine;
    ClientFile.open(FileName, ios::out);
    if (ClientFile.is_open())
    {
        for (sClient& s : vClient)
        {
            if (s.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(s, "#//#");
                ClientFile << DataLine << endl;
            }
        }
        ClientFile.close();
    }
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe Following Are The Client Details\n\n";
    cout << "----------------------------------------------\n";
    cout << "Account Number : " << Client.AccountNumber << endl;
    cout << "Pin Code       : " << Client.PinCode << endl;
    cout << "Name           : " << Client.Name << endl;
    cout << "Phone          : " << Client.Phone << endl;
    cout << "Account Balance: " << Client.AccountBalance << endl;
    cout << "\n----------------------------------------------\n\n";
}

void PrintClientRecord(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintTotalBalance(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector<sClient> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

sClient ReadNewClient(vector<sClient>& vClients)
{
    sClient Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);
    while (ClientExists(Client.AccountNumber, vClients))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists.";
        cout << "\nEnter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }
    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    Client.AccountBalance = ReadPositiveDouble("Enter AccountBalance? ");
    return Client;
}

void AddNewClient(vector<sClient>& vClients)
{
    char Add = 'y';
    do
    {
        sClient Client = ReadNewClient(vClients);
        vClients.push_back(Client);
        AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client, "#//#"));
        cout << "\nClient Added Successfully\n";
        cout << "\nDo You want Add More? ";
        cin >> Add;
        if (Add == 'y' || Add == 'Y')
        {
            system("cls");
        }
    } while (Add == 'y' || Add == 'Y');
}

bool MarkClientForDeleteByAccountID(string AccountNumber, vector<sClient>& vClient)
{
    for (sClient& s : vClient)
    {
        if (s.AccountNumber == AccountNumber)
        {
            s.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

bool DeleteClientInfo(string AccNum, vector<sClient>& vClient)
{
    char Delete = 'N';
    char Again = 'N';
    bool DeletedAnyClient = false;
    do
    {
        sClient Client;
        if (FindClientByAccountNumber(AccNum, vClient, Client))
        {
            PrintClientCard(Client);
            cout << "\nAre you sure you want to delete this client? (Y/N): ";
            cin >> Delete;
            if (Delete == 'y' || Delete == 'Y')
            {
                MarkClientForDeleteByAccountID(AccNum, vClient);
                SaveClientDataToFile(ClientsFileName, vClient);
                vClient = LoadCleintsDataFromFile(ClientsFileName);
                cout << "\nClient Deleted Successfully\n";
                DeletedAnyClient = true;
            }
            else
            {
                cout << "\nDelete Canceled\n";
            }
        }
        else
        {
            cout << "\nClient with Account Number [" << AccNum << "] was not found.\n";
        }
        cout << "\nDo You want Delete More? ";
        cin >> Again;
        if (Again == 'y' || Again == 'Y')
        {
            AccNum = ReadClientNumber();
            system("cls");
        }
    } while (Again == 'y' || Again == 'Y');
    return DeletedAnyClient;
}

sClient ChangeClientInfo()
{
    sClient Client;
    cout << "\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    Client.AccountBalance = ReadPositiveDouble("Enter AccountBalance? ");
    return Client;
}

bool UpdateClientByAccountNumber(string AccNum, vector<sClient>& vClient)
{
    sClient Client;
    char Update = 'n';
    if (!FindClientByAccountNumber(AccNum, vClient, Client))
    {
        cout << "\nClient With Account ID (" << AccNum << ") Not Found\n";
        return false;
    }
    PrintClientCard(Client);
    cout << "\nAre You Sure You Want Update Client? (Y/N): ";
    cin >> Update;
    if (Update == 'y' || Update == 'Y')
    {
        for (sClient& s : vClient)
        {
            if (s.AccountNumber == AccNum)
            {
                s = ChangeClientInfo();
                s.AccountNumber = AccNum;
                break;
            }
        }
        SaveClientDataToFile(ClientsFileName, vClient);
        cout << "\nClient Info Updated Successfully\n";
        return true;
    }
    cout << "\nUpdate Canceled\n";
    return false;
}

void FindClient(string AccountNumber, vector<sClient>& vClient)
{
    sClient Client;
    if (FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "\nClient With Account ID (" << AccountNumber << ") Not Found\n";
    }
}

bool DepositBalanceByAccountNumber(string AccountNumber, double Amount, vector<sClient>& vClient)
{
    char Perform = 'n';
    cout << "\nAre you sure you want to perform this transaction? (Y/N)? ";
    cin >> Perform;
    if (Perform == 'y' || Perform == 'Y')
    {
        for (sClient& C : vClient)
        {
            if (C.AccountNumber == AccountNumber && C.AccountBalance > 0)
            {
                C.AccountBalance += Amount;
                SaveClientDataToFile(ClientsFileName, vClient);
                cout << "\nDeposit Done Successfully. New balance is: " << C.AccountBalance << endl;
                return true;
            }
        }
    }
    return false;
}

void Deposit(vector<sClient>& vClient)
{
    cout << "----------------------------------------------\n";
    cout << "             Deposit Screen\n";
    cout << "----------------------------------------------\n";
    string AccountNumber = ReadClientNumber();
    sClient Client;
    while (!FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        cout << "\nClient with Account Number [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientNumber();
    }
    PrintClientCard(Client);
    double Amount = ReadPositiveDouble("Please Enter Deposit Amount? ");
    char Perform;
    cout << "\nAre you sure you want to perform this transaction? (Y/N)? ";
    cin >> Perform;
    if (Perform == 'y' || Perform == 'Y')
    {
        for (sClient& C : vClient)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveClientDataToFile(ClientsFileName, vClient);
                cout << "\nDeposit Done Successfully. New balance is: " << C.AccountBalance << endl;
                return;
            }
        }
    }
}

void With_draw(vector<sClient>& vClient)
{
    cout << "----------------------------------------------\n";
    cout << "             Withdraw Screen\n";
    cout << "----------------------------------------------\n";
    string AccountNumber = ReadClientNumber();
    sClient Client;
    while (!FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        cout << "\nClient with Account Number [" << AccountNumber << "] does not exist.\n";
        char Again;
        cout << "Do You want Try Again? ";
        cin >> Again;
        if (Again == 'y' || Again == 'Y')
        {
            system("cls");
            AccountNumber = ReadClientNumber();
        }
        else
            return;
    }
    PrintClientCard(Client);
    double Amount;
    while (true)
    {
        Amount = ReadPositiveDouble("Please Enter Withdraw Amount? ");
        if (Amount <= Client.AccountBalance)
            break;
        int Choice = ReadInt(
            "\nAmount Exceeds The Balance."
            "\nYou Can Withdraw Up To: " + to_string(Client.AccountBalance) +
            "\n\n[1] Withdraw Again\n[2] Back To Transaction Menu\nChoice: ", 1, 2);
        if (Choice == 2)
            return;
    }
    char Perform;
    cout << "\nAre you sure you want to perform this transaction? (Y/N)? ";
    cin >> Perform;
    if (Perform == 'y' || Perform == 'Y')
    {
        for (sClient& C : vClient)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance -= Amount;
                SaveClientDataToFile(ClientsFileName, vClient);
                cout << "\nWithdraw Done Successfully. New balance is: " << C.AccountBalance << endl;
                return;
            }
        }
    }
}

void ShowTotalBalances(vector<sClient> vClients)
{
    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    double TotalBalance = 0;
    for (sClient Client : vClients)
    {
        PrintTotalBalance(Client);
        cout << endl;
        TotalBalance += Client.AccountBalance;
    }
    cout << "\n\t\tTotal Balance = " << TotalBalance << endl;
}


bool FindUserByUsername(string UserName, vector<sUser>& vUsers, sUser& User)
{
    for (sUser C : vUsers)
    {
        if (C.UserName == UserName)
        {
            User = C;
            return true;
        }
    }
    return false;
}

bool FindUserByUsernameAndPassword(string UserName, string Password, sUser& User)
{
    vector<sUser> Us = LoadUsersDataFromFile(UserFileName);
    for (sUser C : Us)
    {
        if (C.UserName == UserName && C.Password == Password)
        {
            User = C;
            return true;
        }
    }
    return false;
}

bool UserExists(string UserName, vector<sUser>& vUsers)
{
    sUser User;
    return FindUserByUsername(UserName, vUsers, User);
}

sUser ConvertUserLineToRecord(string Line, string Seperator)
{
    sUser User;
    vector<string> vUserData = SplitString(Line, Seperator);
    if (vUserData.size() >= 3)
    {
        User.UserName = vUserData[0];
        User.Password = vUserData[1];
        User.Permissions = stoi(vUserData[2]);
    }
    return User;
}

string ConvertUserRecordToLine(sUser User, string Seperator)
{
    string stUserRecord = "";
    stUserRecord += User.UserName + Seperator;
    stUserRecord += User.Password + Seperator;
    stUserRecord += to_string(User.Permissions);
    return stUserRecord;
}

vector<sUser> LoadUsersDataFromFile(string FileName)
{
    vector<sUser> vUsers;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {
            if (Line != "")
            {
                sUser Client = ConvertUserLineToRecord(Line);
                vUsers.push_back(Client);
            }
        }
        MyFile.close();
    }
    return vUsers;
}

void SaveUsersDataToFile(string FileName, vector<sUser>& vUsers)
{
    fstream UserFile;
    string DataLine;
    UserFile.open(FileName, ios::out);
    if (UserFile.is_open())
    {
        for (sUser& s : vUsers)
        {
            if (s.MarkForDelete == false)
            {
                DataLine = ConvertUserRecordToLine(s);
                UserFile << DataLine << endl;
            }
        }
        UserFile.close();
    }
}

void PrintUserCard(sUser User)
{
    cout << "\nThe Following Are The Client Details\n\n";
    cout << "----------------------------------------------\n";
    cout << "username        : " << User.UserName << endl;
    cout << "Passaword       : " << User.Password << endl;
    cout << "Permissions     : " << User.Permissions << endl;
    cout << "\n----------------------------------------------\n\n";
}

void PrintUserRecord(sUser User)
{
    cout << "| " << setw(15) << left << User.UserName;
    cout << "| " << setw(20) << left << User.Password;
    cout << "| " << setw(40) << left << User.Permissions;
}

void PrintAllUsersData(vector<sUser> vUsers)
{
    cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(20) << "Passaword";
    cout << "| " << left << setw(40) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sUser User : vUsers)
    {
        PrintUserRecord(User);
        cout << endl;
    }
}

string ReadUserName(string Message)
{
    cout << Message;
    string username;
    getline(cin >> ws, username);
    return username;
}

sUser ReadNewUser(vector<sUser>& vUsers)
{
    sUser User;
    cout << "Enter username: ";
    getline(cin >> ws, User.UserName);
    while (UserExists(User.UserName, vUsers))
    {
        system("cls");
        cout << "\nUser with [" << User.UserName << "] already exists, Enter another Username? ";
        getline(cin, User.UserName);
    }
    cout << "Enter Passaword: ";
    getline(cin, User.Password);
    User.Permissions = ReadPermissionsToSet();
    return User;
}

void AddNewUser(vector<sUser>& vUsers)
{
    char AddAgain = 'Y';
    do
    {
        sUser User = ReadNewUser(vUsers);
        vUsers.push_back(User);
        AddDataLineToFile(UserFileName, ConvertUserRecordToLine(User));
        system("cls");
        cout << "User Added Successfully\n";
        cout << "Do You Want Add More? ";
        cin >> AddAgain;
        if (AddAgain == 'y' || AddAgain == 'Y')
        {
            system("cls");
        }
    } while (AddAgain == 'Y' || AddAgain == 'y');
}

bool MarkUserForDeleteByUsername(string UserName, vector<sUser>& vUsers)
{
    for (sUser& s : vUsers)
    {
        if (s.UserName == UserName)
        {
            s.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

bool DeleteUserByUsername(string username, vector<sUser>& vUser)
{
    char Delete = 'N';
    char Again = 'N';
    bool DeletedAnyUser = false;
    do
    {
        sUser User;
        if (!FindUserByUsername(username, vUser, User))
        {
            cout << "\nUser with Username [" << username << "] was not found.\n";
        }
        else if (username == "Admin" || username == "admin")
        {
            cout << "You Cannot Delete This User\n\n";
        }
        else
        {
            PrintUserCard(User);
            cout << "\nAre You Sure You Want To Delete This User? (Y/N): ";
            cin >> Delete;
            if (Delete == 'y' || Delete == 'Y')
            {
                MarkUserForDeleteByUsername(username, vUser);
                SaveUsersDataToFile(UserFileName, vUser);
                vUser = LoadUsersDataFromFile(UserFileName);
                system("cls");
                cout << "User Deleted Successfully\n";
                DeletedAnyUser = true;
            }
            else
            {
                cout << "\nDelete Canceled\n";
            }
        }
        cout << "\nDo You want Delete More? ";
        cin >> Again;
        if (Again == 'y' || Again == 'Y')
        {
            username = ReadUserName("\nEnter UserName: ");
            system("cls");
        }
    } while (Again == 'y' || Again == 'Y');
    return DeletedAnyUser;
}

sUser ChangeUsertInfo()
{
    sUser User;
    cout << "\nPassaword: ";
    getline(cin >> ws, User.Password);
    User.Permissions = ReadPermissionsToSet();
    return User;
}

bool UpdateUserByUsername(string UserName, vector<sUser>& vUsers)
{
    sUser User;
    char Update = 'n';
    if (!FindUserByUsername(UserName, vUsers, User))
    {
        cout << "\nUser With Username (" << UserName << ") Not Found\n";
        return false;
    }
    PrintUserCard(User);
    cout << "\nAre You Sure You Want Update User? (Y/N): ";
    cin >> Update;
    if (Update == 'y' || Update == 'Y')
    {
        for (sUser& s : vUsers)
        {
            if (s.UserName == UserName)
            {
                s = ChangeUsertInfo();
                s.UserName = UserName;
                break;
            }
        }
        SaveUsersDataToFile(UserFileName, vUsers);
        cout << "\nUser Info Updated Successfully\n";
        return true;
    }
    cout << "\nUpdate Canceled\n";
    return false;
}

void FindUserByUsernameScreen(string UserName, vector<sUser>& vUsers)
{
    sUser User;
    cout << "----------------------------------------------\n";
    cout << "            Find User Screen\n";
    cout << "----------------------------------------------\n";
    FindUserByUsername(UserName, vUsers, User);
    cout << endl;
    PrintUserCard(User);
    cout << "\n\n";
}

bool CheckAccessPermission(int Permission)
{
    if (CurrentUser.Permissions == -1)
        return true;
    return (CurrentUser.Permissions & Permission) == Permission;
}

void ShowAccessDeniedMessage()
{
    cout << "----------------------------------------------\n";
    cout << "Access Denied,\nYou Done Have Permission To Do This,\nPlease Conact Your Admin.\n";
    cout << "----------------------------------------------\n";
}

int ReadPermissionsToSet()
{
    int Permissions = 0;
    char Answer;
    cout << "Do You Want Give Full Access Y/N ? ";
    cin >> Answer;
    if (Answer == 'Y' || Answer == 'y')
    {
        return -1;
    }
    cout << "\nDo You Want Give:\n\n";
    cout << "Show Client List Y/N: ";
    cin >> Answer;
    if (Answer == 'Y' || Answer == 'y')
        Permissions |= 1;
    cout << "Add New Client Y/N: ";
    cin >> Answer;
    if (Answer == 'Y' || Answer == 'y')
        Permissions |= 2;
    cout << "Delete Client Y/N: ";
    cin >> Answer;
    if (Answer == 'Y' || Answer == 'y')
        Permissions |= 4;
    cout << "Update Client Info Y/N: ";
    cin >> Answer;
    if (Answer == 'Y' || Answer == 'y')
        Permissions |= 8;
    cout << "Find Client Y/N: ";
    cin >> Answer;
    if (Answer == 'Y' || Answer == 'y')
        Permissions |= 16;
    cout << "Transactions Y/N: ";
    cin >> Answer;
    if (Answer == 'Y' || Answer == 'y')
        Permissions |= 32;
    cout << "Manage Users Y/N: ";
    cin >> Answer;
    if (Answer == 'Y' || Answer == 'y')
        Permissions |= 64;
    return Permissions;
}

bool LoadUserInfo(string UserName, string Password)
{
    vector<sUser> vUsers = LoadUsersDataFromFile(UserFileName);
    sUser User;
    if (FindUserByUsername(UserName, vUsers, User))
    {
        if (User.Password == Password)
        {
            CurrentUser = User;
            return true;
        }
    }
    return false;
}

bool Login()
{
    string UserName;
    string Password;
    int LoginAttempts = 0;
    while (LoginAttempts < 3)
    {
        system("cls");
        cout << "----------------------------------------------\n";
        cout << "\t\tLogin Screen\n";
        cout << "----------------------------------------------\n";
        cout << "Enter Username: ";
        cin >> UserName;
        cout << "Enter Password: ";
        cin >> Password;
        if (LoadUserInfo(UserName, Password))
        {
            cout << "\nLogin Successful!\n";
            cout << "Welcome " << CurrentUser.UserName << "!\n";
            system("pause");
            StartBank();
            return true;
        }
        LoginAttempts++;
        cout << "\nInvalid Username or Password!\n";
        cout << "Attempts Remaining: " << 3 - LoginAttempts << endl;
        system("pause");
    }
    cout << "\nYou Failed To Login 3 Times.\n";
    cout << "Program Will Exit.\n";
    system("pause");
    return false;
}

// ====================== menus ======================
void GoBackToMainMenu()
{
    cout << "\n\nPress Any Key To Go Back To Main Menu...";
    system("pause > nul");
}

void GoBackToTransctionsMenu()
{
    cout << "\n\nPress Any Key To Go Back To Transctions Menu...";
    system("pause > nul");
}

void GoBackToManageUsersMenu()
{
    cout << "\n\nPress Any Key To Go Back To Manage Users Menu...";
    system("pause > nul");
    ShowManageUsersMenu();
}

void ShowMainMenu()
{
    cout << "---------------------------------------------------------------\n";
    cout << "\n\t\t\tMain Menu Screen\n\n";
    cout << "---------------------------------------------------------------\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transctions Menu.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Exit.\n";
    cout << "---------------------------------------------------------------\n";
}

void ShowTransctionsMenu()
{
    cout << "---------------------------------------------------------------\n";
    cout << "\n\t\t\tTransctions Menu Screen\n\n";
    cout << "---------------------------------------------------------------\n";
    cout << "\t[1] Depoist.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menu Screen.\n";
    cout << "---------------------------------------------------------------\n";
}

void ShowManageUsersMenu()
{
    cout << "----------------------------------------------\n";
    cout << "\t\tManage Users Menu Screen\n";
    cout << "----------------------------------------------\n";
    cout << "\t\t[1] List Users\n";
    cout << "\t\t[2] Add New User\n";
    cout << "\t\t[3] Delete User\n";
    cout << "\t\t[4] Update User\n";
    cout << "\t\t[5] Find Users\n";
    cout << "\t\t[6] Main Menu Users\n";
    cout << "----------------------------------------------\n";
}

MainMenuChoice ReadMainMenuChoice()
{
    return (MainMenuChoice)ReadInt("\nChoose What Do You Want Do? [1 , 8]:  ", 1, 8);
}

TransctionsMenu ReadTranstionsMenu()
{
    return (TransctionsMenu)ReadInt("\nChoose What Do You Want Do? [1 , 4]:  ", 1, 4);
}

ManageUsersMenu ReadManageUsersMenuChoice()
{
    return (ManageUsersMenu)ReadInt("\nChoose What Do You Want Do? [1 , 6]: ", 1, 6);
}

void HandleTransctionsMenuOption(TransctionsMenu UserChoice, vector<sClient>& vClient)
{
    switch (UserChoice)
    {
    case Depoist:
        system("cls");
        Deposit(vClient);
        GoBackToTransctionsMenu();
        break;
    case Withdraw:
        system("cls");
        With_draw(vClient);
        GoBackToTransctionsMenu();
        break;
    case TotalBalances:
        system("cls");
        ShowTotalBalances(vClient);
        GoBackToTransctionsMenu();
        break;
    case MainMenu:
        break;
    }
}

void StartTransctionsMenu(vector<sClient>& vClient)
{
    while (true)
    {
        system("cls");
        ShowTransctionsMenu();
        TransctionsMenu Choice = ReadTranstionsMenu();
        if (Choice == MainMenu)
            break;
        HandleTransctionsMenuOption(Choice, vClient);
    }
}

void HandleManageUsersMenuOption(ManageUsersMenu UserChoice, vector<sUser>& vUsers)
{
    sUser User;
    switch (UserChoice)
    {
    case ListUsers:
        system("cls");
        PrintAllUsersData(vUsers);
        GoBackToManageUsersMenu();
        break;
    case ManageUsersMenu::AddNewUsers:
        system("cls");
        AddNewUser(vUsers);
        GoBackToManageUsersMenu();
        break;
    case ManageUsersMenu::DeleteUser:
        system("cls");
        DeleteUserByUsername(ReadUserName("\nEnter username To Delete: "), vUsers);
        GoBackToManageUsersMenu();
        break;
    case ManageUsersMenu::UpdateUser:
        system("cls");
        UpdateUserByUsername(ReadUserName("\nEnter username To Update: "), vUsers);
        GoBackToManageUsersMenu();
        break;
    case ManageUsersMenu::FindUsers:
        system("cls");
        FindUserByUsername(ReadUserName("\nEnter User To Find: "), vUsers, User);
        GoBackToManageUsersMenu();
        break;
    case ManageUsersMenu::MainMenus:
        system("cls");
        break;
    }
}

void StartManageUsersMenu(vector<sUser>& vUsers)
{
    while (true)
    {
        system("cls");
        ShowManageUsersMenu();
        ManageUsersMenu Choice = ReadManageUsersMenuChoice();
        if (Choice == MainMenus)
            break;
        HandleManageUsersMenuOption(Choice, vUsers);
    }
}

void HandleMainMenuOption(MainMenuChoice UserChoice, vector<sClient>& vClient, vector<sUser>& vUser)
{
    system("cls");
    switch (UserChoice)
    {
    case ShowCLientList:
        if (!CheckAccessPermission(1))
        {
            ShowAccessDeniedMessage();
            GoBackToMainMenu();
            break;
        }
        PrintAllClientsData(vClient);
        GoBackToMainMenu();
        break;
    case AddNewClientInfo:
        if (!CheckAccessPermission(2))
        {
            ShowAccessDeniedMessage();
            GoBackToMainMenu();
            break;
        }
        cout << "\n----------------------------------------------\n";
        cout << "            Add Client Screen\n";
        cout << "----------------------------------------------\n";
        AddNewClient(vClient);
        GoBackToMainMenu();
        break;
    case DelteClientInfo:
        if (!CheckAccessPermission(4))
        {
            ShowAccessDeniedMessage();
            GoBackToMainMenu();
            break;
        }
        cout << "\n----------------------------------------------\n";
        cout << "            Delete Screen\n";
        cout << "----------------------------------------------\n";
        DeleteClientInfo(ReadClientNumber(), vClient);
        GoBackToMainMenu();
        break;
    case UpdateCLintInfo:
        if (!CheckAccessPermission(8))
        {
            ShowAccessDeniedMessage();
            GoBackToMainMenu();
            break;
        }
        cout << "\n----------------------------------------------\n";
        cout << "            Update Client Info Screen\n";
        cout << "----------------------------------------------\n";
        UpdateClientByAccountNumber(ReadClientNumber(), vClient);
        GoBackToMainMenu();
        break;
    case FindClients:
        if (!CheckAccessPermission(16))
        {
            ShowAccessDeniedMessage();
            GoBackToMainMenu();
            break;
        }
        cout << "----------------------------------------------\n";
        cout << "            Find Client Screen\n";
        cout << "----------------------------------------------\n";
        FindClient(ReadClientNumber(), vClient);
        GoBackToMainMenu();
        break;
    case Transctions:
        if (!CheckAccessPermission(32))
        {
            ShowAccessDeniedMessage();
            GoBackToMainMenu();
            break;
        }
        StartTransctionsMenu(vClient);
        break;
    case ManageUsers:
        if (!CheckAccessPermission(64))
        {
            ShowAccessDeniedMessage();
            GoBackToMainMenu();
            break;
        }
        StartManageUsersMenu(vUser);
        break;
    case LogOut:
        break;
    }
}

void StartBank()
{
    vector<sClient> Data = LoadCleintsDataFromFile(ClientsFileName);
    vector<sUser> Data1 = LoadUsersDataFromFile(UserFileName);
    while (true)
    {
        system("cls");
        ShowMainMenu();
        MainMenuChoice UserChoice = ReadMainMenuChoice();
        if (UserChoice == LogOut)
        {
            system("cls");
            Login();
            break;
        }
        HandleMainMenuOption(UserChoice, Data, Data1);
    }
}

int main()
{
    Login();

    return 0;
}
