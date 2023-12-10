#include "framework.h"
#include "SuppliersRepo.h"


SuppliersRepo::SuppliersRepo(std::string filePath) : filePath(filePath) 
{}

void SuppliersRepo::loadData()
{
	supliers.clear();
	Json::Value data;
	Json::Reader reader;
	std::ifstream fin; 
	fin.open(filePath); 
	reader.parse(fin, data); 
	fin.close();
	// ->
	int size = data["size"].asInt(); 
	const Json::Value list = data["list"]; 
	
	for (int i = 0; i < size; i++) {
		Supplier sup = { 
			list[i]["id"].asInt(),
			list[i]["company_name"].asString(),
			list[i]["company_mobile"].asString(),
			list[i]["company_email"].asString(),
			list[i]["address"].asString(),
			list[i]["f_name"].asString(),
			list[i]["l_name"].asString(),
			list[i]["mobile"].asString(),
			list[i]["email"].asString(),
			list[i]["jobtitle"].asString(),
			list[i]["goods_resived"].asInt(),
			list[i]["total_coast"].asDouble() 
		}; 

		supliers.push_back(sup); 
	}
	
}

void SuppliersRepo::saveData()
{
	
	Json::Value data;
	Json::Reader reader;
	std::ifstream fin; 
	fin.open(filePath); 
	// ->
	reader.parse(fin, data);
	fin.close();

	Json::Value nList;

	for (int i = 0; i < supliers.size(); i++) {
		nList["id"] = supliers[i].getId();
		nList["company_name"] = supliers[i].getComName();
		nList["company_mobile"] = supliers[i].getComMob();
		nList["company_email"] = supliers[i].getComMail();
		nList["address"] = supliers[i].getAddress();
		nList["f_name"] = supliers[i].getFname();
		nList["l_name"] = supliers[i].getLname();
		nList["mobile"] = supliers[i].getMob();
		nList["email"] = supliers[i].getMail();
		nList["jobtitle"] = supliers[i].getJobTitle();
		nList["goods_resived"] = supliers[i].getGoodsResive();
		nList["total_coast"] = supliers[i].getTotalCoast();
		// ->

		data["list"][i] = nList;
	}

	data["size"] = supliers.size();

	std::ofstream fout; 
	Json::StyledStreamWriter writer; 
	
	fout.open(filePath);
	writer.write(fout, data); 
	fout.close(); 
}

void SuppliersRepo::addSuplier(TCHAR comName[100], TCHAR ComMob[100], TCHAR ComMail[100], TCHAR Address[100], TCHAR Fname[100], TCHAR Lname[100], TCHAR Mob[100], TCHAR Mail[100], TCHAR JobTitle[100])
{
	
}

void SuppliersRepo::delSuplier(int id)
{
	auto iter = std::find_if(supliers.begin(), supliers.end(),
		[id](Supplier& s) {
			return (s.getId() == id);
		});
	if (iter != supliers.end()) {
		supliers.erase(iter);
	}
}

void SuppliersRepo::editExist()
{
}

void SuppliersRepo::displayExist(TCHAR sup[100], HWND hDlg, HWND hList) const
{
	char buff[100];
	wcstombs_s(NULL, buff, sup, 100);

	auto iter1 = std::find_if(supliers.begin(), supliers.end(),
		[buff](const Supplier& supplier) {  
		return (supplier.getComName() == buff || supplier.getComMob() == buff || supplier.getComMail() == buff); 
		});

	if (iter1 == supliers.end()) {
		MessageBox(hDlg, L"Suppliers with exist attribute, not found!", L"Warning!", MB_OK | MB_ICONWARNING);
	}
	else {
		int n = 1;
		SendMessage(hList, LB_RESETCONTENT, 0, 0); 
		std::for_each(supliers.begin(), supliers.end(), 
			[buff, &hList, &n](const Supplier& s) {
				
				if (s.getComName() == buff || s.getComMob() == buff || s.getComMail() == buff) { 
					Helper helper; 
					std::string suplier = std::to_string(n++) + "  " + s.getComName() + " " + std::to_string(s.getGoodsResive()) + "  " + std::to_string(s.getTotalCoast()); 
					TCHAR* pInfo = helper.string_tchar(suplier); 
					SendMessage(hList, LB_ADDSTRING, 0, LPARAM(pInfo)); 
				}
			}); 
	}
}

void SuppliersRepo::displayAll(HWND hDlg, HWND hList) const
{
	Helper helper;
	int n = 1;
	for (auto s : supliers) {
		std::string suplier = std::to_string(n++) + "  " + s.getComName() + " " + std::to_string(s.getGoodsResive()) + "  " + std::to_string(s.getTotalCoast());
		TCHAR* pInfo = helper.string_tchar(suplier);
		SendMessage(hList, LB_ADDSTRING, 0, LPARAM(pInfo));
		delete[] pInfo;
	}
}

std::vector<Supplier> SuppliersRepo::getSuppliers()
{
	return supliers;
}
