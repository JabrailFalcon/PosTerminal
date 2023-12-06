#pragma once

class Product
{
	int id;
	std::string sku;
	std::string name;
	std::string category;
	double in_price;
	double out_price;
	std::string description;
	int quantity;
public:
	Product();
	Product(int id, std::string sku, std::string name, std::string category, double in_price, double out_price, std::string description, int quantity);
	int getID();
	std::string getSKU();
	std::string getName();
	std::string getCategory();
	double getIn_price();
	double getOut_price();
	std::string getDescription();
	int getQuantity();
	void setID(int id);
	void setSKU(std::string sku);
	void setName(std::string name);
	void setCategory(std::string category);
	void setIn_price(double in_price);
	void setOut_price(double out_price);
	void setDescription(std::string description);
	void setQuantity(int quantity);
};

