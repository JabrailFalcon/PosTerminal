#pragma once
#include "Product.h"

class ProductsRepo
{
	std::vector<Product> products;
	std::string filepath;
	std::vector<int> idStorage;
	std::vector<Product> sortedProducts; 
	Helper helper;
public:
	ProductsRepo();
	void loadData();
	void saveData();
	void displayAllProducts(HWND& hProductsList);
	void modifyProduct(HWND& hDlg, HWND& hEditProductSKU, HWND& hEditProductName, HWND& hEditProductDesc,
		HWND& hEditProductInprice, HWND& hEditProductOutprice, HWND& hEditProductQuantity, HWND& hComboProdCategories, int productid, bool edit, bool sorted);
	void generateSKU(HWND& hEdit);
	bool checkSKU_Availability(std::string sku);
	void deleteProduct(HWND& hDlg, HWND& hProductsList, bool sorted, HWND& hEditProdNameSKU);
	void fillEditWindow(int productid, HWND& hEditProductSKU, HWND& hEditProductName, HWND& hEditProductDesc,
		HWND& hEditProductInprice, HWND& hEditProductOutprice, HWND& hEditProductQuantity, HWND& hComboProdCategoriesAdd);
	void comboSort(HWND& hComboProdSort);

	void selectProducts(HWND& hDlg, HWND& hProductsList, HWND& hEditProdNameSKU);
	void sortByCategory(std::string category);
	void sortByName(std::string name);
	void sortBySKU(std::string sku);
	void sortByPrice(double price);
	void displaySortedProducts(HWND& hProductsList);
	int getIDbyIndex(int index);
};

