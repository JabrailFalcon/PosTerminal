#include "framework.h"
#include "CategoriesRepo.h"

CategoriesRepo::CategoriesRepo() :filepath("Data/Categories.json")
{}

void CategoriesRepo::loadData()
{
	categories.clear();

	Json::Value data;
	Json::Reader reader;

	std::ifstream fin;
	fin.open(filepath);
	reader.parse(fin, data);
	fin.close();

	int size = data["size"].asInt();

	for (int i = 0; i < size; i++) {
		categories.push_back(data["categories"][i]["category"].asString());
	}
}

void CategoriesRepo::saveData()
{
	Json::Value data;
	Json::StyledStreamWriter writer;

	int size = categories.size();
	data["size"] = size;

	int i = 0;
	for (auto& category : categories) {
		data["categories"][i]["category"] = category;
		i++;
	}

	std::ofstream fout;
	fout.open(filepath);
	writer.write(fout, data);
	fout.close();
}

void CategoriesRepo::comboCategories(HWND& hComboProdCategories)
{
	TCHAR* buff;
	for (auto& category : categories) {
		buff = helper.string_tchar(category);
		SendMessage(hComboProdCategories, CB_ADDSTRING, 0, (LPARAM)buff);
		delete[] buff;
	}
	SendMessage(hComboProdCategories, CB_SETCURSEL, 0, 0);
}

void CategoriesRepo::addCategory(HWND& hDlg, HWND& hEditCatAdd)
{
	TCHAR buff[100];
	GetWindowText(hEditCatAdd, buff, 100);

	if (lstrlen(buff) == 0) {
		MessageBox(hDlg, L"Category name is empty", L"Warning", MB_OK || MB_ICONWARNING);
		SetFocus(hEditCatAdd);
		return;
	}
	else {
		std::string category = helper.tchar_string(buff);
		categories.push_back(category);
		MessageBox(hDlg, L"Added new category", L"Warning", MB_OK || MB_ICONWARNING);
		saveData();
	}
}

int CategoriesRepo::categoriesSize()
{
	return categories.size();
}
