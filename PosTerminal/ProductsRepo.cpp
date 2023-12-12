#include "framework.h"
#include "ProductsRepo.h"
#include "Product.h"

ProductsRepo::ProductsRepo() : filepath("Data/Products.json")
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
	int i = 1;
	for (auto& p : products) {
		std::stringstream ss;
		ss << std::left << std::setw(10) << i++
			<< std::setw(10) << p.getSKU()
			<< std::setw(50) << p.getName()
			<< std::setw(45) << p.getCategory()
			<< std::setw(15) << p.getQuantity()
			<< std::setw(15) << p.getOut_price();
		std::string product = ss.str();
		TCHAR* pInfo = helper.string_tchar(product);
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

	SetWindowText(hEditProductSKU, helper.string_tchar(products[index].getSKU()));
	SetWindowText(hEditProductName, helper.string_tchar(products[index].getName()));
	SetWindowText(hEditProductDesc, helper.string_tchar(products[index].getDescription()));
	SetWindowText(hEditProductInprice, helper.string_tchar(std::to_string(products[index].getIn_price())));
	SetWindowText(hEditProductOutprice, helper.string_tchar(std::to_string(products[index].getOut_price())));
	SetWindowText(hEditProductQuantity, helper.string_tchar(std::to_string(products[index].getQuantity())));

}
