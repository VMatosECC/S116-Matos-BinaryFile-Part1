// S116-Matos-Binary-Files-Part1

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//Structures ----------------------------------------------
struct Person {
    int     id;
    char    name[30];       //instead of modern string name
    int     age;
    char    data[10];

    void print() {
        cout << "ID: " << id
            << ", Age: " << age
            << ", Data: " << data
            << ", Name: " << name
            << endl;
    }

};


//Prototypes ----------------------------------------------
void experiment01();
void experiment02();
void experiment03();

int main()
{
    experiment01();
    experiment02();
    cout << "\nAll done!\n";
}
void experiment02()
{
    //Read and show the binary file
    fstream binFile("c:/temp/springfieldPeople.bin", ios::in | ios::out| ios::binary);

    Person p;
    while (binFile.read( (char*)(& p), sizeof(p)) ) {
        p.print();
    }

    //How many records are there?
    binFile.clear();
    binFile.seekg(0, ios::end);
    cout << "Current byte position: " << binFile.tellg() << endl;
    int numRec = binFile.tellg() / sizeof(p);
    cout << "Number of records in the binary file: " << numRec << endl;

    //Add new record to file.
    binFile.clear();
    binFile.seekp(0, ios::end);
    Person pnew;
    pnew.id = 555;
    pnew.age = 33;
    //pnew.name = "Jimbo Jones";
    strcpy_s(pnew.name, "Jimbo Jones");
    strcpy_s(pnew.data, "data555");

    binFile.write((char*)(&pnew), sizeof(p));
    binFile.close();
    cout << "New record added \n";
    pnew.print();
}




//User-Defined Methods -------------------------------------
void experiment01()
{
    //Read csv file create memory resident database
    //also create a binary file image
    fstream infile("c:/temp/springfieldPeople.txt", ios::in);
    if (!infile) {
        cout << "Fatal error - file not found\n";
        exit(1);
    }

    vector<Person> db;
    fstream binFile("c:/temp/springfieldPeople.bin", ios::out | ios::binary);

    string strId, strName, strAge, strData;
    while (getline(infile, strId, ',')) {
        getline(infile, strName, ',');
        getline(infile, strAge, ',');
        getline(infile, strData);
        Person p;
        p.id = stoi(strId);
        //p.name = strName;
        strcpy_s(p.name, strName.c_str());
        p.age = stoi(strAge);
        //p.data = strData;
        strcpy_s(p.data, strData.c_str());

        db.push_back(p);        //Add person to memory database
        binFile.write((char*)(& p), sizeof(p));  


    }
    cout << "Memory resident database created\n";
    cout << "Binary file created\n";
    infile.close();
    binFile.close();
}