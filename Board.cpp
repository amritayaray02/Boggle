#include <iostream>
#include <windows.h>
#include <vector>
#include <strings.h>
#include <time.h>
using namespace std;
 
int rollDie()
{
    int roll;
    roll = rand() % 6;
    return roll;
}

int randomrow()
{
    int roll;
    roll = rand() % 5;
    return roll;
}

string shuffle_string()
{   
    char first[6] = {'A','A','A','F','R','S'};
    char second[6] = {'A','E','E','G','M','U'};
    char third[6] = {'C','E','I','I','L','T'};
    char fourth[6] = {'D','H','L','N','O','R'};
    char fifth[6] = {'F','I','P','R','S','Y'};
    char sixth[6] = {'A','A','E','E','E','E'};
    char seventh[6] = {'A','E','G','M','N','N'};
    char eigth[6] = {'C','E','I','L','P','T'};
    char ninth[6] = {'D','H','L','N','O','R'};
    char tenth[6] = {'G','O','R','R','V','W'};
    char eleven[6] = {'A','A','F','I','R','S'};
    char twelve[6] = {'A','F','I','R','S','Y'};
    char thirteen[6] = {'C','E','I','P','S','T'};
    char fourteen[6] = {'E','I','I','I','T','T'};
    char fifteen[6] = {'I','P','R','R','R','Y'};
    char sixteen[6] = {'A','D','E','N','N','N'};
    char seventeen[6] = {'B','J','K','Q','X','Z'};
    char eightteen[6] = {'D','D','H','N','O','T'};
    char nineteen[6] = {'E','M','O','T','T','T'};
    char twenty[6] = {'N','O','O','T','U','W'};
    char twentyone[6] = {'A','E','E','E','E','M'};
    char twentytwo[6] = {'C','C','E','N','S','T'};
    char twentythree[6] = {'D','H','H','L','O','R'};
    char twentyfour[6] = {'E','N','S','S','S','U'};
    char twentyfive[6] = {'O','O','O','T','T','U'};

    srand(time(0));

    char shuffledDie[5][5]={  {first[rollDie()],  second[rollDie()],   third[rollDie()],   fourth[rollDie()],   fifth[rollDie()] },
                        {sixth[rollDie()],  seventh[rollDie()],   eigth[rollDie()],   ninth[rollDie()],   tenth[rollDie()] },
                        {eleven[rollDie()],  twelve[rollDie()],   thirteen[rollDie()],   fourteen[rollDie()],   fifteen[rollDie()] },
                        {sixteen[rollDie()],  seventeen[rollDie()],   eightteen[rollDie()],   nineteen[rollDie()],   twenty[rollDie()] },
                        {twentyone[rollDie()],  twentytwo[rollDie()],   twentythree[rollDie()],  twentyfour[rollDie()],   twentyfive[rollDie()] }  
                     };
    
    string s1 = "";
    for(int i=0; i<5 ; i++)
    {
        for(int j=0; j<5; j++)
        {
            s1+=shuffledDie[i][j];
        }
    }

    char temp = 'a';
    for(int i=0; i<5 ; i++)
    {
        for(int j=0; j<5; j++)
        {
            int i1=randomrow(); 
            int j1=randomrow(); 

            temp = shuffledDie[i][j];
            shuffledDie[i][j] = shuffledDie[i1][j1];
            temp = shuffledDie[i1][j1];
        }
    }
    string s2 = "";
     for (int i = 0; i < 5; i++)
       {
           for (int j = 0; j < 5; j++)
            {
                s2+= shuffledDie[i][j];
            }
       }
    return s1;
}

void show_board(string shuffle){
    cout<<"\n\tBOGGLE BOARD:\t\t\tSCORING KEY:"<<endl;
    cout<<"\t-------------------"<<endl;
    for(int j=0; j<5; j++)
    {
        cout<<"\t|  ";
		for(int k=0; k<5; k++)
        {
			cout<<shuffle[j*5+k]<<"  ";
		}
        cout<<"|\t\t";
        if(j==0){
            cout<<"word of length 3 = 1 point"<<endl;
        }else if(j==1){
            cout<<"word of length 4 = 2 point"<<endl;
        }else if(j==2){
            cout<<"word of length 5 = 3 point"<<endl;
        }else if(j==3){
            cout<<"word of length 6 = 6 point"<<endl;
        }else if(j==4){
            cout<<"word of length >6 = 11 point"<<endl;
        }
	}
    cout<<"\t-------------------\n";
    //cout<<"\nTime remaining  | Your words: "<<endl;
    //cout<<"(in seconds)\n"<<endl;
}

void instructions(){
    cout<<"\n\tGAME INSTRUCTIONS\n";
    cout<<"1. You can make words using the letters available on the 5X5 board\n";
    cout<<"2. The letters must be adjoining in a 'chain' \n";
    cout<<"   (Letters in the chain may be adjacent horizontally, vertically, or diagonally)\n";
    cout<<"3. Each word should be of at least three letters\n";
    cout<<"4. Words that have the exact spelling but different meanings will be counted only once\n";
    cout<<"5. You cannot repeat any words\n";
    cout<<"6. You can use both singular and plural forms of the same word\n";
    cout<<"7. Time Limit = 120 seconds\n";
    cout<<"8. Press 0 to end the game\n";
}