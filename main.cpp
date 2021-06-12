#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>

using namespace std;


class Family {//��ͥ��Ա
public:
    bool isValuable = true;
    int number = 0;//���
    string name;//����
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

    static Family createFamily() {//����һ����ͥ
        cout << "�������ͥ������" << endl;
        Family family;
        family.name;
        cin >> family.name;
        cout << "�������ͥ�ı��" << endl;
        cin >> family.number;
        return family;
    }

};

class Bill { //�˵�
public:
    bool isValuable = true;//�����ж϶�����Ϣ�Ƿ���Ч
    int family;//���������ļ�ͥ
    int num = 0;//�˵����
    string call;//�˵�����
    string type;//�˵�����
    double money = 0;//�˵����
    int year = 1;//��
    int month = 1;//��
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

    static Bill createBill() {//����һ������

        Bill bill;
        cout << "�������˵����" << endl;
        cin >> bill.num;
        cout << "�������˵�����" << endl;
        cin >> bill.call;
        cout << "�������˵����" << endl;
        cin >> bill.money;
        cout << "�������˵�����" << endl;
        cin >> bill.type;
        cout << "�������˵����" << endl;
        cin >> bill.year;
        cout << "�������˵��·�" << endl;
        cin >> bill.month;
        cout << "�������˵������ļ�ͥ���" << endl;
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
        cout<<"����ɹ���"<<endl;
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
            cout<<"������"<<bills.size()<<"���˵�����"<<endl;
        }else{
            cout<<"δ�ܼ����κ��˵�����"<<endl;
        }

        if(!families.empty()){
            cout<<"������"<<families.size()<<"���û�����"<<endl;
        }else{
            cout<<"δ�ܼ����κ��û�����"<<endl;
        }

        f1.close();
        f2.close();


    }
    void addBill(Bill bill) { bills.push_back(bill); };//����һ��������ϵͳ
    void showBills(vector<Bill> bs) {//չʾ������Ϣ
        if (bs.empty()) {
            cout << "��ѯ���Ϊ�գ�" << endl;
            return;
        }
        cout << "��ͥ���   �˵����   �˵�����   �˵�����   �˵����   �˵����   �˵��·�" << endl;
        for (auto i = bs.begin(); i < bs.end(); i++) {
            cout << *i << endl;
        }
    }

    void showFamilies(vector<Family> fm) {//չʾ�û���Ϣ
        if (fm.empty()) {
            cout << "��ѯ���Ϊ�գ�" << endl;
            return;
        }
        cout << "��ͥ���   ��ͥ����" << endl;
        for (auto i = fm.begin(); i < fm.end(); i++) {
            cout << *i << endl;
        }
    }


    vector<Bill> getBillByFamily(int number) {// ����һ����ͥ�Ķ���
        vector<Bill> temp;
        for (auto i = bills.begin(); i < bills.end(); i++) {
            if (i->family == number) {
                temp.push_back(*i);
            }
        }
        return temp;
    }

    vector<Bill> getBillByFamily(const string &name) {// ����һ����ͥ�Ķ���
        vector<Bill> temp;
        for (auto i = bills.begin(); i < bills.end(); i++) {
            if (getFamily(i->family).name == name) {
                temp.push_back(*i);
            }
        }
        return temp;
    }

    vector<Bill> getBillByType(const string &type) {// ����һ�����͵Ķ���
        vector<Bill> temp;
        for (auto i = bills.begin(); i < bills.end(); i++) {
            if (i->type == type) {
                temp.push_back(*i);
            }
        }
        return temp;
    }

    Bill getBillByNum(int num) {// ���Ҷ���
        Bill bill;
        bill.isValuable = false;
        for (auto i = bills.begin(); i < bills.end(); i++) {
            if (i->num == num) {
                bill = *i;
            }
        }
        return bill;
    }

    vector<Bill> getBillByMoneyAndType() {// ���Ҷ���������Ҫ��ļ۸������
        double from, to;
        string type;

        cout << "�������ѯ����ͼ۸�" << endl;
        cin >> from;
        cout << "�������ѯ����߼۸�" << endl;
        cin >> to;
        cout << "�������ѯ���˵�����" << endl;
        cin >> type;

        vector<Bill> temp;
        for (auto i = bills.begin(); i < bills.end(); i++) {
            if (i->type == type && i->money >= from && i->money < to) {
                temp.push_back(*i);
            }
        }
        return temp;
    }

    bool modifyBill(const Bill &newBill, const Bill &targetBill) {//�޸Ķ���
        for (auto i = bills.begin(); i < bills.end(); i++) {
            if (*i == targetBill) {
                *i = newBill;
                return true;
            }
        }
        return false;
    }

    bool deleteBill(const Bill &targetBill) {//ɾ������
        for (auto i = bills.begin(); i < bills.end(); i++) {
            if (*i == targetBill) {
                bills.erase(i);
                return true;
            }
        }
        return false;
    }

    void addFamily(Family family) {//�����û���Ϣ��ϵͳ��
        families.push_back(family);
    }

    bool modifyFamily(const Family &newFamily, const Family &targetFamily) {//�޸ļ�ͥ��Ϣ
        for (auto i = families.begin(); i < families.end(); i++) {
            if (*i == targetFamily) {
                *i == newFamily;
                return true;
            }
        }
        return false;
    }

    Family getFamily(int number) {//��ȡһ����ͥ��Ϣ
        Family family;
        family.isValuable = false;
        for (auto i = families.begin(); i < families.end(); i++) {
            if (i->number == number) {
                family = *i;
            }
        }
        return family;
    }

    Family getFamily(string name) {//��ȡһ����ͥ��Ϣ
        Family family;
        for (auto i = families.begin(); i < families.end(); i++) {
            if (i->name == name) {
                family = *i;
            }
        }
        return family;
    }

    vector<Family> getFamilies(int number) {//��ȡ��ͥ��Ϣ
        vector<Family> temp;
        for (auto i = families.begin(); i < families.end(); i++) {
            if (i->number == number) {
                temp.push_back(*i);
            }
        }
        return temp;
    }

    vector<Family> getFamilies(string name) {//��ȡ��ͥ��Ϣ
        vector<Family> temp;
        for (auto i = families.begin(); i < families.end(); i++) {
            if (i->name == name) {
                temp.push_back(*i);
            }
        }
        return temp;
    }

    bool deleteFamily(const Family &target) {//ɾ����ͥ��Ϣ
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
    cout << "************��ͥ�˵�����ϵͳ************" << endl;
    cout << "*************************************" << endl;
}

int showOption() {//չʾ����ѡ��
    cout << "���������Ĳ���ѡ��" << endl;
    cout << "1 �鿴���ж��� 2 �鿴�����û� 3 �������� 4 �����û�" << endl;
    cout << "5 ɾ������ 6 ɾ���û� 7 �޸Ķ��� 8 �޸��û���Ϣ 9 ��ѯ���� 0 ����" << endl;
    int option;
    cin >> option;

    if (option < 0 || option > 9) {
        cout << "��������ȷ��ѡ��!" << endl;
        return showOption();
    }
    return option;

}

int searchOption() {//չʾ����ѡ��
    cout << "���������Ĳ���ѡ��" << endl;
    cout << "1 ��ѯ�û����� 2 ��ѯ�˵�(�û���) 3 ��ѯ�˵�(����) 4���ݽ�Χ���˵����Ͳ�ѯ" << endl;
    int option;
    cin >> option;

    if (option < 1 || option > 4) {
        cout << "��������ȷ��ѡ��!" << endl;
        return showOption();
    }
    return option;

}

int getNumber() {
    cout << "��������" << endl;
    int num;
    cin >> num;
    return num;
}


string getName() {
    cout << "������" << endl;
    string name;
    cin >> name;
    return name;
}

void modifyBill(BillManagerSystem &billManagerSystem) {//�޸Ķ���
    cout << "������Ҫ�޸ĵĶ���" << endl;
    Bill oldBill = billManagerSystem.getBillByNum(getNumber());
    if (!oldBill.isValuable) {
        cout << "�Ҳ���������Ϣ!��������ȷ�Ķ������" << endl;
        return;
    }
    cout << "�������µ��˵���Ϣ" << endl;
    Bill newBill = Bill::createBill();
    billManagerSystem.modifyBill(newBill, oldBill);
    cout << "�޸ĳɹ���" << endl;
}

void modifyFamily(BillManagerSystem &billManagerSystem) {//�޸��û���Ϣ
    cout << "������Ҫ�޸ĵļ�ͥ���" << endl;
    Family oldFamily = billManagerSystem.getFamily(getNumber());
    if (!oldFamily.isValuable) {
        cout << "�Ҳ���������Ϣ!��������ȷ��ͥ���" << endl;
        return;
    }
    cout << "�������µļ�ͥ��Ϣ" << endl;
    Family newFamily = Family::createFamily();

    billManagerSystem.modifyFamily(newFamily, oldFamily);
    cout << "�޸ĳɹ���" << endl;
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
                    cout << "��������ȷ������" << endl;
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
                cout << (billManagerSystem.deleteBill(billManagerSystem.getBillByNum(getNumber())) ? "ɾ���ɹ�!"
                                                                                                   : "ɾ��ʧ�ܣ�δ�ҵ�Ŀ��")
                     << endl;
                break;
            case 6:
                cout << (billManagerSystem.deleteFamily(billManagerSystem.getFamily(getNumber())) ? "ɾ���ɹ�!"
                                                                                                  : "ɾ��ʧ�ܣ�δ�ҵ�Ŀ��")
                     << endl;
                break;
            case 7:
                modifyBill(billManagerSystem);
                break;
            case 8:
                modifyFamily(billManagerSystem);
                break;
            default:
                cout << "��������ȷ������" << endl;
                break;
        }
    }
}

