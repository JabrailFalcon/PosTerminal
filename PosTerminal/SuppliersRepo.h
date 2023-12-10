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
	void addSuplier();
	void delSuplier(int id);
	void editExist();
	void displayExist(TCHAR sup[100], HWND hDlg, HWND hList) const;
	void displayAll(HWND hDlg, HWND hList) const;
};

