#include "framework.h"
#include "Supplier.h"

Supplier::Supplier() 
	: id(0), company_name(""), company_mobile(""), company_mail(""), address(""), f_name(""), 
	l_name(""), mobile(""), mail(""), jobtitle(""), goods_resived(0), total_coast(0.0)
{}

Supplier::Supplier(int id, std::string company_name, std::string company_mobile, std::string company_mail, std::string address, std::string f_name, std::string l_name, std::string mobile, std::string mail, std::string jobtitle, int goods_resived, double total_coast)
	: id(id), company_name(company_name), company_mobile(company_mobile), company_mail(company_mail), address(address), f_name(f_name), l_name(l_name), mobile(mobile), mail(mail), jobtitle(jobtitle), goods_resived(goods_resived), total_coast(total_coast)
{}



int Supplier::getId() const
{
	return id;
}

std::string Supplier::getComName() const
{
	return company_name;
}

std::string Supplier::getComMob() const
{
	return company_mobile;
}

std::string Supplier::getComMail() const
{
	return company_mail;
}

std::string Supplier::getAddress() const
{
	return address;
}

std::string Supplier::getFname() const
{
	return f_name;
}

std::string Supplier::getLname() const
{
	return l_name;
}

std::string Supplier::getMob() const
{
	return mobile;
}

std::string Supplier::getMail() const
{
	return mail;
}

std::string Supplier::getJobTitle() const
{
	return jobtitle;
}

int Supplier::getGoodsResive() const
{
	return goods_resived;
}

double Supplier::getTotalCoast() const
{
	return total_coast;
}

void Supplier::setId(int id)
{
	this->id = id; 
}

void Supplier::setComName(std::string company_name)
{
	this->company_name = company_name;
}

void Supplier::setComMob(std::string company_mobile)
{
	this->company_mobile = company_mobile; 
}

void Supplier::setComMail(std::string company_mail)
{
	this->company_mail = company_mail;
}

void Supplier::setAddress(std::string address)
{
	this->address = address;
}

void Supplier::setFname(std::string f_name)
{
	this->f_name = f_name;
}

void Supplier::setLname(std::string l_name)
{
	this->l_name = l_name;
}

void Supplier::setMob(std::string mobile)
{
	this->mobile = mobile;
}

void Supplier::setMail(std::string mail)
{
	this->mail = mail;
}

void Supplier::setJobTitle(std::string jobtitle)
{
	this->jobtitle = jobtitle;
}

void Supplier::setGoodsResive(int goods_resived)
{
	this->goods_resived = goods_resived;
}

void Supplier::setTotalCoast(double total_coast)
{
	this->total_coast = total_coast;
}
