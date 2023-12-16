#include "framework.h"
#include "ProductsRepo.h"
#include "Product.h"

ProductsRepo::ProductsRepo() : filepath("Data/Products.json")
{}

void ProductsRepo::loadData()
{
	products.clear();
	sortedProducts.clear();
	idStorage.clear();

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
	data["size"] = size;

	std::ofstream fout;
	fout.open(filepath);
	writer.write(fout, data);
	fout.close();
}

void ProductsRepo::displayAllProducts(HWND& hProductsList)
{
	idStorage.clear();
	TCHAR* pInfo;
	std::string product;

	int i = 1;
	for (auto& p : products) {
		//IDs
		idStorage.push_back(p.getID());
		//Display
		std::stringstream ss;
		ss << std::left << std::setw(10) << i++
			<< std::setw(10) << p.getSKU()
			<< std::setw(50) << p.getName()
			<< std::setw(45) << p.getCategory()
			<< std::setw(15) << p.getQuantity()
			<< std::setw(15) << p.getIn_price()
			<< std::setw(15) << p.getOut_price();
		product = ss.str();
		pInfo = helper.string_tchar(product);
		SendMessage(hProductsList, LB_ADDSTRING, 0, LPARAM(pInfo));
		delete[] pInfo;
	}
}

Product* ProductsRepo::createProduct(HWND& hDlg, HWND& hEditProductSKU, HWND& hEditProductName, HWND& hEditProductDesc,
	HWND& hEditProductInprice, HWND& hEditProductOutprice, HWND& hEditProductQuantity, HWND& hComboProdCategories, int productid, bool edit, std::string samesku)
{
	std::string sku;
	std::string name;
	std::string category;
	double in_price = 0.0;
	double out_price = 0.0;
	std::string description;
	int quantity = 0;
	int id = 0;
	TCHAR buff[100];

	//CATEGORY
	GetDlgItemText(hDlg, IDC_COMBO_CATEGORY, buff, 100);
	category = helper.tchar_string(buff);

	//SKU
	GetWindowText(hEditProductSKU, buff, 100);
	if (lstrlen(buff) == 0) {
		MessageBox(hDlg, L"SKU is empty", L"Warning", MB_OK || MB_ICONWARNING);
		SetFocus(hEditProductSKU);
		return nullptr;
	}
	else {
		sku = helper.tchar_string(buff);
		bool skuyes = checkSKU_Availability(sku);
		if (skuyes || sku == samesku) {
			GetWindowText(hEditProductName, buff, 100);
		}
		else {
			MessageBox(hDlg, L"This SKU already exists. It should be unique.", L"Warning", MB_OK || MB_ICONWARNING);
			SetWindowText(hEditProductSKU, 0);
			SetFocus(hEditProductSKU);
			return nullptr;
		}
	}

	//PRODUCT NAME
	if (lstrlen(buff) == 0) {
		MessageBox(hDlg, L"Product name is empty", L"Warning", MB_OK || MB_ICONWARNING);
		SetFocus(hEditProductName);
		return nullptr;
	}
	else {
		name = helper.tchar_string(buff);
		GetWindowText(hEditProductInprice, buff, 100);
	}
	
	//IN-PRICE
	if (lstrlen(buff) == 0) {
		MessageBox(hDlg, L"In-price is empty", L"Warning", MB_OK || MB_ICONWARNING);
		SetFocus(hEditProductInprice);
		return nullptr;
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
			return nullptr;
		}
	}

	//OUT-PRICE
	if (lstrlen(buff) == 0) {
		MessageBox(hDlg, L"Out-price is empty", L"Warning", MB_OK || MB_ICONWARNING);
		SetFocus(hEditProductOutprice);
		return nullptr;
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
			return nullptr;
		}
	}

	//QUANTITY
	if (lstrlen(buff) == 0) {
		MessageBox(hDlg, L"Quantity is empty", L"Warning", MB_OK || MB_ICONWARNING);
		SetFocus(hEditProductQuantity);
		return nullptr;
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
			return nullptr;
		}
	}

	//DESCRIPTION
	if (lstrlen(buff) == 0) {
		MessageBox(hDlg, L"Description is empty", L"Warning", MB_OK || MB_ICONWARNING);
		SetFocus(hEditProductDesc);
		return nullptr;
	}
	else {
		description = helper.tchar_string(buff);
		if (edit) {
			auto iterator = std::find_if(products.begin(), products.end(), [productid](Product& p) { return p.getID() == productid; });
			id = iterator->getID();
		}
		else {
			id = products.back().getID() + 1;
		}
		Product* product = new Product{ id, sku, name, category, in_price, out_price, description, quantity };
		return product;
	}
}

void ProductsRepo::addProduct(HWND& hDlg, HWND& hEditProductSKU, HWND& hEditProductName, HWND& hEditProductDesc,
	HWND& hEditProductInprice, HWND& hEditProductOutprice, HWND& hEditProductQuantity, HWND& hComboProdCategories,
	int productid, bool edit, bool& correct)
{
	Product* product = createProduct(hDlg, hEditProductSKU, hEditProductName, hEditProductDesc, hEditProductInprice,
		hEditProductOutprice, hEditProductQuantity, hComboProdCategories, productid, edit, "");
	if (product != nullptr) {
		products.push_back(*product);
		delete product;
		MessageBox(hDlg, L"Added new product", L"Info", MB_OK);
		saveData();
		correct = true;
	}
}

void ProductsRepo::editProduct(HWND& hDlg, HWND& hEditProductSKU, HWND& hEditProductName, HWND& hEditProductDesc,
	HWND& hEditProductInprice, HWND& hEditProductOutprice, HWND& hEditProductQuantity, HWND& hComboProdCategories,
	int productid, bool edit, bool sorted, bool& correct, std::string samesku)
{
	Product* product = createProduct(hDlg, hEditProductSKU, hEditProductName, hEditProductDesc, hEditProductInprice,
		hEditProductOutprice, hEditProductQuantity, hComboProdCategories, productid, edit, samesku);
	if (product != nullptr) {
		std::vector<Product>::iterator iterator;
		iterator = std::find_if(products.begin(), products.end(), [productid](Product& p) { return p.getID() == productid; });

		iterator->setID(product->getID());
		iterator->setSKU(product->getSKU());
		iterator->setName(product->getName());
		iterator->setCategory(product->getCategory());
		iterator->setIn_price(product->getIn_price());
		iterator->setOut_price(product->getOut_price());
		iterator->setDescription(product->getDescription());
		iterator->setQuantity(product->getQuantity());

		if (sorted) {
			iterator = std::find_if(sortedProducts.begin(), sortedProducts.end(), [productid](Product& p) { return p.getID() == productid; });

			iterator->setID(product->getID());
			iterator->setSKU(product->getSKU());
			iterator->setName(product->getName());
			iterator->setCategory(product->getCategory());
			iterator->setIn_price(product->getIn_price());
			iterator->setOut_price(product->getOut_price());
			iterator->setDescription(product->getDescription());
			iterator->setQuantity(product->getQuantity());

		}
		delete product;
		MessageBox(hDlg, L"Edited product", L"Info", MB_OK);
		saveData();
		correct = true;
	}
}

void ProductsRepo::generateSKU(HWND& hEdit)
{
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
	return false;
}

void ProductsRepo::deleteProduct(HWND& hDlg, HWND& hProductsList, bool sorted, HWND& hEditProdNameSKU)
{
	int index = SendMessage(hProductsList, LB_GETCURSEL, 0, 0);
	if (index >= 0) {
		int productid = getIDbyIndex(index);
		auto iterator = std::find_if(products.begin(), products.end(), [productid](Product& p) { return p.getID() == productid; });
		products.erase(iterator);
		SendMessage(hProductsList, LB_RESETCONTENT, 0, 0);
		if (sorted) {
			sortedProducts.erase(sortedProducts.begin() + index);
			if (sortedProducts.empty()) {
				displayAllProducts(hProductsList);
				MessageBox(hDlg, L"Sorted list is empty, displaying all products", L"Warning", MB_OK || MB_ICONWARNING);
				SetWindowText(hEditProdNameSKU, 0);
			}
			else {
				displaySortedProducts(hProductsList);
			}
		}
		else {
			displayAllProducts(hProductsList);
		}
		saveData();
	}
	else {
		MessageBox(hDlg, L"Select product in the list to delete it!", L"Warning", MB_OK || MB_ICONWARNING);
	}
}

void ProductsRepo::fillEditWindow(int productid, HWND& hEditProductSKU, HWND& hEditProductName, HWND& hEditProductDesc,
	HWND& hEditProductInprice, HWND& hEditProductOutprice, HWND& hEditProductQuantity, HWND& hComboProdCategoriesAdd)
{
	auto iterator = std::find_if(products.begin(), products.end(), [productid](Product& p) { return p.getID() == productid; });

	TCHAR* buff = helper.string_tchar(iterator->getSKU());
	SetWindowText(hEditProductSKU, buff);
	delete[] buff;

	buff = helper.string_tchar(iterator->getName());
	SetWindowText(hEditProductName, buff);
	delete[] buff;

	buff = helper.string_tchar(iterator->getDescription());
	SetWindowText(hEditProductDesc, buff);
	delete[] buff;

	buff = helper.string_tchar(std::to_string(iterator->getIn_price()));
	SetWindowText(hEditProductInprice, buff);
	delete[] buff;

	buff = helper.string_tchar(std::to_string(iterator->getOut_price()));
	SetWindowText(hEditProductOutprice, buff);
	delete[] buff;

	buff = helper.string_tchar(std::to_string(iterator->getQuantity()));
	SetWindowText(hEditProductQuantity, buff);
	delete[] buff;

	buff = helper.string_tchar(iterator->getCategory());
	int i = SendMessage(hComboProdCategoriesAdd, CB_FINDSTRING, -1, (LPARAM)buff);
	delete[] buff;
	SendMessage(hComboProdCategoriesAdd, CB_SETCURSEL, i, 0);
}

void ProductsRepo::comboSort(HWND& hComboProdSort)
{
	SendMessage(hComboProdSort, CB_ADDSTRING, 0, (LPARAM)_T("Category"));
	SendMessage(hComboProdSort, CB_ADDSTRING, 0, (LPARAM)_T("Name"));
	SendMessage(hComboProdSort, CB_ADDSTRING, 0, (LPARAM)_T("Price"));
	SendMessage(hComboProdSort, CB_ADDSTRING, 0, (LPARAM)_T("SKU"));
	SendMessage(hComboProdSort, CB_SETCURSEL, 0, 0);
}

void ProductsRepo::selectProducts(HWND& hDlg, HWND& hProductsList, HWND& hEditProdNameSKU)
{
	sortedProducts.clear();


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

	if (sortedProducts.empty()) {
		MessageBox(hDlg, L"There are no products matching your filter", L"Warning", MB_OK || MB_ICONWARNING);
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
	idStorage.clear();

	TCHAR* pInfo;
	std::string product;

	int i = 1;
	for (auto& p : sortedProducts) {

		idStorage.push_back(p.getID());

		std::stringstream ss;
		ss << std::left << std::setw(10) << i++
			<< std::setw(10) << p.getSKU()
			<< std::setw(50) << p.getName()
			<< std::setw(45) << p.getCategory()
			<< std::setw(15) << p.getQuantity()
			<< std::setw(15) << p.getIn_price()
			<< std::setw(15) << p.getOut_price();
		product = ss.str();
		pInfo = helper.string_tchar(product);
		SendMessage(hProductsList, LB_ADDSTRING, 0, LPARAM(pInfo));
		delete[] pInfo;
	}
}

int ProductsRepo::getIDbyIndex(int index)
{
	return idStorage[index];
}
