#pragma once
#include "Product.h"

class ProductsRepo
{
	std::vector<Product> products;
	std::string filepath;
	std::vector<std::string> categories;
	std::string categoryFilepath;
	std::vector<Product> sortedProducts;
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
	void comboCategories(HWND& hComboProdCategories);
	void comboSort(HWND& hComboProdSort);
	void saveCategories();
	void selectProducts(HWND& hDlg, HWND& hProductsList, HWND& hEditProdNameSKU);
	void sortByCategory(std::string category);
	void sortByName(std::string name);
	void sortBySKU(std::string sku);
	void sortByPrice(double price);
	void displaySortedProducts(HWND& hProductsList);
};

