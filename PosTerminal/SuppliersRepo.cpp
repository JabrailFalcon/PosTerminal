#include "framework.h"
#include "SuppliersRepo.h"


SuppliersRepo::SuppliersRepo(std::string filePath, std::string fileIdBuff) : filePath(filePath), fileIdBuff(fileIdBuff)
{}

void SuppliersRepo::loadData()
{
	indent.clear();
	//->
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
		indent.push_back(sup.getId());
		sortname.push_back(sup.getComName());
	}
}

void SuppliersRepo::saveData()
{
	indent.clear();
	//
	Json::Value data;
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
		//
		indent.push_back(supliers[i].getId());
	}
	  
	data["size"] = supliers.size();

	std::ofstream fout; 
	Json::StyledStreamWriter writer; 
	//->
	fout.open(filePath);
	writer.write(fout, data); 
	fout.close(); 
}

void SuppliersRepo::addSuplier(HWND hDlg, HWND hList, TCHAR comName[100], TCHAR ComMob[100], TCHAR ComMail[100], TCHAR Address[100], TCHAR Fname[100], TCHAR Lname[100], TCHAR Mob[100], TCHAR Mail[100], TCHAR JobTitle[100])
{
	Helper helper; 
	char buff1[100];
	char buff2[100];
	char buff3[100];
	char buff4[100];
	char buff5[100];
	char buff6[100];
	char buff7[100];
	char buff8[100];
	char buff9[100];
	// ->
	int id = supliers.back().getId() + 1;
	
	// ->
	int goodsRes = 0;
	double totalCost = 0.0;
	wcstombs_s(NULL, buff1, comName, 100);
	wcstombs_s(NULL, buff2, ComMob, 100);
	wcstombs_s(NULL, buff3, ComMail, 100); 
	wcstombs_s(NULL, buff4, Address, 100); 
	wcstombs_s(NULL, buff5, Fname, 100); 
	wcstombs_s(NULL, buff6, Lname, 100); 
	wcstombs_s(NULL, buff7, Mob, 100); 
	wcstombs_s(NULL, buff8, Mail, 100); 
	wcstombs_s(NULL, buff9, JobTitle, 100); 
	// ->
	Supplier s(id, buff1, buff2, buff3, buff4, buff5, buff6, buff7, buff8, buff9, goodsRes, totalCost);

	supliers.push_back(s); 
	indent.push_back(id); 

	int n = indent.size();
	// ->
	std::string suplier = std::to_string(n) + "               " + s.getComName() +
		"                                                                                                                                                            "
		+ std::to_string(s.getGoodsResive()) + "                                            " + std::to_string(s.getTotalCoast()); 
	TCHAR* pInfo = helper.string_tchar(suplier); 
	SendMessage(hList, LB_ADDSTRING, 0, LPARAM(pInfo)); 
	delete[] pInfo;
	
	// ->
	std::ofstream fout; 
	fout.open(fileIdBuff);
	int i = 0;
	for (auto& in : indent) {
		fout << indent[i] << std::endl;
		i++;
	}
	fout.close();
	
	saveData();
}

void SuppliersRepo::delSuplier(int index)
{
	
	int id = indent[index]; 
	auto iter = std::find_if(supliers.begin(), supliers.end(),
		[id](Supplier& s) { 
			return (s.getId() == id);
		}); 
	if (iter != supliers.end()) { 
		supliers.erase(iter); 	
	}


	saveData(); 

}

void SuppliersRepo::displayEditExist(int index, HWND hEdit1, HWND hEdit2, HWND hEdit3, HWND hEdit4, HWND hEdit5, HWND hEdit6, HWND hEdit7, HWND hEdit8, HWND hEdit9)
{
	Helper helper; 
	int id = indent[index];
	// ->
	auto iter = std::find_if(supliers.begin(), supliers.end(), 
		[id](const Supplier& s) {
			return (s.getId() == id);
		});
	// ->
	TCHAR* buff1 = helper.string_tchar(iter->getComName());
	TCHAR* buff2 = helper.string_tchar(iter->getComMail());
	TCHAR* buff3 = helper.string_tchar(iter->getComMob());
	TCHAR* buff4 = helper.string_tchar(iter->getAddress());
	TCHAR* buff5 = helper.string_tchar(iter->getFname());
	TCHAR* buff6 = helper.string_tchar(iter->getLname());
	TCHAR* buff7 = helper.string_tchar(iter->getMob());
	TCHAR* buff8 = helper.string_tchar(iter->getMail());
	TCHAR* buff9 = helper.string_tchar(iter->getJobTitle());
	// ->
	SetWindowText(hEdit1, buff1); 
	SetWindowText(hEdit2, buff2);
	SetWindowText(hEdit3, buff3);
	SetWindowText(hEdit4, buff4);
	SetWindowText(hEdit5, buff5);
	SetWindowText(hEdit6, buff6);
	SetWindowText(hEdit7, buff7);
	SetWindowText(hEdit8, buff8);
	SetWindowText(hEdit9, buff9);

	delete buff1, buff2, buff3, buff4, buff5, buff6, buff7, buff8, buff9;
}

void SuppliersRepo::editExist(int index, TCHAR comName[100], TCHAR ComMob[100], TCHAR ComMail[100], TCHAR Address[100], TCHAR Fname[100], TCHAR Lname[100], TCHAR Mob[100], TCHAR Mail[100], TCHAR JobTitle[100])
{
	int id = indent[index]; 
	// ->
	char buff1[100];
	char buff2[100];
	char buff3[100];
	char buff4[100];
	char buff5[100];
	char buff6[100];
	char buff7[100];
	char buff8[100];
	char buff9[100];
	// ->
	wcstombs_s(NULL, buff1, comName, 100); 
	wcstombs_s(NULL, buff2, ComMob, 100); 
	wcstombs_s(NULL, buff3, ComMail, 100); 
	wcstombs_s(NULL, buff4, Address, 100); 
	wcstombs_s(NULL, buff5, Fname, 100); 
	wcstombs_s(NULL, buff6, Lname, 100); 
	wcstombs_s(NULL, buff7, Mob, 100); 
	wcstombs_s(NULL, buff8, Mail, 100); 
	wcstombs_s(NULL, buff9, JobTitle, 100); 
	// ->
	for (int i = 0; i < supliers.size(); i++) {
		if (supliers[i].getId() == id) {
			supliers[i].setComName(buff1); 
			supliers[i].setComMail(buff3); 
			supliers[i].setComMob(buff2);  
			supliers[i].setAddress(buff4);  
			supliers[i].setFname(buff5);
			supliers[i].setLname(buff6);
			supliers[i].setMob(buff7);
			supliers[i].setMail(buff8);
			supliers[i].setJobTitle(buff9); 
		}
	}
	saveData(); 
}

void SuppliersRepo::displayExist(TCHAR sup[100], HWND hDlg, HWND hList)
{
	// ->
	char buff[100];
	wcstombs_s(NULL, buff, sup, 100);
	// ->
	auto iter1 = std::find_if(supliers.begin(), supliers.end(),
		[buff](const Supplier& supplier) {  
		return (supplier.getComName() == buff || supplier.getComMob() == buff || supplier.getComMail() == buff); 
		});

	if (iter1 == supliers.end()) {
		MessageBox(hDlg, L"Suppliers with exist attribute, not found!", L"Warning!", MB_OK | MB_ICONWARNING);
	}
	else {
		indent.clear(); 
		int n = 1;
		SendMessage(hList, LB_RESETCONTENT, 0, 0); 
		// ->
		std::ofstream fout;
		fout.open(fileIdBuff);

		// ->
		std::for_each(supliers.begin(), supliers.end(), 
			[buff, &hList, &n, &fout](const Supplier& s) {
				
				if (s.getComName() == buff || s.getComMob() == buff || s.getComMail() == buff) { 
					
					Helper helper; 
					std::string suplier = std::to_string(n++) + "                  " + s.getComName() + "                                                                                                        " 
						+ std::to_string(s.getGoodsResive()) + "                  " + std::to_string(s.getTotalCoast()); 
					TCHAR* pInfo = helper.string_tchar(suplier); 
					SendMessage(hList, LB_ADDSTRING, 0, LPARAM(pInfo));				
					fout << s.getId() << std::endl;
				}
			});
		fout.close();
		
		// ->
		std::ifstream fin; 
		fin.open(fileIdBuff); 
		// -> 
		char buff[100];
		while (!fin.eof()) {
			fin.getline(buff, 100);
			if (strlen(buff) > 0) { 
				indent.push_back(atoi(buff)); 

			} 
		}
		fin.close();
	}
}

void SuppliersRepo::displayAll(HWND hDlg, HWND hList)
{
	Helper helper;
	int n = 1;
	indent.clear();
	

	for (auto s : supliers) {
		indent.push_back(supliers[n - 1].getId());
		std::string suplier = std::to_string(n++) + "               " + 
			s.getComName() + "                                                                                                                                                            " + 
			std::to_string(s.getGoodsResive()) + "                                            " + std::to_string(s.getTotalCoast());
		TCHAR* pInfo = helper.string_tchar(suplier);
		SendMessage(hList, LB_ADDSTRING, 0, LPARAM(pInfo));
		delete[] pInfo;
	}
	
}

void SuppliersRepo::comboSort(HWND hDlg, HWND hCombo1)
{
	SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)_T("By name"));
	SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)_T("By goods recived"));
	SendMessage(hCombo1, CB_ADDSTRING, 0, (LPARAM)_T("By total cost"));
}

void SuppliersRepo::sortByName(HWND hDlg, HWND hList)
{
	Helper helper;
	indent.clear(); 
	sort(sortname.begin(), sortname.end()); 
	//->
	SendMessage(hList, LB_RESETCONTENT, 0, 0); 
	int n = 1;
	
	for (int i = 0; i < sortname.size(); i++) {
		for (auto s : supliers) {
			if (s.getComName() == sortname[i]) {
				std::string sup = std::to_string(n++) + "               " +
					s.getComName() + "                                                                                                                                                            " +
					std::to_string(s.getGoodsResive()) + "                                            " + std::to_string(s.getTotalCoast()); 
				// ->
				TCHAR* pInfo = helper.string_tchar(sup);
				SendMessage(hList, LB_ADDSTRING, 0, LPARAM(pInfo)); 
				indent.push_back(s.getId()); 
				delete[] pInfo;
			}
		}
	}

	
}


std::vector<Supplier> SuppliersRepo::getSuppliers()
{
	return supliers;
}
