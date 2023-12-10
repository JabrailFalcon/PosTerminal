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
	std::string getSKU() const;
	std::string getName() const;
	std::string getCategory() const;
	double getIn_price() const;
	double getOut_price() const;
	std::string getDescription() const;
	int getQuantity() const;
	void setID(int id);
	void setSKU(std::string sku);
	void setName(std::string name);
	void setCategory(std::string category);
	void setIn_price(double in_price);
	void setOut_price(double out_price);
	void setDescription(std::string description);
	void setQuantity(int quantity);
};

