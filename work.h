#pragma once


#include "print.h"
#include "variable.h"
#include "read.h"
using namespace std;

int standhere;

void robotchange(int h,int yy){
    if(h==yy)return ;
    int uu=16+h*5,vv=16+yy*5;
    for(int i=0;i<=9;i++)
        for(int j=0;j<5;j++){
            mapp[1+i][vv+j]=mapp[1+i][uu+j];
            mapp[1+i][uu+j]=' ';
        }
    return ;
}
bool work(){
    standhere=0;len1=n1;len2=0;nownum=A;
    for(int i=0;i<spac;i++)empt[i]=A;

    for(int i=1;i<=lines;i++){
        if(omo==1)system("pause");
        if(check(i)==0){cout<<"Error on instruction "<<i<<endl;return 0;}
        stringstream str(users[i]);
        str >> instruction;
        str >> num;
        if(instruction=="inbox"){
            if(len1==0)return 1;
            nownum=orig[1];
            for(int j=1;j<len1;j++)orig[j]=orig[j+1];
            len1--;
            if(spac==0){robotchange(standhere,-1);standhere=-1;}
            else{robotchange(standhere,0);standhere=0;}
            mapp[2][17+standhere*5]=mapp[2][7];
            mapp[2][18+standhere*5]=mapp[2][8];
            mapp[2][19+standhere*5]=mapp[2][9];
            for(int j=1;j<=len1;j++)
                for(int op=0;op<3;op++)
                    mapp[j*3-1][7+op]=mapp[j*3+2][7+op];
                    
            mapp[len1*3+2][7]=mapp[len1*3+2][9]=' ';
            mapp[len1*3+2][8]='X';
            print(i);
            continue;
        }
        if(instruction=="outbox"){
            len2++;
            for(int j=len2;j>1;j--)subs[j]=subs[j-1];
            subs[1]=nownum;
            nownum=A;
            if(spac==0){robotchange(standhere,1);standhere=1;}
            else{robotchange(standhere,spac-1);standhere=spac-1;}
            for(int j=len2-1;j>=1;j--)
                for(int op=0;op<3;op++)
                    mapp[j*3+2][max(spac,1)*5+30-8+op]=mapp[j*3-1][max(spac,1)*5+30-8+op];
            mapp[2][max(spac,1)*5+30-8]=mapp[2][17+standhere*5];
            mapp[2][max(spac,1)*5+30-7]=mapp[2][18+standhere*5];
            mapp[2][max(spac,1)*5+30-6]=mapp[2][19+standhere*5];
            mapp[2][17+standhere*5]=' ';
            mapp[2][18+standhere*5]='X';
            mapp[2][19+standhere*5]=' ';
            print(i);
            continue;
        }
        if(instruction=="add"){
            nownum+=empt[num];
            if(nownum>=100||nownum<=-100){cout<<"Are you sure you're thinking in the right direction?"<<endl;return 0;}
            int jkl=nownum;
            robotchange(standhere,num);standhere=num;
            if(jkl<0){mapp[2][17+standhere*5]='-';jkl=-jkl;}
            else mapp[2][17+standhere*5]=' ';
            if(jkl>=10)mapp[2][18+standhere*5]=char((jkl/10)+'0'),mapp[2][19+standhere*5]=char((jkl%10)+'0');
            else mapp[2][18+standhere*5]=char(jkl+'0'),mapp[2][19+standhere*5]=' ';
            print(i);
            continue;
        }
        if(instruction=="sub"){
            nownum-=empt[num];
            if(nownum>=100||nownum<=-100){cout<<"Are you sure you're thinking in the right direction?"<<endl;return 0;}
            int jkl=nownum;
            robotchange(standhere,num);standhere=num;
            if(jkl<0){mapp[2][17+standhere*5]='-';jkl=-jkl;}
            else mapp[2][17+standhere*5]=' ';
            if(jkl>=10)mapp[2][18+standhere*5]=char((jkl/10)+'0'),mapp[2][19+standhere*5]=char((jkl%10)+'0');
            else mapp[2][18+standhere*5]=char(jkl+'0'),mapp[2][19+standhere*5]=' ';
            print(i);
            continue;
        }
        if(instruction=="copyto"){
            empt[num]=nownum;
            robotchange(standhere,num);standhere=num;
            mapp[12][17+num*5]=mapp[2][17+standhere*5];
            mapp[12][18+num*5]=mapp[2][18+standhere*5];
            mapp[12][19+num*5]=mapp[2][19+standhere*5];
            print(i);
            continue;
        }
        if(instruction=="copyfrom"){
            nownum=empt[num];
            robotchange(standhere,num);standhere=num;
            mapp[2][17+standhere*5]=mapp[12][17+num*5];
            mapp[2][18+standhere*5]=mapp[12][18+num*5];
            mapp[2][19+standhere*5]=mapp[12][19+num*5];
            print(i);
            continue;
        }
        if(instruction=="jump"){
            print(i);
            i=num-1;
            continue;
        }
        if(instruction=="jumpifzero"){
            print(i);
            if(nownum==0)i=num-1;
        }
    }
    return 1;
}
void sus(int p){
    bool okk=1;
    if(len2==n2){
        for(int i=1;i<=len2;i++)
            if(subs[i]!=targ[len2+1-i])
                okk=0;
    }
    else okk=0;
    if(okk==0){
        cout<<"Fail"<<endl;
        cout<<"Oh,GOD! I'm sorry you didn't pass this level"<<endl;
    }
    else{
        cout<<"Success"<<endl;
        cout<<"Congratulations, you have passed this level"<<endl;
        ofstream fout(task[0]);
        for(int i=1;i<=p;i++)fout<<"yes"<<endl;
        for(int i=p+1;i<=4;i++)fout<<"no"<<endl;
        fout.close();
    }
}