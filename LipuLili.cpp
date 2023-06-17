
#define WORDLIST_NAME "wordlist.txt"

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <bitset>



using namespace std;

template<typename T>
inline T LoadFile(const std::string& filename, const std::string& fileClass = "File");


void Encode(fstream file);
void Decode(fstream file);

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout << "Usage: " << argv[0] << " <input> <output>" << endl;
        return 1;
    }


    //Loads the supplied file and the wordlist
    
    ifstream fin = LoadFile<ifstream>(argv[1], "input");   
    ifstream WordList(WORDLIST_NAME);

    if(!WordList || WordList.bad())
    {
        cout << "Wordlist file not found! \nThe file has to be named wordlist.txt!" << endl;
        return 1;
    }
    
    map<string,uint8_t> wordlist;
    
    int linecount = 0;
    string line;
    while(getline(WordList,line))
    {
        wordlist[line] = linecount;
        linecount++;
    }

    
    string OutFileName{argv[2]};
    
    string::size_type DotPos = OutFileName.find(".", 0);
    
    if(DotPos != 0 )
    {
        OutFileName = OutFileName.substr(0,DotPos );
    }

    cout << OutFileName;

    string InFileName{argv[1]};
    string InFileExtension = InFileExtension.substr(InFileName.find("."), InFileName.length());


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
        std::cerr << fileClass << " not found!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return filestream;
}
void Encode(fstream file)
{

}
void Decode(fstream file)
{

}