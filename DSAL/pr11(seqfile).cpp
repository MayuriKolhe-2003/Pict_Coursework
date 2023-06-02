#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class student
{
    string name;
    int rollno;
    int div;
    string address;

public:
    student()
    {
        name = address = "";
        rollno = div = -1;
    }
    student(string n, string a, int no, int d)
    {
        name = n;
        address = a;
        rollno = no;
        div = d;
    }
    void accept()
    {
        cout<<"Enter rollno : ";
        cin>>rollno;
        cout<<"Enter name : ";
        cin>>name;
        cout<<"Enter div : ";
        cin>>div;
        cout<<"Enter address : ";
        cin>>address;

    }
    void show()
    {
        cout << rollno << " \t\t " << name << " \t\t " << div << " \t\t " << address << endl;
    }
    friend class database;
};

class database
{
    student stu;
    student tmp;
public:
    void insert()
    {
        fstream fout,fin;
        bool found = false;
        stu.accept();

        fout.open("student_data.txt", ios::app | ios::binary);
        fin.open("student_data.txt", ios::in | ios::binary);
        if (!fout)
        {
            cout << "Error opening file" << endl;
            return;
        }
        else
        {
            fin.read((char *)&tmp, sizeof(tmp));
            while (!fin.eof())
            {
                if(stu.rollno == tmp.rollno)
                {
                    found = true;
                    break;
                }
                fin.read((char *)&tmp, sizeof(tmp));
            }
            if(!found)
            {
                fout.write((char *)&stu, sizeof(stu));
                cout << "added\n";
            }else{
                cout<<"Student with rollno :"<< stu.rollno<<"already exists"<<endl;
            }
        }
        fout.close();
        fin.close();
    }

    void display()
    {
        fstream fin;
        fin.open("student_data.txt", ios::in | ios::binary);
        if (!fin)
        {
            cout << "Error opening file" << endl;
            return;
        }
        else
        {
            cout << "Rollno\t\t Name\t\t Div\t\t Address" << endl;
            fin.read((char *)&stu, sizeof(stu));
            while (!fin.eof())
            {
                stu.show();
                fin.read((char *)&stu, sizeof(stu));
            }
        }
        fin.close();
    }
    void search()
    {
        fstream fin;
        int n;
        bool found = false;

        fin.open("student_data.txt", ios::in | ios::binary);
        if (!fin)
        {
            cout << "Error opening file" << endl;
            return;
        }
        else
        {
            cout<<"Enter rollno to search : ";
            cin>>n;

            fin.read((char *)&stu, sizeof(stu));
            while (!fin.eof())
            {
                if(stu.rollno == n)
                {
                    found = true;
                    cout << "Rollno\t\t Name\t\t Div\t\t Address" << endl;
                    stu.show();
                    return;
                }
                fin.read((char *)&stu, sizeof(stu));
            }
        }
        fin.close();
    }

    void remove_student()
    {
        fstream fin,fout;
        int n;
        bool found = false;

        fin.open("student_data.txt", ios::in | ios::binary);
        fout.open("temp.txt", ios::out | ios::binary);
        if (!fin)
        {
            cout << "Error opening file" << endl;
            return;
        }
        else
        {
            cout<<"Enter rollno to delete : ";
            cin>>n;

            fin.read((char *)&stu, sizeof(stu));
            while (!fin.eof())
            {
                if(stu.rollno != n)
                {
                    fout.write((char*)&stu , sizeof(stu));
                }else{
                    found = true;
                    cout<<"Record deleted successfully"<<endl;
                }
                fin.read((char *)&stu, sizeof(stu));
            }
        }
        fin.close();
        fout.close();
        if(!found)
        {
            cout<<"Record not found\n";
        }
        remove("student_data.txt");
        rename("temp.txt","student_data.txt");
    }

    void update_student()
    {
        student news;
        fstream fin,fout;
        int n;
        bool found = false;

        fin.open("student_data.txt", ios::in | ios::binary);
        fout.open("temp.txt", ios::out | ios::binary);
        if (!fin)
        {
            cout << "Error opening file" << endl;
            return;
        }
        else
        {
            cout<<"Enter rollno to delete : ";
            cin>>n;

            fin.read((char *)&stu, sizeof(stu));
            while (!fin.eof())
            {
                if(stu.rollno != n)
                {
                    fout.write((char*)&stu , sizeof(stu));
                }else{
                    found = true;
                    news.accept();
                    fout.write((char*)&news , sizeof(news));
                    cout<<"Record updated successfully"<<endl;
                }
                fin.read((char *)&stu, sizeof(stu));
            }
        }
        fin.close();
        fout.close();
        if(!found)
        {
            cout<<"Record not found\n";
        }
        remove("student_data.txt");
        rename("temp.txt","student_data.txt");
    }
};

int main()
{
    database d;
    int ch;
    while(1)
    {
        cout<<"1.Insert 2.Update 3.Delete 4.Display\n";
        cout<<"Enter choice :";
        cin>>ch;

        switch(ch)
        {
            case 1:
            d.insert();
            break;

            case 2:
            d.update_student();
            break;

            case 3:
            d.remove_student();
            break;

            case 4:
            d.display();
            break;

            default:exit(0);
        }
    }
}
