#include<iostream>
#include<deque>
#include<vector>
#include<conio.h>
#include<time.h>
using namespace std;

class player{
    public:
    int x,y;
    player(int width){
        x=width/2;
        y=0;
    }
};
class lane{
    private:
    deque<bool>cars;
    bool right;
    public:
    lane(int width){
        for(int i=0;i<width;i++){
            cars.push_front(true);
        }
        right=rand()%2;
    }
    void move(){
        if(right){
        if(rand()%10==1)cars.push_back(true);
        else cars.push_back(false);
        cars.pop_front();
        }
        else{
             if(rand()%10==1)cars.push_front(true);
        else cars.push_front(false);
        cars.pop_back();
        }
    }
    bool checkpos(int pos){
        return cars[pos];
    }
    void changedirection(){ right!=right;}
    };
class game{
   private:
   bool quit;
   int numberoflanes;
   int width;
   int score;
   player *player1;
   vector<lane*>map;
   public:
   game(int w=20,int h=5){
    numberoflanes=h;
    width=w;
    score=0;
    quit=false;
    for(int i=0;i<numberoflanes;i++)
      map.push_back(new lane(width));
      player1=new player(width);
   }
   void draw(){
        system("cls");
       
      
        for(int i=0;i<numberoflanes;i++){
           for(int j=0;j<width;j++){
            if(j==0||j==width-1)cout<<"|";
            if(map[i]->checkpos(j)&&i!=0&&i!=numberoflanes-1)cout<<"#";
            else if(player1->x==j&&player1->y==i)cout<<"V";
            else cout<<" ";
           }
            cout<<endl;
        }
   }
   void input(){
     if(_kbhit()){
        char current=_getch();
        if(current=='a')player1->x--;
        if(current=='d')player1->x++;
        if(current=='w')player1->y--;
        if(current=='s')player1->y++;
        if(current=='q')quit=true;
     }

   }
   void logic(){
       for(int i=1;i<numberoflanes-1;i++){
        if(rand()%10==1)map[i]->move();
        if(map[i]->checkpos(player1->x)&&player1->y==i)quit=true;
        if(player1->y==numberoflanes-1){
            score++;
            player1->y=0;
            cout<<"\x07";
            map[rand()%numberoflanes]->changedirection();
       }}
       cout<<"Score :"<<score<<endl;
   }
   void run(){
    while(!quit){
        input();
        draw();
        logic();
    }}
   
};

int main(){
    srand(time(NULL));
   game game1(30,5);
  game1.run();
    cout<<"Game Over!"<<endl;
 
    getchar();
}