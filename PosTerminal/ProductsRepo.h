#pragma once
#include "Product.h"
#include "Helper.h"

class ProductsRepo
{
	std::vector<Product> products;
	std::string filepath;
public:
	ProductsRepo();
	void loadData();
	void saveData();
	void displayAllProducts(HWND& hDlg, HWND& hProductsList) const;
	void addProduct(HWND& hDlg, HWND& hEditProductSKU, HWND& hEditProductName, HWND& hEditProductDesc,
		HWND& hEditProductInprice, HWND& hEditProductOutprice, HWND& hEditProductQuantity, int index);
	void generateSKU(HWND& hEdit);
	bool checkSKU_Availability(std::string sku);
	void deleteProduct(HWND& hDlg, HWND& hProductsList);
	void fillEditWindow(int index, HWND& hEditProductSKU, HWND& hEditProductName, HWND& hEditProductDesc,
		HWND& hEditProductInprice, HWND& hEditProductOutprice, HWND& hEditProductQuantity);
};
