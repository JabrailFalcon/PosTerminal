#pragma once
#include "Product.h"

class ProductsRepo
{
	std::vector<Product> products;
	std::string filepath;
public:
	ProductsRepo();
	void loadData();
	void saveData();
	void displayAllProducts(HWND hDlg, HWND hProductsList) const;
	std::vector<Product> getProducts() const;
};

