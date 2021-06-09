#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
using namespace std;


class Family {//家庭成员
public:
    int number = 0;//编号
    string name;//姓名
    friend ostream &operator<<(ostream &os, const Family &family) {
        os << "number: " << family.number << " name: " << family.name;
        return os;
    }

    bool operator==(const Family &rhs) const {
        return number == rhs.number &&
               name == rhs.name;
    }

};

class Bill { //账单
public:
    Family family;
    int num = 0;//账单编号
    string call;//账单名称
    string type;//账单类型
    double money = 0;//账单金额
    int year = 1;//年
    int month = 1;//月
    friend ostream &operator<<(ostream &os, const Bill &bill) {
        os << "family: " << bill.family << " num: " << bill.num << " call: " << bill.call << " type: " << bill.type
           << " money: " << bill.money << " year: " << bill.year << " month: " << bill.month;
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



};
class BillManagerSystem{
    vector<Bill> bills;
    vector<Family> families;
public:
    int getSize(){return bills.size();};
    void addBill(Bill bill){bills.push_back(bill);};
    vector<Bill> getBillByFamily(int number){
        vector<Bill> temp;
        for(auto i=bills.begin();i<bills.end();i++){
            if(i->family.number==number){
                temp.push_back(*i);
            }
        }
        return temp;
    }
    vector<Bill> getBillByFamily(const string& name){
        vector<Bill> temp;
        for(auto i=bills.begin();i<bills.end();i++){
            if(i->family.name==name){
                temp.push_back(*i);
            }
        }
        return temp;
    }
    vector<Bill> getBillByType(const string& type){
        vector<Bill> temp;
        for(auto i=bills.begin();i<bills.end();i++){
            if(i->type==type){
                temp.push_back(*i);
            }
        }
        return temp;
    }
    Bill getBillByNum(int num){
        for(auto i=bills.begin();i<bills.end();i++){
            if(i->num==num){
                return *i;
            }
        }
    }
    vector<Bill> getBillByMoneyAndType(double from,double to,const string& type){
        vector<Bill> temp;
        for(auto i=bills.begin();i<bills.end();i++){
            if(i->type==type&&i->money>=from&&i->money<to){
                temp.push_back(*i);
            }
        }
        return temp;
    }
    bool modifyBill(const Bill& newBill,const Bill& targetBill){
        for(auto i=bills.begin();i<bills.end();i++){
            if(*i==targetBill){
                *i=newBill;
                return true;
            }
        }
        return false;
    }
    bool deleteBill(const Bill& targetBill){
        for(auto i=bills.begin();i<bills.end();i++){
            if(*i==targetBill){
                bills.erase(i);
                return true;
            }
        }
        return false;
    }
    void addFamily(Family family){
        families.push_back(family);
    }
    bool modifyFamily(const Family& newFamily,const Family& targetFamily){
        for(auto i=families.begin();i<families.end();i++){
            if(*i==targetFamily){
                *i==newFamily;
                return true;
            }
        }
        return false;
    }
    Family getFamily(int number){
        for(auto i=families.begin();i<families.end();i++){
            if(i->number==number){
                return *i;
            }
        }
    }
    Family getFamily(string name){
        for(auto i=families.begin();i<families.end();i++){
            if(i->name==name){
                return *i;
            }
        }
    }
    bool deleteFamily(const Family &target){
        for(auto i=families.begin();i<families.end();i++){
            if(*i==target){
                families.erase(i);
                return true;
            }
        }
        return false;
    }

};


