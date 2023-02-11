#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void uncap(std::string &text)
{
    int i;
    for(i=0;i<text.size();i++)
        if(text.at(i)>='A'&&text.at(i)<='Z')
            text.at(i)=text.at(i)+32;
}

void frc(std::string text, std::vector<int>&frcv)
{
    int i;
    for(i=0;i<text.size();i++)
        if(text.at(i)>='a'&&text.at(i)<='z')
            frcv.at(text.at(i))++;

}

int main(int argc, char* argv[])
{
    std::string text;
    
    std::vector<int>frcv;
    int maxv,maxc,i,mostnr;
    char mac,mav,most;
    std::ifstream f;

   for(i=0;i<='z';i++)
        frcv.push_back(0);
        
   if(argc==1){
    while(std::getline(std::cin,text)){
            uncap(text);
            frc(text,frcv);
    }
   }
   else{
    if(argc>2){
    std::cout<<"cannot handle parameter list"<<std::endl;
    return 1;
   }

   f.open(argv[1]);

   if(!f.is_open()){
    std::cout<<"cannot open input file "<<argv[1]<<std::endl;
    return 1;
   }
    while(!f.eof()){
        std::getline(f,text);
        uncap(text);
        frc(text,frcv);
    }
    f.close();
   }
    maxv=maxc=0;
    mav='a';
    mac='b';
    for(i='a';i<='z';i++)
        if(i=='a'||i=='e'||i=='i'||i=='o'||i=='u'){
            if(frcv.at(i)>maxv){
                maxv=frcv.at(i);
                mav=i;
            }
        }
        else
            if(frcv.at(i)>maxc){
                maxc=frcv.at(i);
                mac=i;
            }
    
    if(maxv>maxc){
        mostnr=maxv;
        most=mav;
    }
    else
        if(maxv<maxc){
            mostnr=maxc;
            most=mac;
        }
    else
        if(mac>mav){
            mostnr=maxv;
            most=mav;
        }
        else{
            mostnr=maxc;
            most=mac;
        }

   std::cout<<"Most frequent vowel: "<<mav<<" ("<<maxv<<" times)"<<std::endl;
   std::cout<<"Most frequent consonant: "<<mac<<" ("<<maxc<<" times)"<<std::endl;
   std::cout<<"Most frequent letter, overall: "<<most<<" ("<<mostnr<<" times)"<<std::endl;

}