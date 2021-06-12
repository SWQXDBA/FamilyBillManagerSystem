#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>

using namespace std;


class Family {//家庭成员
public:
    bool isValuable = true;
    int number = 0;//编号
    string name;//姓名
    friend ostream &operator<<(ostream &os, const Family &family) {

        os << "number: " << family.number << " name: " << family.name;
        return os;
    }
    friend ofstream &operator<<(ofstream &os, const Family &family) {

        os <<family.name<<" "<<family.number<<" "<<family.isValuable;
        return os;
    }
    bool operator==(const Family &rhs) const {
        return number == rhs.number &&
               name == rhs.name;
    }

    static Family createFamily() {//创建一个家庭
        cout << "请输入家庭的名字" << endl;
        Family family;
        family.name;
        cin >> family.name;
        cout << "请输入家庭的编号" << endl;
        cin >> family.number;
        return family;
    }

};

class Bill { //账单
public:
    bool isValuable = true;//用于判断订单信息是否有效
    int family;//订单所属的家庭
    int num = 0;//账单编号
    string call;//账单名称
    string type;//账单类型
    double money = 0;//账单金额
    int year = 1;//年
    int month = 1;//月
    friend ostream &operator<<(ostream &os, const Bill &bill) {
        os << "familyNum: " << bill.family << " num: " << bill.num << " call: " << bill.call << " type: " << bill.type
           << " money: " << bill.money << " year: " << bill.year << " month: " << bill.month;
        return os;
    }
    friend ofstream &operator<<(ofstream &os, const Bill &bill) {
        os  << bill.family << " " << bill.num << " " << bill.call << " " << bill.type
           << " " << bill.money << " " << bill.year << " " << bill.month;
        return os;
    }
    bool operator==(const Bill &rhs) const {
        return family == rhs.family &&
               num == rhs.num &&
               call == rhs.call &&
               type == rhs.type &&
               money == rhs.money &&
               year == rhs.year &&
               month == rhs.month;
    }

    static Bill createBill() {//创建一个订单

        Bill bill;
        cout << "请输入账单编号" << endl;
        cin >> bill.num;
        cout << "请输入账单名称" << endl;
        cin >> bill.call;
        cout << "请输入账单金额" << endl;
        cin >> bill.money;
        cout << "请输入账单类型" << endl;
        cin >> bill.type;
        cout << "请输入账单年份" << endl;
        cin >> bill.year;
        cout << "请输入账单月份" << endl;
        cin >> bill.month;
        cout << "请输入账单所属的家庭编号" << endl;
        int num;
        cin >> num;
        bill.family = num;

        return bill;
    }



};

class BillManagerSystem {
public:
    vector<Bill> bills;
    vector<Family> families;

    BillManagerSystem() {
        load();
    }

    void save(){
        ofstream f1("data_bill.txt");
        for(auto i = bills.begin();i<bills.end();i++){
            f1<<*i<<endl;
        }

        f1.close();
        ofstream f2("data_family.txt");
        for(auto i = families.begin();i<families.end();i++){
            f2<<*i<<endl;
        }

        f2.close();
        cout<<"保存成功！"<<endl;
    }
    void load(){
        ifstream f1("data_bill.txt");
        if(f1.is_open()){
            Bill bill;
            Bill *i=&bill;
            while((f1>>i->family>>i->num>>i->call>>i->type>>i->money>>i->year>>i->month)){
                bills.push_back(bill);
            }
        }



        ifstream f2("data_family.txt");
        if(f2.is_open()){
            Family family;
            Family * i=&family;
            while(f2>>i->name>>i->number>>i->isValuable){
                families.push_back(family);
            }
        }
        if(!bills.empty()){
            cout<<"加载了"<<bills.size()<<"条账单数据"<<endl;
        }else{
            cout<<"未能加载任何账单数据"<<endl;
        }

        if(!families.empty()){
            cout<<"加载了"<<families.size()<<"条用户数据"<<endl;
        }else{
            cout<<"未能加载任何用户数据"<<endl;
        }

        f1.close();
        f2.close();


    }
    void addBill(Bill bill) { bills.push_back(bill); };//新增一个订单到系统
    void showBills(vector<Bill> bs) {//展示订单信息
        if (bs.empty()) {
            cout << "查询结果为空！" << endl;
            return;
        }
        cout << "家庭编号   账单编号   账单名称   账单类型   账单金额   账单年份   账单月份" << endl;
        for (auto i = bs.begin(); i < bs.end(); i++) {
            cout << *i << endl;
        }
    }

    void showFamilies(vector<Family> fm) {//展示用户信息
        if (fm.empty()) {
            cout << "查询结果为空！" << endl;
            return;
        }
        cout << "家庭编号   家庭名字" << endl;
        for (auto i = fm.begin(); i < fm.end(); i++) {
            cout << *i << endl;
        }
    }


    vector<Bill> getBillByFamily(int number) {// 查找一个家庭的订单
        vector<Bill> temp;
        for (auto i = bills.begin(); i < bills.end(); i++) {
            if (i->family == number) {
                temp.push_back(*i);
            }
        }
        return temp;
    }

    vector<Bill> getBillByFamily(const string &name) {// 查找一个家庭的订单
        vector<Bill> temp;
        for (auto i = bills.begin(); i < bills.end(); i++) {
            if (getFamily(i->family).name == name) {
                temp.push_back(*i);
            }
        }
        return temp;
    }

    vector<Bill> getBillByType(const string &type) {// 查找一个类型的订单
        vector<Bill> temp;
        for (auto i = bills.begin(); i < bills.end(); i++) {
            if (i->type == type) {
                temp.push_back(*i);
            }
        }
        return temp;
    }

    Bill getBillByNum(int num) {// 查找订单
        Bill bill;
        bill.isValuable = false;
        for (auto i = bills.begin(); i < bills.end(); i++) {
            if (i->num == num) {
                bill = *i;
            }
        }
        return bill;
    }

    vector<Bill> getBillByMoneyAndType() {// 查找订单，根据要求的价格和类型
        double from, to;
        string type;

        cout << "请输入查询的最低价格" << endl;
        cin >> from;
        cout << "请输入查询的最高价格" << endl;
        cin >> to;
        cout << "请输入查询的账单类型" << endl;
        cin >> type;

        vector<Bill> temp;
        for (auto i = bills.begin(); i < bills.end(); i++) {
            if (i->type == type && i->money >= from && i->money < to) {
                temp.push_back(*i);
            }
        }
        return temp;
    }

    bool modifyBill(const Bill &newBill, const Bill &targetBill) {//修改订单
        for (auto i = bills.begin(); i < bills.end(); i++) {
            if (*i == targetBill) {
                *i = newBill;
                return true;
            }
        }
        return false;
    }

    bool deleteBill(const Bill &targetBill) {//删除订单
        for (auto i = bills.begin(); i < bills.end(); i++) {
            if (*i == targetBill) {
                bills.erase(i);
                return true;
            }
        }
        return false;
    }

    void addFamily(Family family) {//新增用户信息到系统中
        families.push_back(family);
    }

    bool modifyFamily(const Family &newFamily, const Family &targetFamily) {//修改家庭信息
        for (auto i = families.begin(); i < families.end(); i++) {
            if (*i == targetFamily) {
                *i == newFamily;
                return true;
            }
        }
        return false;
    }

    Family getFamily(int number) {//获取一个家庭信息
        Family family;
        family.isValuable = false;
        for (auto i = families.begin(); i < families.end(); i++) {
            if (i->number == number) {
                family = *i;
            }
        }
        return family;
    }

    Family getFamily(string name) {//获取一个家庭信息
        Family family;
        for (auto i = families.begin(); i < families.end(); i++) {
            if (i->name == name) {
                family = *i;
            }
        }
        return family;
    }

    vector<Family> getFamilies(int number) {//获取家庭信息
        vector<Family> temp;
        for (auto i = families.begin(); i < families.end(); i++) {
            if (i->number == number) {
                temp.push_back(*i);
            }
        }
        return temp;
    }

    vector<Family> getFamilies(string name) {//获取家庭信息
        vector<Family> temp;
        for (auto i = families.begin(); i < families.end(); i++) {
            if (i->name == name) {
                temp.push_back(*i);
            }
        }
        return temp;
    }

    bool deleteFamily(const Family &target) {//删除家庭信息
        for (auto i = families.begin(); i < families.end(); i++) {
            if (*i == target) {
                families.erase(i);
                return true;
            }
        }
        return false;
    }


};

void menu() {
    cout << "*************************************" << endl;
    cout << "************家庭账单管理系统************" << endl;
    cout << "*************************************" << endl;
}

int showOption() {//展示操作选项
    cout << "请输入您的操作选项" << endl;
    cout << "1 查看所有订单 2 查看所有用户 3 新增订单 4 新增用户" << endl;
    cout << "5 删除订单 6 删除用户 7 修改订单 8 修改用户信息 9 查询操作 0 保存" << endl;
    int option;
    cin >> option;

    if (option < 0 || option > 9) {
        cout << "请输入正确的选项!" << endl;
        return showOption();
    }
    return option;

}

int searchOption() {//展示操作选项
    cout << "请输入您的操作选项" << endl;
    cout << "1 查询用户资料 2 查询账单(用户名) 3 查询账单(类型) 4根据金额范围和账单类型查询" << endl;
    int option;
    cin >> option;

    if (option < 1 || option > 4) {
        cout << "请输入正确的选项!" << endl;
        return showOption();
    }
    return option;

}

int getNumber() {
    cout << "请输入编号" << endl;
    int num;
    cin >> num;
    return num;
}


string getName() {
    cout << "请输入" << endl;
    string name;
    cin >> name;
    return name;
}

void modifyBill(BillManagerSystem &billManagerSystem) {//修改订单
    cout << "请输入要修改的订单" << endl;
    Bill oldBill = billManagerSystem.getBillByNum(getNumber());
    if (!oldBill.isValuable) {
        cout << "找不到订单信息!请输入正确的订单编号" << endl;
        return;
    }
    cout << "请输入新的账单信息" << endl;
    Bill newBill = Bill::createBill();
    billManagerSystem.modifyBill(newBill, oldBill);
    cout << "修改成功！" << endl;
}

void modifyFamily(BillManagerSystem &billManagerSystem) {//修改用户信息
    cout << "请输入要修改的家庭编号" << endl;
    Family oldFamily = billManagerSystem.getFamily(getNumber());
    if (!oldFamily.isValuable) {
        cout << "找不到订单信息!请输入正确家庭编号" << endl;
        return;
    }
    cout << "请输入新的家庭信息" << endl;
    Family newFamily = Family::createFamily();

    billManagerSystem.modifyFamily(newFamily, oldFamily);
    cout << "修改成功！" << endl;
}

int main() {
    menu();
    BillManagerSystem billManagerSystem;
    while (true) {
        int option = showOption();
        if (option == 9) {
            flag1:;
            option = searchOption();
            switch (option) {
                case 1:
                    billManagerSystem.showFamilies(billManagerSystem.getFamilies(getNumber()));
                    break;
                case 2:
                    billManagerSystem.showBills(billManagerSystem.getBillByFamily(getName()));
                    break;
                case 3:
                    billManagerSystem.showBills(billManagerSystem.getBillByType(getName()));
                    break;
                case 4:
                    billManagerSystem.showBills(billManagerSystem.getBillByMoneyAndType());
                    break;
                default:
                    cout << "请输入正确的数字" << endl;
                    goto flag1;
                    break;
            }
            continue;
        }
        switch (option) {
            case 0:
                billManagerSystem.save();
                break;
            case 1:
                billManagerSystem.showBills(billManagerSystem.bills);
                break;
            case 2:
                billManagerSystem.showFamilies(billManagerSystem.families);
                break;
            case 3:
                billManagerSystem.addBill(Bill::createBill());
                break;
            case 4:
                billManagerSystem.addFamily(Family::createFamily());
                break;
            case 5:
                cout << (billManagerSystem.deleteBill(billManagerSystem.getBillByNum(getNumber())) ? "删除成功!"
                                                                                                   : "删除失败！未找到目标")
                     << endl;
                break;
            case 6:
                cout << (billManagerSystem.deleteFamily(billManagerSystem.getFamily(getNumber())) ? "删除成功!"
                                                                                                  : "删除失败！未找到目标")
                     << endl;
                break;
            case 7:
                modifyBill(billManagerSystem);
                break;
            case 8:
                modifyFamily(billManagerSystem);
                break;
            default:
                cout << "请输入正确的数字" << endl;
                break;
        }
    }
}

