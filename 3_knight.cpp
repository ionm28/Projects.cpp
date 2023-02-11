#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdexcept>


class position{
    public:
        int l,c;
};


int l_poz(std::string argm)
{
    int i;
    if(argm.size() > 2){
        std::string arg;
        arg.push_back(argm.at(1));
        arg.push_back(argm.at(2));
        i=atoi(arg.c_str());
    }
    else
        i=argm.at(1)-'0';
   return i;
}

int c_poz(std::string argm)
{
    int j;
    j=argm.at(0)-97+1;
    return j;
}

int verif(int k, std::vector<std::vector<int>>&matrix, std::vector<position>&poz, int size2)
{
     
     if(poz.at(k).l>=1&&poz.at(k).l<=size2&&poz.at(k).c>=1&&poz.at(k).c<=size2&&matrix.at(poz.at(k).l).at(poz.at(k).c)==-1){
        return 1;
     }
    return 0;
}

bool findKnightsTour (std::vector<std::vector<int>>&matrix, int k, std::string end, std::vector<position>&poz, int size2, int posei, int posej, std::vector<position>&adv)
{
    int i;
    std::vector<int>lin={2,1,-1,-2,-2,-1,1,2};
    std::vector<int>col={1,2,2,1,-1,-2,-2,-1};
    if(poz.at(k-1).l==posei&&poz.at(k-1).c==posej)
        return true;
    for(i=0;i<8;i++){
        poz.at(k).l=poz.at(k-1).l+lin.at(i);
         poz.at(k).c=poz.at(k-1).c+col.at(i);
            if(verif(k,matrix,poz,size2)){
                matrix.at(poz.at(k).l).at(poz.at(k).c)=1;
                bool x=findKnightsTour(matrix,k+1,end,poz,size2,posei,posej,adv);
                if(x){
                    adv.push_back(poz.at(k));
                    return true;
                }
               else
                 matrix.at(poz.at(k).l).at(poz.at(k).c)=-1;
            }
    }
    return false;
}

int main(int argc, char *argv[])
{
    try{
        if(argc!=4)
            throw std::runtime_error("invalid parameter list");
    int i,j,l;
    std::string size1=argv[1];
    int size2=atoi(size1.c_str());
    if(size2<1||size2>26)
        throw std::runtime_error("invalid parameter list");
    std::string start;
    std::string end;
    std::vector<std::vector<int>>matrix(size2+1);
    std::vector<position>poz;
    int size=(size2)*(size2);
    poz.resize(size);
    start=argv[2];
    end=argv[3];
    int posei=l_poz(end);
    int posej=c_poz(end);
    int possi=l_poz(start);
    int possj=c_poz(start);
    if(size2<posei||size2<posej||size2<possi||size2<possj)
         throw std::runtime_error("invalid parameter list");
    for(i=0;i<=size2;i++)
        matrix.at(i).resize(size2+1);
    for(i=1;i<=size2;i++)
        for(j=1;j<=size2;j++)
            matrix.at(i).at(j)=-1; 
    poz.at(0).l=l_poz(start);
    poz.at(0).c=c_poz(start);
    matrix.at(poz.at(0).l).at(poz.at(0).c)=0;
    std::string converted;
    char convlet,convnum;
    std::vector<position>adv;
    adv.push_back(poz.at(0));
    if(findKnightsTour(matrix,1,end,poz,size2,posei,posej,adv)){
        std::cout<<start<<" ";
            for(i=adv.size()-1;i>=1;i--){
                convlet=adv.at(i).c+97-1;
                converted.push_back(convlet);
                if(adv.at(i).l>=10){
                    convnum=adv.at(i).l/10+'0';
                    converted.push_back(convnum);
                    convnum=adv.at(i).l%10+'0';
                    converted.push_back(convnum);
                }
                else{
                    convnum=adv.at(i).l+'0';
                    converted.push_back(convnum);
                }
                converted.push_back(' ');
            }
    std::cout<<converted;
    }
    else
        std::cout<<"could not find a knight's tour";
    }
    catch(std::runtime_error& excpt){
        std::cout<<excpt.what(); 
    }
    return 0;   
}