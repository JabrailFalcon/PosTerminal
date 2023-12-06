#include "framework.h"
#include "ProductsRepo.h"
#include "Product.h"

ProductsRepo::ProductsRepo() : filepath("Data/Products.json")
{}

void ProductsRepo::loadData()
{
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
}

void ProductsRepo::displayAllProducts(HWND hDlg, HWND hProductsList) const
{
	Helper helper;
	for (auto p : products) {
		std::string product = std::to_string(p.getID()) + " " + p.getSKU() + " " + p.getName() + " " + p.getCategory() + " " + std::to_string(p.getQuantity()) + " " + std::to_string(p.getOut_price());
		TCHAR* pInfo = helper.string_tchar(product);
		SendMessage(hProductsList, LB_ADDSTRING, 0, LPARAM(pInfo));
		delete[] pInfo;
	}
}

std::vector<Product> ProductsRepo::getProducts() const
{
	return products;
}
