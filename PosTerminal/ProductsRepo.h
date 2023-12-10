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
	void addProduct(HWND& hDlg, HWND& hEdit1, HWND& hEdit2, HWND& hEdit3, HWND& hEdit10, HWND& hEdit11, HWND& hEdit12, int index);
	void generateSKU(HWND& hEdit);
	bool checkSKU_Availability(std::string sku);
	void deleteProduct(HWND& hDlg, HWND& hProductsList);
	void fillEditWindow(int index, HWND& hEdit1, HWND& hEdit2, HWND& hEdit3, HWND& hEdit10, HWND& hEdit11, HWND& hEdit12);
};

