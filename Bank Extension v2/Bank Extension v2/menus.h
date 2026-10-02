#pragma once
#include "Client.h"
#include "Useres.h"

enum MainMenuChoice
{
    ShowCLientList = 1,
    AddNewClientInfo,
    DelteClientInfo,
    UpdateCLintInfo,
    FindClients,
    Transctions,
    ManageUsers,
    LogOut
};

enum TransctionsMenu
{
    Depoist = 1,
    Withdraw,
    TotalBalances,
    MainMenu
};

enum ManageUsersMenu
{
    ListUsers = 1,
    AddNewUsers,
    DeleteUser,
    UpdateUser,
    FindUsers,
    MainMenus
};

void ShowMainMenu();
void ShowTransctionsMenu();
void ShowManageUsersMenu();

MainMenuChoice ReadMainMenuChoice();
TransctionsMenu ReadTranstionsMenu();
ManageUsersMenu ReadManageUsersMenuChoice();

void GoBackToMainMenu();
void GoBackToTransctionsMenu();
void GoBackToManageUsersMenu();

void HandleMainMenuOption(MainMenuChoice UserChoice, vector<sClient>& vClient, vector<sUser>& vUser);
void HandleTransctionsMenuOption(TransctionsMenu UserChoice, vector<sClient>& vClient);
void HandleManageUsersMenuOption(ManageUsersMenu UserChoice, vector<sUser>& vUsers);

void StartTransctionsMenu(vector<sClient>& vClient);
void StartManageUsersMenu(vector<sUser>& vUsers);
void StartBank();