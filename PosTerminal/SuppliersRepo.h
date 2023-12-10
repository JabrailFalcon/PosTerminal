#pragma once
#include "Supplier.h"

class SuppliersRepo
{
	std::string filePath;
	std::vector<Supplier> supliers;	
public:
	SuppliersRepo(std::string filePath); 
	void loadData();
	void saveData();
	void addSuplier(TCHAR comName[100], TCHAR ComMob[100], TCHAR ComMail[100], TCHAR Address[100], TCHAR Fname[100], TCHAR Lname[100], TCHAR Mob[100], TCHAR Mail[100], TCHAR JobTitle[100]);
	void delSuplier(int id);
	void editExist();
	void displayExist(TCHAR sup[100], HWND hDlg, HWND hList) const;
	void displayAll(HWND hDlg, HWND hList) const;
	std::vector<Supplier> getSuppliers();
};

