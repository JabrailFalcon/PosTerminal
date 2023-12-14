#pragma once

class CategoriesRepo
{
	std::vector<std::string> categories;
	std::string filepath;
	Helper helper;
public:
	CategoriesRepo();
	void loadData();
	void saveData();
	void comboCategories(HWND& hComboProdCategories);
	void addCategory(HWND& hDlg, HWND& hEditCatAdd);
	int categoriesSize();
};

