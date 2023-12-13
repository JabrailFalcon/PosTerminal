#include "framework.h"
#include "ProductsRepo.h"
#include "Product.h"

ProductsRepo::ProductsRepo() : filepath("Data/Products.json"), categoryFilepath("Data/Categories.json")
{}

void ProductsRepo::loadData()
{
	products.clear();

	Json::Value data;
	Json::Reader reader;

	std::ifstream fin;
	fin.open(filepath);
	reader.parse(fin, data);
	fin.close();

	int size = data["size"].asInt();

	for (int i = 0; i < size; i++) {
		Product p = {
			data["products"][i]["id"].asInt(),
			data["products"][i]["sku"].asString(),
			data["products"][i]["name"].asString(),
			data["products"][i]["category"].asString(),
			data["products"][i]["in_price"].asDouble(),
			data["products"][i]["out_price"].asDouble(),
			data["products"][i]["description"].asString(),
			data["products"][i]["quantity"].asInt()
		};
		products.push_back(p);
	}

	//Categories
	categories.clear();

	fin.open(categoryFilepath);
	reader.parse(fin, data);
	fin.close();
	
	size = data["size"].asInt();

	for (int i = 0; i < size; i++) {
		categories.push_back(data["categories"][i]["category"].asString());
	}
}

void ProductsRepo::saveData()
{
	Json::Value data;
	Json::StyledStreamWriter writer;

	int size = products.size();
	data["size"] = size;

	int i = 0;
	for (auto& product : products) {
		data["products"][i]["id"] = product.getID();
		data["products"][i]["sku"] = product.getSKU();
		data["products"][i]["name"] = product.getName();
		data["products"][i]["category"] = product.getCategory();
		data["products"][i]["in_price"] = product.getIn_price();
		data["products"][i]["out_price"] = product.getOut_price();
		data["products"][i]["description"] = product.getDescription();
		data["products"][i]["quantity"] = product.getQuantity();
		i++;
	}

	std::ofstream fout;
	fout.open(filepath);
	writer.write(fout, data);
	fout.close();
}

void ProductsRepo::displayAllProducts(HWND& hDlg, HWND& hProductsList) const
{
	Helper helper;
	TCHAR* pInfo;
	std::string product;

	int i = 1;
	for (auto& p : products) {
		std::stringstream ss;
		ss << std::left << std::setw(10) << i++
			<< std::setw(10) << p.getSKU()
			<< std::setw(50) << p.getName()
			<< std::setw(45) << p.getCategory()
			<< std::setw(15) << p.getQuantity()
			<< std::setw(15) << p.getOut_price();
		product = ss.str();
		pInfo = helper.string_tchar(product);
		SendMessage(hProductsList, LB_ADDSTRING, 0, LPARAM(pInfo));
		delete[] pInfo;
	}
}

void ProductsRepo::addProduct(HWND& hDlg, HWND& hEditProductSKU, HWND& hEditProductName, HWND& hEditProductDesc,
	HWND& hEditProductInprice, HWND& hEditProductOutprice, HWND& hEditProductQuantity, int index)
{
	Helper helper;
	bool correct = false;
	int id = 0;

	if (index >= 0) {
		id = products[index].getID();
		products.erase(products.begin() + index);
	}
	else {
		id = products.back().getID() + 1;
	}
	std::string sku;
	std::string name;
	std::string category;
	double in_price = 0.0;
	double out_price = 0.0;
	std::string description;
	int quantity = 0;

	TCHAR buff[100];

	//SKU
	GetWindowText(hEditProductSKU, buff, 100);
	if (lstrlen(buff) == 0) {
		MessageBox(hDlg, L"SKU is empty", L"Warning", MB_OK || MB_ICONWARNING);
		SetFocus(hEditProductSKU);
		return;
	}
	else {
		if (checkSKU_Availability(helper.tchar_string(buff))) {
			sku = helper.tchar_string(buff);
			GetWindowText(hEditProductName, buff, 100);
		}
		else {
			MessageBox(hDlg, L"This SKU already exists. It should be unique.", L"Warning", MB_OK || MB_ICONWARNING);
			SetWindowText(hEditProductSKU, 0);
			SetFocus(hEditProductSKU);
			return;
		}
	}

	//PRODUCT NAME
	if (lstrlen(buff) == 0) {
		MessageBox(hDlg, L"Product name is empty", L"Warning", MB_OK || MB_ICONWARNING);
		SetFocus(hEditProductName);
		return;
	}
	else {
		name = helper.tchar_string(buff);
		GetWindowText(hEditProductInprice, buff, 100);
	}

	//...
	category = "placeholder";

	//IN-PRICE
	if (lstrlen(buff) == 0) {
		MessageBox(hDlg, L"In-price is empty", L"Warning", MB_OK || MB_ICONWARNING);
		SetFocus(hEditProductInprice);
		return;
	}
	else {
		std::string text = helper.tchar_string(buff);
		if (helper.validateDouble(text)) {
			in_price = stod(text);
			GetWindowText(hEditProductOutprice, buff, 100);
		}
		else {
			MessageBox(hDlg, L"Input correct in-price value!", L"Warning", MB_OK || MB_ICONWARNING);
			SetWindowText(hEditProductInprice, 0);
			SetFocus(hEditProductInprice);
			return;
		}
	}

	//OUT-PRICE
	if (lstrlen(buff) == 0) {
		MessageBox(hDlg, L"Out-price is empty", L"Warning", MB_OK || MB_ICONWARNING);
		SetFocus(hEditProductOutprice);
		return;
	}
	else {
		std::string text = helper.tchar_string(buff);
		if (helper.validateDouble(text)) {
			out_price = stod(text);
			GetWindowText(hEditProductQuantity, buff, 100);
		}
		else {
			MessageBox(hDlg, L"Input correct out-price value!", L"Warning", MB_OK || MB_ICONWARNING);
			SetWindowText(hEditProductOutprice, 0);
			SetFocus(hEditProductOutprice);
			return;
		}
	}

	//QUANTITY
	if (lstrlen(buff) == 0) {
		MessageBox(hDlg, L"Quantity is empty", L"Warning", MB_OK || MB_ICONWARNING);
		SetFocus(hEditProductQuantity);
		return;
	}
	else {
		std::string text = helper.tchar_string(buff);
		if (helper.validateInt(text)) {
			quantity = stoi(text);
			GetWindowText(hEditProductDesc, buff, 100);
		}
		else {
			MessageBox(hDlg, L"Input correct quantity value!", L"Warning", MB_OK || MB_ICONWARNING);
			SetWindowText(hEditProductQuantity, 0);
			SetFocus(hEditProductQuantity);
			return;
		}
	}

	//DESCRIPTION
	if (lstrlen(buff) == 0) {
		MessageBox(hDlg, L"Description is empty", L"Warning", MB_OK || MB_ICONWARNING);
		SetFocus(hEditProductDesc);
		return;
	}
	else {
		description = helper.tchar_string(buff);
		correct = true;
	}

	if (correct) {
		Product product{ id, sku, name, category, in_price, out_price, description, quantity };
		products.push_back(product);
		if (index >= 0) {
			MessageBox(hDlg, L"Edited product", L"Info", MB_OK);
		}
		else {
			MessageBox(hDlg, L"Added new product", L"Info", MB_OK);
		}
		saveData();
	}
}

void ProductsRepo::generateSKU(HWND& hEdit)
{
	Helper helper;
	int number = 0;
	std::string sku = "TF";
	do {
		srand(time(0));
		number = rand() % 989999 + 10000;
		sku += std::to_string(number);
		if (checkSKU_Availability(sku)) {
			SetWindowText(hEdit, helper.string_tchar(sku));
			break;
		}
	} while (true);
}

bool ProductsRepo::checkSKU_Availability(std::string sku)
{
	auto iter = std::find_if(products.begin(), products.end(), [sku](Product& p) { return p.getSKU() == sku; });
	if (iter == products.end()) {
		return true;
	}
	else {
		return false;
	}
}

void ProductsRepo::deleteProduct(HWND& hDlg, HWND& hProductsList)
{
	int index = SendMessage(hProductsList, LB_GETCURSEL, 0, 0);
	if (index >= 0) {
		products.erase(products.begin() + index);
		saveData();
	}
	else {
		MessageBox(hDlg, L"Select product in the list to delete it!", L"Warning", MB_OK || MB_ICONWARNING);
	}
}

void ProductsRepo::fillEditWindow(int index, HWND& hEditProductSKU, HWND& hEditProductName, HWND& hEditProductDesc,
	HWND& hEditProductInprice, HWND& hEditProductOutprice, HWND& hEditProductQuantity)
{
	Helper helper;

	TCHAR* buff = helper.string_tchar(products[index].getSKU());
	SetWindowText(hEditProductSKU, buff);
	delete[] buff;

	buff = helper.string_tchar(products[index].getName());
	SetWindowText(hEditProductName, buff);
	delete[] buff;

	buff = helper.string_tchar(products[index].getDescription());
	SetWindowText(hEditProductDesc, buff);
	delete[] buff;

	buff = helper.string_tchar(std::to_string(products[index].getIn_price()));
	SetWindowText(hEditProductInprice, buff);
	delete[] buff;

	buff = helper.string_tchar(std::to_string(products[index].getOut_price()));
	SetWindowText(hEditProductOutprice, buff);
	delete[] buff;

	buff = helper.string_tchar(std::to_string(products[index].getQuantity()));
	SetWindowText(hEditProductQuantity, buff);
	delete[] buff;
}

void ProductsRepo::comboCategories(HWND& hComboProdCategories)
{
	Helper helper;
	TCHAR* buff;
	for (auto& category : categories) {
		buff = helper.string_tchar(category);
		SendMessage(hComboProdCategories, CB_ADDSTRING, 0, (LPARAM)buff);
		delete[] buff;
	}
	SendMessage(hComboProdCategories, CB_SETCURSEL, 0, 0);
}

void ProductsRepo::comboSort(HWND& hComboProdSort)
{
	SendMessage(hComboProdSort, CB_ADDSTRING, 0, (LPARAM)_T("Category"));
	SendMessage(hComboProdSort, CB_ADDSTRING, 0, (LPARAM)_T("Name"));
	SendMessage(hComboProdSort, CB_ADDSTRING, 0, (LPARAM)_T("Price"));
	SendMessage(hComboProdSort, CB_ADDSTRING, 0, (LPARAM)_T("SKU"));
	SendMessage(hComboProdSort, CB_SETCURSEL, 0, 0);
}

void ProductsRepo::saveCategories()
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
	fout.open(categoryFilepath);
	writer.write(fout, data);
	fout.close();
}

void ProductsRepo::selectProducts(HWND& hDlg, HWND& hProductsList, HWND& hEditProdNameSKU)
{
	sortedProducts.clear();

	Helper helper;
	TCHAR text[100];
	GetDlgItemText(hDlg, IDC_COMBO_SORT_PROD3, text, 100);

	std::string stringtext = helper.tchar_string(text);
	int choice = -1;

	if (stringtext == "Category") choice = 0;
	if (stringtext == "Name") choice = 1;
	if (stringtext == "Price") choice = 2;
	if (stringtext == "SKU") choice = 3;

	switch (choice) {
	case 0:
		{
			GetDlgItemText(hDlg, IDC_COMBO_CATEGORY_PRODUCT, text, 100);
			sortByCategory(helper.tchar_string(text));
		}
		break;
	case 1:
		{
			GetWindowText(hEditProdNameSKU, text, 100);
			if (lstrlen(text) == 0) {
				MessageBox(hDlg, L"Enter product name", L"Warning", MB_OK || MB_ICONWARNING);
				SetFocus(hEditProdNameSKU);
				return;
			}
			else {
				sortByName(helper.tchar_string(text));
			}			
		}
		break;
	case 2:
		{
			//price
		}
		break;
	case 3:
		{
			GetWindowText(hEditProdNameSKU, text, 100);
			if (lstrlen(text) == 0) {
				MessageBox(hDlg, L"Enter SKU", L"Warning", MB_OK || MB_ICONWARNING);
				SetFocus(hEditProdNameSKU);
				return;
			}
			else {
				sortBySKU(helper.tchar_string(text));
			}			
		}
		break;
	default:
		{
			MessageBox(hDlg, L"Something went wrong", L"Warning", MB_OK || MB_ICONWARNING);
		}
		break;
	}

	if(sortedProducts.empty()) {
		MessageBox(hDlg, L"Such product was not found", L"Warning", MB_OK || MB_ICONWARNING);
		SetWindowText(hEditProdNameSKU, 0);
	}
	else {
		SendMessage(hProductsList, LB_RESETCONTENT, 0, 0);
		displaySortedProducts(hProductsList);
	}	
}

void ProductsRepo::sortByCategory(std::string category)
{
	std::copy_if(products.begin(), products.end(), std::back_inserter(sortedProducts),
		[category](Product& p) { return p.getCategory() == category; });
}

void ProductsRepo::sortByName(std::string name)
{
	std::copy_if(products.begin(), products.end(), std::back_inserter(sortedProducts),
		[name](Product& p) { return p.getName() == name; });
}

void ProductsRepo::sortBySKU(std::string sku)
{
	std::copy_if(products.begin(), products.end(), std::back_inserter(sortedProducts),
		[sku](Product& p) { return p.getSKU() == sku; });
}

void ProductsRepo::sortByPrice(double price)
{
}

void ProductsRepo::displaySortedProducts(HWND& hProductsList)
{
	Helper helper;
	TCHAR* pInfo;
	std::string product;

	int i = 1;
	for (auto& p : sortedProducts) {
		std::stringstream ss;
		ss << std::left << std::setw(10) << i++
			<< std::setw(10) << p.getSKU()
			<< std::setw(50) << p.getName()
			<< std::setw(45) << p.getCategory()
			<< std::setw(15) << p.getQuantity()
			<< std::setw(15) << p.getOut_price();
		product = ss.str();
		pInfo = helper.string_tchar(product);
		SendMessage(hProductsList, LB_ADDSTRING, 0, LPARAM(pInfo));
		delete[] pInfo;
	}
}
