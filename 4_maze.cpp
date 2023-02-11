#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <stack>

class CreateMatrix{
    public:
        CreateMatrix();
        void init();
        void generate_matrix();
        void setSizeLin(int size);
        void setSizeCol(int size);
        int getSizeLin(){return sizeLin;};
        int getsizeCol(){return sizeCol;};
        void setSeed(int seed);
        void getNeighbors(CreateMatrix smth);
        void Delete(int i, CreateMatrix smth);
        void Delete_dots();
        void dfs();
        void Select_random();
        void Print(); 
        std::vector<std::vector<std::string>> getMaze(){return matrix;};
        int x,y,vis;
    private:
        int sizeLin,sizeCol,seedimp,nr=0;
        std::vector<std::vector<std::string>>matrix;
        std::vector<CreateMatrix>rnd;
        std::vector<CreateMatrix>neighbours;
};


CreateMatrix::CreateMatrix(){}

void CreateMatrix::Select_random(){}

void CreateMatrix::setSeed(int seed){
    seedimp=seed;
    nr++;
}

void CreateMatrix::setSizeLin(int size){
    sizeLin=size;
}

void CreateMatrix::setSizeCol(int size){
    sizeCol=size;
}

void CreateMatrix::init()
{
    rnd.resize(sizeLin*sizeCol);
    matrix.resize(sizeLin*2+1);
    int i;
   for(i=0;i<sizeLin*2+1;i++)
        matrix.at(i).resize(sizeCol*2+1);
    
}

void CreateMatrix::generate_matrix(){

    int i,j,k=0;
    for(i=1;i<=sizeLin*2-1;i=i+2)
        for(j=1;j<=sizeCol*2-1;j=j+2){
            rnd.at(k).x=i;
            rnd.at(k).y=j;
            k++;
            matrix.at(i).at(j)="  ";
            matrix.at(i-1).at(j-1)=matrix.at(i-1).at(j+1)=matrix.at(i+1).at(j+1)=matrix.at(i+1).at(j-1)="+";
            matrix.at(i-1).at(j)=matrix.at(i+1).at(j)="---";
            if(j-1==0)
                matrix.at(i).at(j-1)="|";
            else
                matrix.at(i).at(j-1)=matrix.at(i).at(j+1)=" |";
        }

}

void CreateMatrix::getNeighbors(CreateMatrix nextCoord){
    std::vector<int>lin={-2,0,2,0};
    std::vector<int>col={0,2,0,-2};
    neighbours.resize(0);
    CreateMatrix coords;
    for(int i=0;i<4;i++){
        coords.x=nextCoord.x+lin.at(i);
        coords.y=nextCoord.y+col.at(i);
        if(coords.x>=1&&coords.x<=sizeLin*2-1&&coords.y>=1&&coords.y<=sizeCol*2-1&&matrix.at(coords.x).at(coords.y)=="  ")
            neighbours.push_back(coords);
    }
}

void CreateMatrix::Delete(int i, CreateMatrix rempos){

            if(neighbours.at(i).y==rempos.y&&neighbours.at(i).x<rempos.x)
                matrix.at(rempos.x-1).at(rempos.y)="   ";
            else
            if(neighbours.at(i).y>rempos.y&&neighbours.at(i).x==rempos.x)
                 matrix.at(rempos.x).at(rempos.y+1)="  ";
            else
            if(neighbours.at(i).y==rempos.y&&neighbours.at(i).x>rempos.x)
                 matrix.at(rempos.x+1).at(rempos.y)="   ";
            else
            if(neighbours.at(i).y<rempos.y&&neighbours.at(i).x==rempos.x)
                matrix.at(rempos.x).at(rempos.y-1)="  ";

}

void CreateMatrix::dfs(){

    std::stack<CreateMatrix>thestack;

    if(nr==1){
        srand(seedimp);
    }
    else
        srand(time(NULL));
    int lamisto=rand() % rnd.size();

    CreateMatrix curr;

    curr=rnd.at(lamisto);

   thestack.push(curr);

   matrix.at(curr.x).at(curr.y)=" .";

   while(!thestack.empty()){

        curr=thestack.top();

        thestack.pop();

        getNeighbors(curr);

        if(neighbours.size()>0){

            thestack.push(curr);
           int random = rand() % neighbours.size();

           Delete(random,curr);

           curr=neighbours.at(random);

            matrix.at(curr.x).at(curr.y)=" .";

            thestack.push(curr);
        }
   }

}

void CreateMatrix::Delete_dots(){
    int i,j;
    for(i=1;i<=sizeLin*2-1;i=i+2)
        for(j=1;j<=sizeCol*2-1;j=j+2)
            matrix.at(i).at(j)="  ";
}

void CreateMatrix::Print(){
    int i,j;
    for(i=0;i<sizeLin*2+1;i++){
        for(j=0;j<sizeCol*2+1;j++)
            std::cout<<matrix.at(i).at(j);
        std::cout<<std::endl;
    }
}


class Path{
    public:
        Path();
        void findNeighbours(Path nextCoord);
        void Print(); 
        void copMaze(std::vector<std::vector<std::string>> obj, int sizeline, int sizecolumn);
        bool findPath(Path start, Path end);
        void setStartEnd();
        bool CheckWall(Path currCoord, Path nextCoord);  
        int line,col;
    private:
        int sizeLine,sizeColm;
        CreateMatrix size;
       
        std::vector<std::vector<std::string>>maze;
       std::vector<Path>neighbours;
};

Path::Path(){}

void Path::copMaze(std::vector<std::vector<std::string>> obj, int sizeline, int sizecolumn){
    maze=obj;
    sizeLine=sizeline;
    sizeColm=sizecolumn;
}

bool Path::CheckWall(Path currCoord, Path nextCoord){

    if (nextCoord.col>currCoord.col&&nextCoord.line==currCoord.line&&maze.at(currCoord.line).at(currCoord.col+1)=="  ")
                 return true;
        if (nextCoord.col==currCoord.col&&nextCoord.line>currCoord.line&&maze.at(currCoord.line+1).at(currCoord.col)=="   ")
                return true;
        if (nextCoord.col==currCoord.col&&nextCoord.line<currCoord.line&&maze.at(currCoord.line-1).at(currCoord.col)=="   ")
                return true;
        if (nextCoord.col<currCoord.col&&nextCoord.line==currCoord.line&& maze.at(currCoord.line).at(currCoord.col-1)=="  ")
                return true;
        return false;
               
}
void Path::findNeighbours(Path nextCoord){
     std::vector<int>lin={0,2,0,-2};
    std::vector<int>colm={2,0,-2,0};
    neighbours.clear();
    Path coords;
    for(int i=0;i<4;i++){
        coords.line=nextCoord.line+lin.at(i);
        coords.col=nextCoord.col+colm.at(i);
        if(coords.line>=1&&coords.line<=sizeLine*2-1&&coords.col>=1&&coords.col<=sizeColm*2-1&&CheckWall(nextCoord,coords)){
            neighbours.push_back(coords);
        }
    }
}

bool Path::findPath(Path start, Path end){

   maze.at(start.line).at(start.col)=" .";
    if(start.line==end.line&&start.col==end.col)
        return true;
    else{
    findNeighbours(start);
    for(int i=0;i<neighbours.size();i++){
        if(maze.at(neighbours.at(i).line).at(neighbours.at(i).col)!=" ."){ 
            maze.at(neighbours.at(i).line).at(neighbours.at(i).col)=" .";
            start.line=neighbours.at(i).line;
            start.col=neighbours.at(i).col;
            if(findPath(neighbours.at(i),end))
                return true;
           //else
            //maze.at(start.line).at(start.col)="  ";
                
        }
    }
     maze.at(start.line).at(start.col)="  ";
    } 
   
    return false;
}

void Path::Print(){
    int i,j;
    for(i=0;i<sizeLine*2+1;i++){
        for(j=0;j<sizeColm*2+1;j++)
            std::cout<<maze.at(i).at(j);
        std::cout<<std::endl;
    }
}


int main(int argc, char *argv[])
{
    try{
        if(argc!=3&&argc!=4)
               throw std::runtime_error("invalid parameter list");
   CreateMatrix obj1;
   
   std::string size1=argv[1];

    std::string size2=argv[2];

    if(argc==4){
        std::string strseed=argv[3];
        int seed=atoi(strseed.c_str());
        obj1.setSeed(seed);
    }



    int sizelin=atoi(size1.c_str());

    int sizecol=atoi(size2.c_str());

    Path start,end;
    start.line=start.col=1;
    end.line=sizelin*2-1;
    end.col=sizecol*2-1;

    Path obj2;
    CreateMatrix();
    obj1.setSizeLin(sizelin);
    obj1.setSizeCol(sizecol);
    obj1.init();
    obj1.generate_matrix();
    obj1.dfs();
    obj1.Delete_dots();
    Path();
    obj2.copMaze(obj1.getMaze(),obj1.getSizeLin(),obj1.getsizeCol());
 obj2.findPath(start,end);
     obj2.Print();
    }
    catch(std::runtime_error& excpt){
        std::cout<<excpt.what(); 
    }

}