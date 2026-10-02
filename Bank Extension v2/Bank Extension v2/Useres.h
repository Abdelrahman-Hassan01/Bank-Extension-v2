#pragma once


#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct sUser
{
    string UserName;
    string Password;
    int Permissions;
    bool MarkForDelete = false;
};
const string UserFileName = "Useres.txt";

bool FindUserByUsername(string UserName, vector<sUser>& vUsers, sUser& User);
bool FindUserByUsernameAndPassword(string UserName, string Password, sUser& User);
bool UserExists(string UserName, vector<sUser>& vUsers);
sUser ConvertUserLineToRecord(string Line, string Seperator = "#//#");
string ConvertUserRecordToLine(sUser User, string Seperator = "#//#");
vector<sUser> LoadUsersDataFromFile(string FileName);
void SaveUsersDataToFile(string FileName, vector<sUser>& vUsers);
void PrintUserCard(sUser User);
void PrintUserRecord(sUser User);
void PrintAllUsersData(vector<sUser> vUsers);
string ReadUserName(string Message);
sUser ReadNewUser(vector<sUser>& vUsers);
void AddNewUser(vector<sUser>& vUsers);
bool MarkUserForDeleteByUsername(string UserName, vector<sUser>& vUsers);
bool DeleteUserByUsername(string username, vector<sUser>& vUser);
sUser ChangeUsertInfo();
bool UpdateUserByUsername(string UserName, vector<sUser>& vUsers);
void FindUserByUsernameScreen(string UserName, vector<sUser>& vUsers);

bool CheckAccessPermission(int Permission);
void ShowAccessDeniedMessage();
int ReadPermissionsToSet();
bool LoadUserInfo(string UserName, string Password);
bool Login();