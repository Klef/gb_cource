#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>


using namespace std;
using std::__fs::filesystem::directory_iterator;

const string Dir = "/data/web/wasteland.su/games/";
const string DataBase = Dir + "tictactoe.ini";
const string DirLog = Dir + "upload/data/";

enum Status
{
    IN_GAME,
    WIN_HUMAN,
    WIN_AI,
    STAND_OF,
    ERROR
};

int main() {


    for (const auto & file : directory_iterator(DirLog))
    {
        string NameFileLog = file.path();
        ifstream FileOfLog;
        FileOfLog.open(NameFileLog);
        if (FileOfLog.is_open())
        {
            cout << NameFileLog << endl;
            string stLog;
            bool isCorrect = true;
            size_t isShag = 0;
            Status isResult;
            int StrokInLog = 0;
            int StrokFind = 0;
            for (FileOfLog >> stLog; !FileOfLog.eof(); FileOfLog >> stLog) 
            {
                cout << stLog << endl;
                int Test = 1;
                //isResult = Test;
                if (stLog.length() == 1 && isShag == 2)
                {
                    isResult = static_cast<Status> (stoi(stLog));
                    isShag++;
                }
                if (stLog.length() != 20 && isShag == 2)
                {
                    isCorrect = false;
                }
                if (stLog.length() == 5 && isShag == 0)
                {
                    isShag++;
                }
                if (stLog.length() == 20 && isShag == 1)
                {
                    isShag++;
                }
                if (stLog.length() == 20)
                {
                    StrokInLog++;
                }
                
                
            }
            if (isShag != 3)
            {
                isCorrect = false;
            }
            if (isCorrect)
            {
                cout << "Good" << endl;
                int Shag = 0;
                switch (isResult)
                {
                case WIN_HUMAN:
                    Shag = -1;
                    break;
                case WIN_AI:
                    Shag = 3;
                    break;
                case STAND_OF:
                    Shag = 1;
                    break;
                default:
                    break;
                }
                unsigned int game_sum = 0;
                unsigned int game_win = 0;
                unsigned int game_los = 0;
                unsigned int game_nop = 0;
                ifstream FileOfDB_orig;
                ofstream FileOfDb_new;
                FileOfDB_orig.open(DataBase);
                FileOfDb_new.open(DataBase+".tmp");
                bool Find = false;
                if (FileOfDb_new.is_open() && FileOfDB_orig.is_open())
                {
                    string stOrig;
                    for (FileOfDB_orig >> stOrig; !FileOfDB_orig.eof(); FileOfDB_orig >> stOrig) 
                    {
                        Find = false;
                        string Chtoto;
                        size_t Finding = 0;
                        FileOfLog.clear();
                        FileOfLog.seekg(0);
                        for (FileOfLog >> stLog; !FileOfLog.eof(); FileOfLog >> stLog)
                        {
                            Finding = 0;
                            for (size_t i = 0; i < stLog.length(); i++)
                            {
                                if (stLog[i] == 35)
                                {
                                    stLog[i] = 46;
                                }
                                if (stLog[i] == stOrig[i])
                                {
                                    //cout << stLog[i] << "=" << stOrig[i] << " " << Finding << endl;
                                    Finding++;
                                }
                            }
                            if (Finding > 19) {
                                Find = true;
                                Chtoto = stLog;
                                break;
                            }
                            
                        }
                        bool isItog = false;
                        if (stOrig[0] == 87)
                        {
                            stOrig[0] = 48;
                            game_win = stoi(stOrig,nullptr,10);
                            if (isResult == WIN_AI)
                            {
                                game_win++;
                            }
                            isItog = true;
                        }
                        if (stOrig[0] == 76)
                        {
                            stOrig[0] = 48;
                            game_los = stoi(stOrig,nullptr,10);
                            if (isResult == WIN_HUMAN)
                            {
                                game_los++;
                            }
                            isItog = true;
                        }
                        if (stOrig[0] == 78)
                        {
                            stOrig[0] = 48;
                            game_nop = stoi(stOrig,nullptr,10);
                            if (isResult == STAND_OF)
                            {
                                game_nop++;
                            }
                            isItog = true;
                        }
                        if (stOrig[0] == 71)
                        {
                            stOrig[0] = 48;
                            game_sum = stoi(stOrig,nullptr,10);
                            game_sum++;
                            isItog = true;
                        }
                        if (Find)
                        {
                            int Umnik = stoi(stOrig.substr(21),nullptr,10);
                            int Itog = ((Umnik + Shag)<0) ? 0 : (Umnik + Shag);
                            FileOfDb_new << Chtoto << "!" << Itog << endl;
                            StrokFind++;
                        }
                        else
                        {
                            if (!isItog)
                            {
                                FileOfDb_new << stOrig << endl;
                            }
                        }
                    }
                }
                if (StrokFind != StrokInLog)
                {
                    FileOfLog.clear();
                    FileOfLog.seekg(0);
                    while(getline(FileOfLog, stLog))
                    {
                        Find = false;
                        if (stLog.length() == 20)
                        {
                            FileOfDB_orig.clear();
                            FileOfDB_orig.seekg(0);
                            string line;
                            int offset;
                            while(getline(FileOfDB_orig, line))
                            {
                                if ((offset = line.find(stLog, 0)) != string::npos) {
                                    cout << "found: " << stLog << endl;
                                    Find = true;
                                    break;
                                }
                            }
                            if (!Find)
                            {
                                cout << "NOT FOUND";
                                FileOfDb_new << stLog << "!" << 2 << endl;
                                cout << stLog << endl;
                            }
                        }
                    }
                }
                // if (!Find)
                // {
                //     FileOfDb_new << Chtoto << "!" << 1 << endl;
                // }
                FileOfDb_new << "G" << game_sum << endl;
                FileOfDb_new << "W" << game_win << endl;
                FileOfDb_new << "L" << game_los << endl;
                FileOfDb_new << "N" << game_nop << endl;
                FileOfDB_orig.close();
                FileOfDb_new.close();
                FileOfDB_orig.open(DataBase+".tmp", ios::binary);
                FileOfDb_new.open(DataBase, ios::binary);

                if (FileOfDb_new.is_open() && FileOfDB_orig.is_open())
                {
                    cout << "Writing" << endl;
                    char * buffer;
                    buffer = new char;
                    FileOfDB_orig.read(buffer, sizeof(char));
                    while (!FileOfDB_orig.eof())
                    {
                        FileOfDB_orig.read(buffer, sizeof(char));
                        FileOfDb_new.write(buffer, sizeof(char));
                    }
                    delete buffer;
                }
                FileOfDB_orig.close();
                FileOfDb_new.close();
            }
            remove(NameFileLog.c_str());
        }

        FileOfLog.close();
    }
    return 0;
}