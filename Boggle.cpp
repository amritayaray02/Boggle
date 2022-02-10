#include <iostream>
#include <windows.h>
#include <cwchar>
#include <time.h>
#include <unordered_map>
#include <strings.h>
#include <vector>
#include <algorithm>
#include "EnglishWord.cpp"
#include "Board.cpp"
#include "Score.cpp"
using namespace std;

char** create_board(string shuffled){
    char** board = new char*[5];

    for(int i=0; i<5; i++)
    {
        board[i] = new char[5];
    }

    for(int j=0; j<5; j++)
    {
		for(int k=0; k<5; k++)
        {
			board[j][k] = shuffled[j*5+k];
		}
	}
    return board;
}

bool** visited(){
    bool** vis = new bool*[5];

    for(int i=0; i<5; i++)
    {
        vis[i] = new bool[5];
    }

    for(int j=0; j<5; j++)
    {
        for(int k=0; k<5; k++)
        {
            vis[j][k] = false;
        }
    }
    return vis;
}

bool isedge(int a, int b, int i, int j){	// a,b curr node and i,j is to be checked
	if( max( abs(a-i), abs(b-j) )==1 )
    {
		return true;
	}
	return false;
}

unordered_map<char, vector<pair<int,int>>> create_map(string shuffled){
    unordered_map<char, vector<pair<int,int>>> letter_map;
    int character = 0;

    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            pair<int,int> coord;
            coord.first = i;
            coord.second = j;
            if ( letter_map.count( shuffled[character] ) == 0 )
            {
                pair<char, vector<pair<int,int>>> p;
                vector<pair<int,int>> v;
                v.push_back(coord);
                p.first = shuffled[character];
                p.second = v;
                letter_map.insert(p);
            }else
            { 
                letter_map[shuffled[character]].push_back(coord);
            }
            character++;
        }
    }
    return letter_map;
}

bool in_board(char** board, unordered_map<char, vector<pair<int,int>>> wordmap, bool** vis, string word, int xx, int yy){
    if( word.length() ==0 )
    {
        return true;
    }
    if( wordmap.count(word[0]) != 0 )
    {
        bool ans = false;
        vector<pair<int,int>> v = wordmap[word[0]];
        int n = v.size();
        for(int j=0; j<n; j++)
        {
            int x = v[j].first, y = v[j].second;
            if(!vis[x][y] && isedge(xx,yy,x,y))
            {
                vis[x][y] = true;
                ans = in_board( board, wordmap, vis, word.substr(1), x, y );
                if(ans)
                {
                    return ans;
                }
            }
        }
    }
    return false;
}

bool Boggle(char** board, unordered_map<char, vector<pair<int,int>>> wordmap, string word){
    bool ans = false;
    bool** vis = visited();
    
    if(wordmap.count(word[0])!=0)
    {
        vector<pair<int,int>> v = wordmap[word[0]];
        int n = v.size();
        for(int j=0; j<n; j++)
        {
            int x = v[j].first, y = v[j].second;
            if( !vis[x][y] )
            {
                vis[x][y] = true;
                if( in_board( board, wordmap, vis, word.substr(1), x, y) )
                {
                    return true;
                }
            }
        }
    }
    return ans;
}

vector<string> play(string shuffled, vector<string> wordlist){
    vector<string> valid;
    char** board = create_board( shuffled );
    unordered_map<char, vector<pair<int,int>>> char_map = create_map(shuffled);
    
    int numwords = wordlist.size();
    for(int i=0; i<numwords; i++)
    {
        if( isWord( wordlist[i] ) )
        {
            if( Boggle( board, char_map, wordlist[i] ) )
            {
                valid.push_back( wordlist[i] );
            }
        }
    }
    return valid;
}

int main()
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 207);
    instructions();
    SetConsoleTextAttribute(hConsole, 224);
    string generate = shuffle_string();         // string of shuffled letters generated
    show_board(generate);                       // board is displayed
    SetConsoleTextAttribute(hConsole, 240);
    cout<<"\nTime remaining  | Your words: "<<endl;
    cout<<"(in seconds)\n"<<endl;
    transform(generate.begin(), generate.end(), generate.begin(), ::tolower);       // shuffled string is converted to lowercase
    char** grid = create_board(generate);       // 2D array of board is created

    vector<string> input;                       // user input of words is taken from here
    unordered_map<string, int> duplicate;
    string s;
    time_t start = time(NULL);                    // start time
    time_t end = time(NULL) + 120;            // end time

    while(s != "0")                             // when user enters "0", input terminates
    {
        if(time(NULL) > end)
        {
            SetConsoleTextAttribute(hConsole, 116);
            cout<<endl<<endl<<"YOUR TIME IS UP!!!"<<endl;
            break;
        }
        int now = (int)(time(NULL) - start);       // current time
        cout<< (120 - now) <<"\t\t| ";
        cin>>s;
        if(time(NULL) > end)
        {
            SetConsoleTextAttribute(hConsole, 116);
            cout<<endl<<endl<<"YOUR TIME IS UP!!!"<<endl;
            break;
        }

        transform(s.begin(), s.end(), s.begin(), ::tolower);
        if(duplicate.count(s)==0){              // removes duplicates entered by user
            pair<string,int> p;
            p.first = s;
            p.second = 1;
            duplicate.insert(p);
            input.push_back(s);
        }
    }

    vector<string> output = play(generate, input);      // valid strings entered by user
    SetConsoleTextAttribute(hConsole, 6);
    cout<<"\nValid words entered by you are: ";
    int n = output.size();                              // valid user input words are displayed
    for(int i=0; i<n; i++)
    {
        cout<<output[i]<<", ";
    }

    int score = calculatePoints(output);                            // points calculated
    SetConsoleTextAttribute(hConsole, 2);
    cout<<endl<<"\nYou scored "<<score<<" points!\n"<<endl;         // points displayed
	return 0;
}