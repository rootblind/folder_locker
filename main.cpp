#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <dirent.h>
#include <conio.h>

using namespace std;

void directories();
void register_path(char path[]);
void lockfolder();
void unlockfolder();
void enc(char text[10000]);
void setpasswd();

int main()

{
 mkdir("file");
 unsigned int choice=0;
 SetConsoleTitle("Folder Lock");
 system("CLS");
 ifstream xDx("file/xDx");
 int verify;
 xDx>>verify;
 xDx.close();
 if(verify != 66)
    {
        setpasswd();
        cin.get();
    }
 ifstream pwd("file/kzhhdw");
 char password[10000];
 pwd.getline(password,9999);
 pwd.close();
 enc(password);
 cout << "=================== Folder Locker - Log in ===================\n";
 char psswd[10000];
 unsigned tries = 0;
 do{cout<<"Passwd: ";cin.get(psswd,9999); cin.get();
    tries++;
    if(tries == 3)
    {
        cout<<"\nToo many tries!\nThe application is going to close!";
        _getch();
        return 0;
    }
 }while(strcmp(psswd,password));
 do{
 system("cls");
 cout << "=================== Folder Locker - Menu ===================\n";
 cout << "\n\n" << "Options:\n";
 cout << "======================\n";
 cout << "1. - Lock Folder.\n";
 cout << "2. - Unlock Folder.\n";
 cout << "3. - Exit.\n";
 cout << "4. - Reset Password.\n";
 cout << "5. - Reset Paths logs.\n";
 cout << "======================  \n";
 directories();


 cout << "\nEnter your choice: ";
 cin >> choice;

 switch (choice)
 {
 case 1: lockfolder(); break;
 case 2: unlockfolder(); break;
 case 3: exit(0); break;
 case 4:
     {
    system("cls");
    cout << "=================== Folder Locker - Resetting the password ===================\n";
    cin.get();
    tries = 0;
    do{cout<<"Passwd: ";cin.get(psswd,9999);cin.get();
    tries++;
    if(tries == 3)
        return 0;
    }while(strcmp(psswd,password));
    ofstream f("file/xDx");
    cout<<"\nReseted successfully!\nNow the application is going to close!";
    f<<0;
    f.close();
    _getch();
    return 0;
     }
     break;
 case 5:
    {
        ofstream f("file/paths");
        f.close();
        cout<<"\nPath logs cleaned!";
        _getch();
    }
    break;
 default: cout << "\nError. Unknown Option Entered. Quitting ....\n";
 _getch();
 return 0;
 break;
 }
 }while(1);

 return 0;
}

void enc(char text[])
{
    char text_dec[10000] = "";
    int i = 0;
    for(i = 0; i < strlen(text); i++)
        if(text[i] >= 'A' && text[i] <= 'Z')
            text_dec[i] = 'Z' - text[i] + 'A';
        else if(text[i] >= 'a' && text[i] <= 'z')
            text_dec[i] = 'z' - text[i] + 'a';
            else if(text[i] >= '0' && text[i] <= '9')
                    text_dec[i] = '9' - text[i] + '0';
            else if(text[i] == ' ')
                text_dec[i] = '.';
                else if(text[i] == '.')
                    text_dec[i] = ' ';
            else
                text_dec[i] = text[i];
    text_dec[i] = NULL;
    strcpy(text,text_dec);
}
void directories()
{
    cout<<"P A T H    L O G S:";
    ifstream dir("file/paths");
    char print[200];
    while(dir.getline(print,sizeof(print)))
        cout<<"\n"<<print;
    cout<<endl;
    dir.close();
}
void register_path(char path[])
{
    fstream p("file/paths",ios::app);
    ifstream pc("file/paths");
    bool exists = false;
    char check_paths[200];
    while(pc.getline(check_paths,sizeof(check_paths)) && !exists)
        if(strcmp(path,check_paths) == 0)
            exists = true;

    if(!exists)
        p<<path<<'\n';
    p.close();
    pc.close();
}

void setpasswd()
{
    system("cls");
    cout << "=================== Folder Locker - Setting Password ===================\n";
    char select;
    ofstream login("file\\kzhhdw");
    ofstream xDx("file\\xDx");
    char passwd[10000];
    do{
    cout<<"Password: ";cin>>passwd;
    cout<<"\nAre you sure your password is "<<passwd<<" ?";
    do{cout<<"\n[y/n]: ";cin>>select;}while(tolower(select) != 'n' && tolower(select) != 'y');
    }while(tolower(select) == 'n');
    enc(passwd);
    login<<passwd;
    system("cls");
    xDx<<66;
    xDx.close();
    login.close();

}

void lockfolder()
{
 char pass[15]="";
 ofstream lfolder;
 char folder[200]={0};
 char tempfolder[200]={'0'};
 char attributes[50]={'0'};

 system("cls");
 cout << "=================== Folder Locker ===================\n";
  directories();
 cout << "\nEnter the complete path to the Folder(spaces are not allowed): ";
 cin >> folder;

 strcpy(tempfolder, folder);

 strcat(folder, "\\Desktop.ini");

 lfolder.open(folder, ios::out);

 lfolder << "[.shellClassInfo]" << endl;
 lfolder << "CLSID = {63E23168-BFF7-4E87-A246-EF024425E4EC}" << endl;

 lfolder.close();

 strcpy(attributes, "attrib +h +s ");
 strcat(attributes, tempfolder);

 WinExec(attributes, NULL);

 lfolder.open("C:\\windows\\db.dat", ios::app);
 lfolder << "Folder Locked: " << tempfolder << endl;
 register_path(tempfolder);
 lfolder.close();

 cout << "\n\n" << tempfolder << " has been locked successfully!\n";
 _getch();
}

void unlockfolder()
{
 char folder[255];
 char tempfolder[255];
 char attributes[50];
 char del[50];
 ofstream lfolder;

 system("cls");
 cout << "=================== Folder Unlocker ===================\n";
  directories();
 cout << "\nEnter the complete path to the Folder(spaces are not allowed): ";
 cin >> folder;

 strcpy(tempfolder, folder);
 strcat(folder, "\\Desktop.ini");

 strcpy(del, "del ");
 strcat(del, folder);
 system(del);

 strcpy(attributes, "attrib -h -s ");
 strcat(attributes, tempfolder);

 WinExec(attributes, NULL);

 lfolder.open("C:\\windows\\db.dat", ios::app);
 lfolder << "! Folder Unlocked: " << tempfolder << endl;
 register_path(tempfolder);
 lfolder.close();

 cout << "\n\n" << tempfolder << " has been unlocked successfully!\n";
 _getch();

}
