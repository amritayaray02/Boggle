#include <iostream>
#include <vector>
using namespace std;

int calculatePoints(vector<string> ValidString){
    
    int points = 0;
    int size = ValidString.size();

    for(int i=0; i<size; i++){
      string str = ValidString[i];
      int len = str.length();
    
      if(len == 3){
          points+=1;
      }
      else if(len == 4){
          points+=2;
      }
      else if(len == 5){
          points+=3;
      }
      else if(len == 6){
          points+=6;
      }
      else if(len>6){
          points+=11;
      }
    }

    return points;
}