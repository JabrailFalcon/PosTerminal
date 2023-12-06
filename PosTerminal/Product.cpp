#include "framework.h"
#include "Product.h"

Product::Product() : id(0), sku(""), name(""), category(""), in_price(0.0), out_price(0.0), description(""), quantity(0)
{}

Product::Product(int id, std::string sku, std::string name, std::string category, double in_price, double out_price, std::string description, int quantity)
	: id(id), sku(sku), name(name), category(category), in_price(in_price), out_price(out_price), description(description), quantity(quantity)
{}

int Product::getID()
{
	return id;
}

std::string Product::getSKU()
{
	return sku;
}

std::string Product::getName()
{
	return name;
}

std::string Product::getCategory()
{
	return category;
}

double Product::getIn_price()
{
	return in_price;
}

double Product::getOut_price()
{
	return out_price;
}

std::string Product::getDescription()
{
	return description;
}

int Product::getQuantity()
{
	return quantity;
}

void Product::setID(int id)
{
	this->id = id;
}

void Product::setSKU(std::string sku)
{
	this->sku = sku;
}

void Product::setName(std::string name)
{
	this->name = name;
}

void Product::setCategory(std::string category)
{
	this->category = category;
}

void Product::setIn_price(double in_price)
{
	this->in_price = in_price;
}

void Product::setOut_price(double out_price)
{
	this->out_price = out_price;
}

void Product::setDescription(std::string description)
{
	this->description = description;
}

void Product::setQuantity(int quantity)
{
	this->quantity = quantity;
}
