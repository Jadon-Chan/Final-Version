#pragma once

#include "variable.h"

void keyboard(void)
{
    cout << "How many lines you'd like to input?" << endl;
    cin >> lines;getchar();
    for (int i = 1; i <= lines; i++)
    {
        getline(cin,users[i]);
    }
}

void file(void)
{
    cout << "Note that your file should consist of n+1 lines," << endl
         << "the first line is an integer n, meaning you have n pieces of instructions." << endl
         << "the rest n lines are the instructions, only one piece of instruction for one line" << endl;
    cout << "Enter the path of your instruction file:" << endl;
    string path;
    cin >> path;
    ifstream source(path);
    source >> lines;
    for (int i = 0; i <= lines; i++)
    {
       getline(source,users[i]);
    }
}

void read(void)
{
    cout << "In which way you'd like to input instructions?" << endl;
    cout << "a) via keyboard    b) via file" << endl;
    char manner;
    while (1)
    {
        manner=getch();
        cout<<manner<<endl;
        switch (manner)
        {
        case 'a':
            keyboard();
            break;
        case 'b':
            file();
            break;
        default:
            cout << "No such an option, please choose between a and b!" << endl;
            continue;
        }
        break;
    }
    cout << "In which way you'd like to show the operation process?" << endl;
    cout << "a) one move at a time    b) all in one step"<<endl;
    while (1)
    {
        manner=getch();
        cout<<manner<<endl;
        switch (manner)
        {
        case 'a':
            omo=1;
            break;
        case 'b':
            omo=0;
            break;
        default:
            cout << "No such an option, please choose between a and b!" << endl;
            continue;
        }
        break;
    }
}
bool isint(char *operand)
{
    for (int i = 0; i < strlen(operand); i++)
    {
        if (operand[i] < '0' || operand[i] > '9')
            return 0;
    }
    return 1;
}
bool check(int i)
{
    char op[100];
    char operand[100];
    stringstream s(users[i]);
    s >> op >> operand;
    string temp = op;
    int situ=-1;
    string sets[] = {"inbox", "outbox", "add", "sub", "copyto", "copyfrom", "jump", "jumpifzero"};
    for (int i = 0; i < 8; i++)
    {
        if (temp == sets[i])
        {
            situ = i;
            break;
        }
    }
    if(situ==-1)return 0;
    bool popo=0;
    for (int i = 1; i<= useable ; i++)
    {
        if(sets[situ]==instr[i])
            popo=1;
    }
    if(popo==0)return 0;
    switch(situ)
    {
    case 0:{
        if (s.tellp() == 0)
            return 0;
        break;
            }
    case 1:{
        if (s.tellp() == 0)
            return 0;
        // how to judge now nownum
        if (nownum == A)
            return 0;
        break;
            }
    case 2:
    case 3:{
        // how to judge field x
        if (s.tellp() != 0)
            return 0;
        s >> op;
        if (s.tellp() == 0)
            return 0;
        if (!isint(operand))
            return 0;
        string temp = operand;
        if (stoi(temp) >= spac || stoi(temp) < 0 || empt[stoi(temp)] == A)
            return 0;
        break;
            }
    case 4:{
        if (s.tellp() != 0)
            return 0;
        s >> op;
        if (s.tellp() == 0)
            return 0;
        if (!isint(operand))
            return 0;
        string temp = operand;
        if (stoi(temp) >= spac || stoi(temp) < 0)
            return 0;
        if (nownum == A)
            return 0;
        break;
            }
    case 5:{
        if (s.tellp() != 0)
            return 0;
        s >> op;
        if (s.tellp() == 0)
            return 0;
        if (!isint(operand))
            return 0;
        string temp = operand;
        if (stoi(temp) >= spac || stoi(temp) < 0 || empt[stoi(temp)] == A)
            return 0;
        break;
            }
    case 6:
    case 7:{
        if (s.tellp() != 0)
            return 0;
        s >> op;
        if (s.tellp() == 0)
            return 0;
        string temp = operand;
        if (stoi(temp)==0||stoi(temp)>lines)
            return 0;
        if (situ == 7 && nownum == A)
            return 0;
        break;
            }
    default:{return 0;}
    }
    return 1;
}