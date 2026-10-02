#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

const string ClientsFileName = "ClientInfo.txt";
bool FindClientByAccountNumber(string AccountNumber, vector<sClient>& vClient, sClient& Client);
bool ClientExists(string AccountNumber, vector<sClient>& vClients);
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#");
string ConvertRecordToLine(sClient Client, string Seperator = "#//#");
vector<sClient> LoadCleintsDataFromFile(string FileName);
void SaveClientDataToFile(string FileName, vector<sClient>& vClient);
void PrintClientCard(sClient Client);
void PrintClientRecord(sClient Client);
void PrintTotalBalance(sClient Client);
void PrintAllClientsData(vector<sClient> vClients);
sClient ReadNewClient(vector<sClient>& vClients);
void AddNewClient(vector<sClient>& vClients);
bool MarkClientForDeleteByAccountID(string AccountNumber, vector<sClient>& vClient);
bool DeleteClientInfo(string AccNum, vector<sClient>& vClient);
sClient ChangeClientInfo();
bool UpdateClientByAccountNumber(string AccNum, vector<sClient>& vClient);
void FindClient(string AccountNumber, vector<sClient>& vClient);


void Deposit(vector<sClient>& vClient);
void With_draw(vector<sClient>& vClient);
void ShowTotalBalances(vector<sClient> vClients);
bool DepositBalanceByAccountNumber(string AccountNumber, double Amount, vector<sClient>& vClient);