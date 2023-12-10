#pragma once
class Supplier
{
	int id;
	std::string company_name;
	std::string company_mobile;
	std::string company_mail;
	std::string address;
	std::string f_name;
	std::string l_name;
	std::string mobile;
	std::string mail;
	std::string jobtitle;
	int goods_resived;
	double total_coast;
public:
	Supplier();
	Supplier(
	int id,
	std::string company_name,
	std::string company_mobile,
	std::string company_mail,
	std::string address,
	std::string f_name,
	std::string l_name,
	std::string mobile,
	std::string mail,
	std::string jobtitle,
	int goods_resived,
	double total_coast
	);
	
	int getId() const;
	std::string getComName() const;
	std::string getComMob() const;
	std::string getComMail() const;
	std::string getAddress() const;
	std::string getFname() const;
	std::string getLname() const;
	std::string getMob() const;
	std::string getMail() const;
	std::string getJobTitle() const;
	int getGoodsResive() const;
	double getTotalCoast() const;
	void setId(int id);
	void setComName(std::string company_name);
	void setComMob(std::string company_mobile);
	void setComMail(std::string company_mail);
	void setAddress(std::string address);
	void setFname(std::string f_name);
	void setLname(std::string l_name);
	void setMob(std::string mobile);
	void setMail(std::string mail);
	void setJobTitle(std::string jobtitle);
	void setGoodsResive(int goods_resived);
	void setTotalCoast(double total_coast);
};

