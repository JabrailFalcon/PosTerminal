#pragma once
#include "Supplier.h"

class SuppliersRepo
{
	std::string filePath;
	std::string fileIdBuff;
	std::vector<Supplier> supliers;	
	std::vector<int> indent;
public:
	SuppliersRepo(std::string filePath, std::string fileIdBuff);
	void loadData();
	void saveData();
	void addSuplier(HWND hDlg, HWND hList, TCHAR comName[100], TCHAR ComMob[100], TCHAR ComMail[100], TCHAR Address[100], TCHAR Fname[100], TCHAR Lname[100], TCHAR Mob[100], TCHAR Mail[100], TCHAR JobTitle[100]);
	void delSuplier(int index);
	void displayEditExist(int index, HWND hEdit1, HWND hEdit2, HWND hEdit3, HWND hEdit4, HWND hEdit5, HWND hEdit6, HWND hEdit7, HWND hEdit8, HWND hEdit9);
	void editExist(int index, TCHAR comName[100], TCHAR ComMob[100], TCHAR ComMail[100], TCHAR Address[100], TCHAR Fname[100], TCHAR Lname[100], TCHAR Mob[100], TCHAR Mail[100], TCHAR JobTitle[100]);
	void displayExist(TCHAR sup[100], HWND hDlg, HWND hList);
	void displayAll(HWND hDlg, HWND hList);
	std::vector<Supplier> getSuppliers();
};

