#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <bitset>
#include <vector>
#include <algorithm>

#define WORDLIST_NAME "wordlist.txt"
#define ENCODED_EXTENSION ".tok"

using namespace std;
using WordList_T = std::map<string, uint8_t>;

template<typename T>
inline T LoadFile(const std::string& filename, const std::string& fileClass = "File");

void Encode(ifstream &file, string OutFileName, const WordList_T &wordlist);
void Decode(ifstream &file, string OutFileName, const WordList_T &wordlist);
bool isalpha(string str);

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout << "Usage: " << argv[0] << " <input> <output> \n" << endl;
        return 1;
    }


    //Loads the supplied file and the wordlist
    
    ifstream fin = LoadFile<ifstream>(argv[1], "Input");   
    ifstream WordList(WORDLIST_NAME);

    if(!WordList || WordList.bad())
    {
        cout << "Wordlist file not found! \nThe file has to be named wordlist.txt! \n" << endl;
        return 1;
    }
    
    WordList_T wordlist;
    
    int linecount = 0;
    string line;
    while(getline(WordList,line))
    {
        wordlist[line] = linecount;
        linecount++;
    }

    
    string OutFileName{argv[2]};
    
    string::size_type OutDotPos = OutFileName.find(".", 0);
    
    if(OutDotPos != string::npos )
    {
        OutFileName = OutFileName.substr(0,OutDotPos );
    }

    

    string InFileName{argv[1]};

    string InFileExtension{""};

    string::size_type InDotPos = InFileName.find(".", 0);
    if(InDotPos != string::npos )
    {
        InFileExtension = InFileName.substr(InDotPos );
    }
    
    if(InFileExtension == ".txt")
    {
        Encode(fin, OutFileName, wordlist);
    }
    else
    {
        Decode(fin, OutFileName, wordlist );
    }
    
    


    fin.close();
    WordList.close();
    return 0;



}


template<typename T>
inline T LoadFile(const std::string& filename, const std::string& fileClass)
{
    T filestream(filename, std::ios::in);

    if (!filestream || filestream.bad())
    {
        std::cerr << fileClass << " could not be loaded!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return filestream;
}
void Encode(ifstream &file, string OutFileName, const WordList_T &wordlist)
{
    ofstream OutFile = LoadFile<ofstream>(OutFileName + ENCODED_EXTENSION, "Output");


    string word{};

    std::vector<std::string> words;
    
    while(file >> word)
    {
        
       

        if(isalpha(word))
        {
            words.push_back(word);
        }
        else
        {
            auto SplitPoint = find_if(word.begin(), word.end(), [](char c) { return !isalpha(c); } );
            
            words.push_back(word.substr(0, distance(word.begin(), SplitPoint)));
            words.push_back(word.substr(distance(word.begin(), SplitPoint)));
        }
        
    }
    for(auto str : words)
    {
        cout << str << " " << (unsigned int) wordlist.at(str) << endl;
        OutFile.write(  (char*) &wordlist.at(str), sizeof(uint8_t));
    }



    OutFile.close();

}
void Decode(ifstream &file, string OutFileName, const WordList_T &wordlist)
{

}
bool isalpha(string str)
{
    for(char cha : str)
    {
        if(isalpha(cha))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}