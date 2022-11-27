#include<iostream>
#include<fstream>
#include<curses.h>
//#include<windows>
//#include<process>
#include <unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


char lmap1[30][54];
char lmap2[30][54];
int pc=0;
char yn='y';
char16_t w = u'ሰ';
long score;
int power=0;
int ptime=21;
int gtype;
char name[50];

using namespace std;

class entity
{
     public:
       int x,y;
       char sym;
       char dir;
       int gt;
       char emove(char mapl[30][54],char dir)
         {
            if(dir=='w')
            {
                if(mapl[x-1][y]!=w)
               {
                  x--;
                  return 'w';
               }
             else return ' ';
            }
            else if(dir=='s')
            {
              if(mapl[x+1][y]!=w)
                {
                   x++;
                   return 's';
                }
              else return ' ';
            }
            else if(dir=='a')
            {
             if(mapl[x][y-2]!=w)
               {
                  y-=2;
                  return 'a';
               }
             else return ' ';
            }
            else
            {
             if(mapl[x][y+2]!=w)
               {
                  y+=2;
                  return 'd';
               }
             else return ' ';
            }
         }
    
entity(int i,int j,char s)
        {
            x=i;
            y=j;
            sym=s;
        }
       int pc(char dir,char mapl[30][54],int pc)
        {
          if(mapl[x][y]=='-'||mapl[x][y]=='+')
          {
           if(lmap2[x][y]=='+')
              {
                  lmap2[x][y]=' ';
                  score+=500;
                  pc++;
                  power=1;
                  ptime--;
              }
           else
             {
                 lmap2[x][y]=' ';
                 pc++;
                 score+=250;
             }
          }
          return pc;
        }
       void portal()
        {
          if((x==14&&y==0)||(x==14&&y==52))
           {
            y=52-y;
           }
        }

};

entity pm(17,26,'>');
entity camoghost(15,26,'M');

void levelmap()
{
  {
    ifstream fin;
    fin.open("MAP.txt",ios::in);
    if(!fin)
      cout<<"Error";
      for(int i=0;i<30;i++)
        {
          for(int j=0;j<54;j++)
          fin.get(lmap1[i][j]);
        }
      fin.close();
  }
      for(int i=0;i<30;i++)
      {
          for(int j=0;j<54;j++)
            {
                if(lmap1[i][j]=='O')
                    lmap1[i][j]=w;
                lmap2[i][j]=lmap1[i][j];
            }
      }
}


void printmap(int lives)
{
         cout<<"PAC MAN\n";

    for(int i=0;i<30;i++)
    {
        for(int j=0;j<54;j++)
            {
               if(pm.x==i&&pm.y==j)
                    cout<<pm.sym;
               else if(camoghost.x==i&&camoghost.y==j)
                    cout<<camoghost.sym;
               else cout<<lmap2[i][j];
            }
    }
    cout<<'\n'<<"LIVES:"<<lives;
    cout<<'\n'<<"SCORE:"<<score;
}
char dir[7]={'w','a','d','w','a','d','s'};

void ghostmove(entity& g)
{
    int i=std::rand()%7;
    switch (g.dir)
    {
        case('w'): g.dir=g.emove(lmap2,'w');
                   break;
        case('a'): g.dir=g.emove(lmap2,'a');
                   break;
        case('s'): g.dir=g.emove(lmap2,'s');
                   break;
        case('d'): g.dir=g.emove(lmap2,'d');
                   break;
        default:   g.dir=dir[i];
                   break;

    }


}

void centerstring(string s)
{
    int l=strlen(s);
    int pos=(80-l)/2;
    for(int i=0;i<pos;i++)
        cout<<" ";
    cout<<s;
}

int deathcheck(int lives, entity& ghost, int power)
{
    if(power==0)
    {
        if(pm.x==ghost.x&&pm.y==ghost.y)
      {
         lives--;
         if(lives==0)
          {
             system("CLS");
             //high_score(score);
             cout<<"\n";
             centerstring("GAME OVER\n");
             exit(0);
          }
         pm.y--;
         printmap(lives);
         sleep(5000);
         pm.x=17;
         pm.y=26;
         ghost.x=15;
         ghost.y=26;
         ghost.dir='w';
      }
     return lives;
    }
    else
    {
        if(pm.x==ghost.x&&pm.y==ghost.y)
        {
            printmap(lives);
            score+=1000;
            sleep(5000);
            ghost.x=15;
            ghost.y=26;
            pm.x=17;
            pm.y=26;
            ghost.dir='w';
        }
      return lives;
    }
}

int main()
{
  char ch;
  int lives=3;
  int t=0;
  int n;
  do
  {
  system("CLS");
  cout<<"\n\n\n\n";
  centerstring("PAC-MAN : CHASE");
  cout<<"\n\n\n";
  centerstring("1. PLAY GAME\n");
  centerstring("2. HIGH SCORE\n");
  centerstring("3. EXIT GAME\n");
  cin>>n;
  system("CLS");

    switch(n)
        {
            case 1:
                {
                    cout<<"Enter your name:";
                    cin>>name;
                    system("CLS");
                    centerstring("INSTRUCTIONS");
                    cout<<"\n\n";
                    centerstring("You're objective is to get the highest score.\n");
                    centerstring("All [-] pellets give you 250 points.\n");
                    centerstring("All [+] power pellets give you 500 points.\n");
                    centerstring("Each time you hit the ghost within the next 15 seconds you get an additional 1000 points.\n");
                    centerstring("BEWARE!! If you hit a ghost without having consumed a power pellet you will lose one of your three precious lives.\n");
                    centerstring("You also have only about 4 minutes to rack up your points, so plan carefully beforehand.\n");
                    centerstring("HOPE YOU ENJOY[:)]\n\n");
                    centerstring("Press any key to continue:");
                    getch();
                    system("CLS");
                    centerstring("PAC-MAN CHASE\n");
                    centerstring("Enter Level\n");
                    centerstring("1.Normal\n");
                    centerstring("2.Camouflage\n");

                    cin>>gtype;
                    changegtype(camoghost);

                    camoghost.dir='w';
                    levelmap();
                    getch();

                    while(t<360)
                    {
                        system("CLS");

                        if(getch())
                            ch=getch();
                        switch(ch)
                        {
                            case 'w':{
                                        if(pm.x%2==0)
                                        pm.sym='V';
                                        else pm.sym='|';
                                        pc=pm.pc('w',lmap2,pc);
                                        ch=pm.emove(lmap2,'w');
                                        lives=deathcheck(lives,camoghost,power);
                                        break;
                                    }

                            case 's':{
                                        if(pm.x%2==0)
                                        pm.sym='A';
                                        else pm.sym='|';
                                        pc=pm.pc('s',lmap2,pc);
                                        ch=pm.emove(lmap2,'s');
                                        lives=deathcheck(lives,camoghost,power);
                                        break;
                                    }
                            case 'a':{
                                        if(pm.y%4==0)
                                        pm.sym='>';
                                        else pm.sym='=';
                                        pc=pm.pc('a',lmap2,pc);
                                        ch=pm.emove(lmap2,'a');
                                        pm.portal();
                                        lives=deathcheck(lives,camoghost,power);
                                        break;
                                    }

                            case 'd':{
                                        if(pm.y%4==0)
                                        pm.sym='<';
                                        else pm.sym='=';
                                        pc=pm.pc('d',lmap2,pc);
                                        ch=pm.emove(lmap2,'d');
                                        pm.portal();
                                        lives=deathcheck(lives,camoghost,power);
                                        break;
                                    }

                            default:ch=' ';
                        }
                        if(t>10)
                            ghostmove(camoghost);
                        printmap(lives);
                        t++;
                        if(ptime<21&&ptime>0)
                            {
                                ptime--;
                                camoghost.sym='!';
                            }
                        else if (ptime==0)
                            {
                                if(gtype==1)
                                    camoghost.sym='G';
                                else camoghost.sym='~';
                                ptime=21;
                                power=0;
                            }
                        else ptime=21;
                        Sleep(250);
                        }

                    getch();
                    break;
                }
            case 2:
                {
                    high_score(score);
                    break;
                }
            case 3:
                {
                    exit(0);
                }
        }
        centerstring("Do you want to continue ?(y/n)");
        cin>>yn;
  }while(yn=='y');
  return 0;
}
