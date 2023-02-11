#include <iostream>
#include <vector>

void deduplicate(std::vector<int>&v)
{
    int i,j,t,n;
    for(i=0;i<v.size()-1;i++)
        for(j=i+1;j<v.size();j++)
            if(v.at(i)==v.at(j)){
                for(t=j;t<v.size()-1;t++)
                    v.at(t)=v.at(t+1);
                n=v.size();
                v.resize(n-1);
                j--;
            }
}

int main()
{
    int i;
    std::vector<int> v;
    std::cout<<"Enter the vector elements: "<<std::endl;
    while (std::cin>>i)
        v.push_back(i);
    deduplicate(v);
    std::cout<<"The deduplicated vector is: [";
    for(i=0;i<v.size()-1;i++)
        std::cout<<v.at(i)<<",";
    std::cout<<v.at(i)<<"]";

}