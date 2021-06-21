#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <curl/curl.h>
#include <ctime>
#include <sys/stat.h>


#define BITFIELD x+y*FIELD_SIZE
#define BITSIZE FIELD_SIZE*FIELD_SIZE


using namespace std;

char ok;
const size_t FIELD_SIZE = 3;
const size_t PL_SIZE = 4;
const size_t CHANCE = 10; //10% на то что бы алгоритм протупил





enum cell
{
    H_HZ = 63,
    X_CROSS = 88,
    O_CIRCLE = 79,
    F_EMTY = 95
};

enum progress
{
    IN_GAME,
    WIN_HUMAN,
    WIN_AI,
    STAND_OF,
    ERROR
};

enum gamer
{
    IS_HUMAN,
    AI_GOOSE,
    AI_TIT,
    AI_SHADOOF
};

struct general
{
    cell Field[FIELD_SIZE][FIELD_SIZE];
    progress Progress = IN_GAME;
    size_t idHuman;
    size_t Tour = 0;
    string Type[PL_SIZE] = {
        "Человек",
        "Глупый",
        "Алгоритм",
        "Коробочка"
    };
    gamer AI;
    string LogFile;

};

static size_t write_data(char *data, size_t size, size_t nmemb, std::ofstream* pBuf){
    size_t result = 0;
    if(pBuf != NULL){
        pBuf->write(data, size*nmemb);
        result = size * nmemb;
    }
    return result;
}

static size_t read_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    curl_off_t nread;

    size_t retcode = fread(ptr, size, nmemb, (FILE*)stream);

    nread = (curl_off_t)retcode;

    return retcode;
}

void ProntField(general & f);

void CheckWin(general & f)
{
    //0 -x
    //1 -o
    bool Win = false;
    for (size_t i = 0; i<2;i++)
    {
        
        cell Verify = (i == 0) ? X_CROSS : O_CIRCLE;
        if (f.Field[0][0] == Verify && f.Field[0][1] == Verify && f.Field[0][2] == Verify) { Win = true;}
        if (f.Field[1][0] == Verify && f.Field[1][1] == Verify && f.Field[1][2] == Verify) { Win = true;}
        if (f.Field[2][0] == Verify && f.Field[2][1] == Verify && f.Field[2][2] == Verify) { Win = true;}
        if (f.Field[0][0] == Verify && f.Field[1][0] == Verify && f.Field[2][0] == Verify) { Win = true;}
        if (f.Field[0][1] == Verify && f.Field[1][1] == Verify && f.Field[2][1] == Verify) { Win = true;}
        if (f.Field[0][2] == Verify && f.Field[1][2] == Verify && f.Field[2][2] == Verify) { Win = true;}
        if (f.Field[0][0] == Verify && f.Field[1][1] == Verify && f.Field[2][2] == Verify) { Win = true;}
        if (f.Field[0][2] == Verify && f.Field[1][1] == Verify && f.Field[2][0] == Verify) { Win = true;}
        if (Win)
        {
            if (i == 0 && f.idHuman == 0)
            {
                f.Progress = WIN_HUMAN;
            }
            else if (i == 1 && f.idHuman == 1)
            {
                f.Progress = WIN_HUMAN;
            }
            else
            {
                f.Progress = WIN_AI;
            }
            break;
        }


    }
    if (f.Tour > 8 && f.Progress == IN_GAME)
    {
        f.Progress = STAND_OF;
    }
}

int InPut(string Txt, size_t MaxValue)
{
    bool C = true;
    size_t InputInt;
    cout << endl;
    cout << Txt << ": ";
    do
    {
        cin >> InputInt;
        if (( InputInt > 0) && (InputInt <= MaxValue))
        {
            C = false;
        }
        else
        {
            cout << endl << "Значение  должно быть от 1 до " << MaxValue << ". Попробуйте еще раз: ";
        }
    } while (C);
    return InputInt;
}

void InitGame( general & f)
{
    //заполняем игровое поле
    for (size_t x = 0; x < FIELD_SIZE; x++)
    {
        for (size_t y = 0; y < FIELD_SIZE; y++)
        {
           f.Field[x][y] = F_EMTY; 
        }
    }
    
    //Выбираем противника
    cout << "Варианты искуственного интелекта: " << endl;
    for (size_t i = 1; i < PL_SIZE; i++)
    {
        cout << i << " - " << f.Type[i] << endl;
    }
    int AI = InPut("Введите ваш выбор", (PL_SIZE-1));
    //int AI = 3;
    f.AI = (gamer)AI;
    //выбираем кто будет ходить первых
    //первыми ходят крестики
    size_t r = (rand() % 2);
    f.idHuman = r;
    cout << "Спасибо за выбор, ваш противник \"" << f.Type[AI] << "\""<< endl;
    cout << "Он играет: " << ((f.idHuman != 0) ? "крестиками (X)" : "ноликами (O)") << endl;
    cout << "Приятной игры" << endl;
    if ( f.AI == AI_SHADOOF) {
        cout << "===========================" << endl;
        cout << "Данный алгоритм использует механизм обучения на основе \"спичечных коробков\"" << endl;
        cout << "Каждая игра делает его умнее" << endl;
        bool AlR = true;
        unsigned int game_sum = 0;
        unsigned int game_win = 0;
        unsigned int game_los = 0;
        unsigned int game_nop = 0;
        ofstream Log;
        Log.open(f.LogFile);
        if (Log.is_open())
        {
            Log <<  "Begin" << endl;
        }
        Log.close();

        CURL *curl;
        CURLcode result;
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "http://wasteland.su/games/tictactoe.ini");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            ofstream CurlToFile;
            CurlToFile.open("tictactoe.ini", ios::binary);
            if (CurlToFile.is_open())
            {
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &CurlToFile);
                curl_easy_perform(curl);
                if(result != CURLE_OK)
                {
                    cout << "WARNING: Невозможно скачать файл" << endl;
                    AlR = false;
                }
            }
            else
            {
                cout << "WARNING: Невозможно записать файл" << endl;
                AlR = false;
            }
            CurlToFile.close();
            curl_easy_cleanup(curl);
        }
        else
        {
            cout << "WARNING: Недоступна библеотека curl" << endl;
            AlR = false;
        }

        ifstream FileAlgoritm;
        FileAlgoritm.open("tictactoe.ini");
        if (FileAlgoritm.is_open())
        {
            string s;
            for (FileAlgoritm >> s; !FileAlgoritm.eof(); FileAlgoritm >> s) 
            {
                if (s[0] == 87)
                {
                    s[0] = 48;
                    game_win = stoi(s,nullptr,10);
                }
                if (s[0] == 76)
                {
                    s[0] = 48;
                    game_los = stoi(s,nullptr,10);
                }
                if (s[0] == 78)
                {
                    s[0] = 48;
                    game_nop = stoi(s,nullptr,10);
                }
                if (s[0] == 71)
                {
                    s[0] = 48;
                    game_sum = stoi(s,nullptr,10);
                }
            }
        }
        else
        {
            cout << "WARNING: Файл с алгоритмом не найден" << endl;
            AlR = false;
        }
        if (game_sum == 0)
        {
            cout << "WARNING: Битые данные" << endl;
            AlR = false;
        }
        if (AlR) {
            
            cout << "Он провел игр: " << game_sum << endl;
            cout << "Из них: " << endl;
            cout << "Выиграл: " << game_win << " (" << ((float)game_win / game_sum * 100) << "%)" << endl;
            cout << "Проиграл: " << game_los << " (" << ((float)game_los / game_sum * 100) << "%)" << endl;
            cout << "Свел в ничью: " << game_nop << " (" << ((float)game_nop / game_sum * 100) << "%)" << endl;
        }
        else
        {
            f.Progress = ERROR;
            cout << "К сожалению вы не сможете поиграть :(" << endl;
        }
        cout << "===========================" << endl;
    }
    cout << "Для продолжения нажимете ENTER" << endl <<endl;
    cin.get(ok);
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void EndGame( general & f)
{   
    ProntField(f);
    
    
    switch (f.Progress)
    {
    case WIN_AI:
        cout << "Победил искуственный интелект" << endl;
        switch (f.AI)
        {
        case IS_HUMAN:
            cout << "Оо";
            break;
        case AI_GOOSE:
            cout << "Поражены вашей неудачей";
            break;
        case AI_TIT:
            cout << "Не растраивайтесь";
            break;
        case AI_SHADOOF:
            cout << "Он учится";
        default:
            break;
        }
        break;
    case WIN_HUMAN:
        cout << "Вы победили" << endl;
        switch (f.AI)
        {
        case IS_HUMAN:
            cout << "Oo";
            break;
        case AI_GOOSE:
            cout << "Это было не трудно";
            break;
        case AI_TIT:
            cout << "Поздравляю";
            break;
        case AI_SHADOOF:
            cout << "Теперь он стал умнее благодаря вам";
        default:
            break;
        }
        break;
    case STAND_OF:
        cout << "Ничья" << endl << "Победила дружба";
        break;
    case IN_GAME:
        cout << "Вы не должны были этого увидеть";
    default:
        cout << "Что то пошло не так, приносим свои изменения";
        break;
    }
    cout << endl << "Спасибо за игру" << endl << endl;
    
    if ( f.AI == AI_SHADOOF )
    {
        ofstream Log;
        Log.open(f.LogFile,ios::app);
        if (Log.is_open())
        {
            Log <<  f.Progress << endl;
        }
        Log.close();
        //отправь файл
        //curl
        
        CURL *curl;
        CURLcode res;
        FILE *hd_src;
        struct stat file_info;
        //переписать!!!
        stat(f.LogFile.c_str(), &file_info);
        curl_off_t fsize = (curl_off_t)file_info.st_size;
        hd_src = fopen(f.LogFile.c_str(), "rb");
        curl_global_init(CURL_GLOBAL_ALL);

        struct curl_slist *headerlist=NULL;
        string url = "http://wasteland.su/games/upload/" + f.LogFile;
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
            curl_easy_setopt(curl, CURLOPT_PUT, 1L);
            curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_data);
            curl_easy_setopt(curl, CURLOPT_POSTQUOTE, headerlist);
            curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);
            curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fsize);
            curl_easy_perform(curl);
            curl_slist_free_all (headerlist);
            curl_easy_cleanup(curl);  
        }
        fclose(hd_src);
        curl_global_cleanup();   

        //очистка всякого
        remove("tictactoe.ini");
        remove(f.LogFile.c_str());
    }
}

void ProntField(general & f)
{
    std::cout << "\x1B[2J\x1B[H";
    cout << "Игра \"Крестики Нолики\"" << endl;
    cout << "Ход# " << (f.Tour / 2 + 1) << endl;
    cout << "Вы играете: " << ((f.idHuman == 0) ? "крестиками (X)" : "ноликами (O)") << endl;
    cout << "Ваш противник: " << f.Type[f.AI] << endl << endl;
    cout << "  ";
    for (size_t x = 0; x < FIELD_SIZE; x++)
    {
        cout << " " << (x+1);
    }
    cout <<  endl;
    for (size_t y = 0; y < FIELD_SIZE; y++)
    {
        cout << (y+1) << " |";
        for (size_t x = 0; x < FIELD_SIZE; x++)
        {   
            cout << (char)f.Field[x][y];
            cout << "|";
            
        }
        cout << endl;
    }
    cout << endl;
}

bool isEmpty(general & f, int x, int y)
{
    if (f.Field[x][y] != F_EMTY)
    {
        ProntField(f);
        
        cout << "Данные координаты заняты уже фигурой" << endl;
        return false;
    }
    
    return true;
}

void HumanTour(general & f)
{
    cout << "Ваш ход: ";
    bool C = true;
    int X;
    int Y;
    do
    {
        X = InPut("Введите номер столбца", FIELD_SIZE);
        Y = InPut("Введите номер строки", FIELD_SIZE);
        C = !isEmpty(f, (X-1), (Y-1));
        //C = false;
    } while (C);
    f.Field[X-1][Y-1] = (f.idHuman == 0) ? X_CROSS : O_CIRCLE;
    f.Tour++;
}


void AiPush(general & f, size_t W)
{
    size_t X = W%FIELD_SIZE;
    size_t Y = W/FIELD_SIZE;
    cell AI = (f.idHuman != 0) ? X_CROSS : O_CIRCLE;
    f.Field[X][Y] = AI;
    
}

bool Ugroza(string Cur, int I, char Plus, char Minus)
{
    int Defcon = 0;
    size_t X = I%FIELD_SIZE;
    size_t Y = I/FIELD_SIZE;
    //горизонтали
    for (size_t y = 0; y < FIELD_SIZE; y++)
    {
        size_t x = X;
        if (Cur[BITFIELD] == Plus)
        {
            Defcon++;
        }
        if (Cur[BITFIELD] == Minus)
        {
            
            Defcon--;
        }
    }
    if (Defcon > 1)
    {
        return true;
    }
    //вертикали
    Defcon = 0;
    for (size_t x = 0; x < FIELD_SIZE; x++)
    {
        size_t y = Y;
        if (Cur[BITFIELD] == Plus)
        {
            Defcon++;
        }
        if (Cur[BITFIELD] == Minus)
        {
            Defcon--;
        }
    }
    if (Defcon > 1)
    {
        return true;
    }
    //диагональ
    Defcon = 0;
    if (X == Y)
    {
        for (size_t i = 0; i < FIELD_SIZE; i++)
        {
            size_t x = i;
            size_t y = i;
            if (Cur[BITFIELD] == Plus)
            {
                Defcon++;
            }
            if (Cur[BITFIELD] == Minus)
            {
                Defcon--;
            }
        }
        if (Defcon > 1)
        {
            return true;
        }
    }
    //обратная диагональ
    Defcon = 0;
    if (X == 2 - Y)
    {
        for (size_t i = 0; i < FIELD_SIZE; i++)
        {
            size_t x = i;
            size_t y = 2 - i;
            if (Cur[BITFIELD] == 45)
            {
                Defcon++;
            }
            if (Cur[BITFIELD] == Minus)
            {
                Defcon--;
            } 
        }
        if (Defcon > 1)
        {
            return true;
        }
    }
    return false;
}

void AITour(general & f)
{
    
    //"Ход нечеловека"
    // 46 - чистое
    // 45 - ход противника
    // 43 - наш ход
    // 42 - вероятный ход
    // 35 - уже определено
    //собираем описание поля
    string Current(BITSIZE, 0);
    for (size_t i =0; i<(BITSIZE); i++)
    {
        Current[i] = 46;
    }
    
    for (size_t x = 0; x<FIELD_SIZE; x++)
    {
        for (size_t y = 0; y<FIELD_SIZE; y++)
        {
            if (f.Field[x][y] == X_CROSS && f.idHuman == 0)
            {
                Current[BITFIELD] = 45;
            }
            if (f.Field[x][y] == X_CROSS && f.idHuman == 1)
            {
                Current[BITFIELD] = 43;
            }
            if (f.Field[x][y] == O_CIRCLE && f.idHuman == 0)
            {
                Current[BITFIELD] = 43;
            }
            if (f.Field[x][y] == O_CIRCLE && f.idHuman == 1)
            {
                Current[BITFIELD] = 45;
            }
        }
    }
    size_t Variants = 0;
    for (size_t i = 0; i < (BITSIZE); i++)
    {
        if (Current[i] == 46)
        {
            Variants++;
        }
    }
    string * pt_Variants = new string[Variants];
    switch (f.AI)
    {
    case AI_GOOSE:
        //Гусек думает
        {
            string Temp = Current;
            for (size_t i = 0; i < Variants; i++) {
                pt_Variants[i] = Temp;
                for (size_t ch = 0; ch < BITSIZE; ch++)
                {
                    if (pt_Variants[i][ch] == 46)
                    {
                        pt_Variants[i][ch] = 42;
                        Temp[ch] = 35;
                        break;
                    }
                }
            }
            size_t Where = (rand() % (Variants));
            size_t Witch = 0;
            Temp = pt_Variants[Where];
            for (size_t i = 0; i < BITSIZE; i++)
            {
                if (Temp[i] == 42)
                {
                    Witch = i;
                    break;
                }

            }
            AiPush(f, Witch);
        }
        break;
    case AI_TIT:
        {
            //Синичка думает
            size_t Nums = 0;
            bool Prioritet = false;
            string Temp = Current;
            size_t t;
            //Решительно побеждаем
            for (int i = 0; i < BITSIZE; i++)
            {
                if (Temp[i] == 46)
                {
                    if (Ugroza(Temp,i, 43, 45))
                    {
                        Prioritet = true;
                        pt_Variants[Nums] = Temp;
                        pt_Variants[Nums][i] = 42;
                        Temp[i] = 35;
                        Nums++;
                    }
                }
            }
            //Мешаем
            for (int i = 0; i < BITSIZE; i++)
            {
                if (Temp[i] == 46)
                {
                    if (Ugroza(Temp,i, 45, 43))
                    {
                        Prioritet = true;
                        pt_Variants[Nums] = Temp;
                        pt_Variants[Nums][i] = 42;
                        Temp[i] = 35;
                        Nums++;
                    }
                }
            }
            //заполняем углы
            t = 0;
            if (Temp[t] == 46) 
            {
                pt_Variants[Nums] = Temp;
                pt_Variants[Nums][t] = 42;
                Temp[t] = 35;
                Nums++;
            }
            t = 2;
            if (Temp[t] == 46) 
            {
                pt_Variants[Nums] = Temp;
                pt_Variants[Nums][t] = 42;
                Temp[t] = 35;
                Nums++;
            }
            t = 6;
            if (Temp[t] == 46) 
            {
                pt_Variants[Nums] = Temp;
                pt_Variants[Nums][t] = 42;
                Temp[t] = 35;
                Nums++;
            }
            t = 8;
            if (Temp[t] == 46) 
            {
                pt_Variants[Nums] = Temp;
                pt_Variants[Nums][t] = 42;
                Temp[t] = 35;
                Nums++;
            }
            
            //выводим на ничью вместо того что бы падать в ошибку
            if (Nums == 0) 
            {
                for (size_t i = 0; i<Variants; i++)
                {
                    pt_Variants[Nums] = Temp;
                    for (size_t ch = 0; ch < BITSIZE; ch++)
                    {
                        if (pt_Variants[i][ch] == 46)
                        {
                            pt_Variants[i][ch] = 42;
                            Temp[ch] = 35;
                            Nums++;
                            break;
                        }
                    }
                }
            }
            size_t Where = (rand() % (Nums));
            size_t Witch = 0;
            Temp = pt_Variants[Where];
            for (size_t i = 0; i < BITSIZE; i++)
            {
                if (Temp[i] == 42)
                {
                    Witch = i;
                    break;
                }

            }
            //даем шанс игроку
            if ((rand() % CHANCE) == 0)
            {
                Prioritet = false;
            }
            if (Prioritet)
            {
                Temp = pt_Variants[0];
                for (size_t i = 0; i < BITSIZE; i++)
                {
                    if (Temp[i] == 42)
                    {
                        Witch = i;
                        break;
                    }

                }
            }
            AiPush(f, Witch);
        }
        break;
    case AI_SHADOOF:
        //Журавль не думает, он покоряет небеса
        {
            ifstream FileAlgoritm;
            FileAlgoritm.open("tictactoe.ini");
            if (FileAlgoritm.is_open())
            {
                string s;
                unsigned int num_Vars = 0;
                for (FileAlgoritm >> s; !FileAlgoritm.eof(); FileAlgoritm >> s) 
                {
                    bool is_Variant = true;
                    if (s[0] == 33) 
                    {
                        for (size_t i = 0; i < BITSIZE; i++) {
                            if (Current[i] != s[i+1])
                            {
                                is_Variant = false;
                                break;
                            }
                        }
                        if (is_Variant)
                        {
                            int KolVars = stoi(s.substr(21),nullptr,10);
                            num_Vars += KolVars;
                        } 
                    }
                }
                size_t Where = 0;
                size_t Witch = 0;
                string Hod = Current;
                //шанс изменения стратегии
                if ((rand() % CHANCE) == 0)
                {
                    num_Vars = 0;
                }
                cout << num_Vars << endl;
                if (num_Vars == 0)
                {
                    //не нашел ходов, делает рандом
                    string Temp = Current;
                    for (size_t i = 0; i < Variants; i++) {
                        pt_Variants[i] = Temp;
                        for (size_t ch = 0; ch < BITSIZE; ch++)
                        {
                            if (pt_Variants[i][ch] == 46)
                            {
                                pt_Variants[i][ch] = 42;
                                Temp[ch] = 35;
                                break;
                            }
                        }
                    }
                    Where = (rand() % (Variants));
                    Witch = 0;
                    Temp = pt_Variants[Where];
                    Hod = pt_Variants[Where];
                    for (size_t i = 0; i < BITSIZE; i++)
                    {
                        if (Temp[i] == 42)
                        {
                            Witch = i;
                            break;
                        }

                    }
                }
                else
                {
                    FileAlgoritm.clear();
                    FileAlgoritm.seekg(0);
                    num_Vars++;
                    string * pt_BoxVariants = new string[num_Vars];
                    int ish = 0;
                    for (FileAlgoritm >> s; !FileAlgoritm.eof(); FileAlgoritm >> s) 
                    {
                        bool is_Variant = true;
                        if (s[0] == 33) 
                        {
                            for (size_t i = 0; i < BITSIZE; i++) {
                                if (Current[i] != s[i+1])
                                {
                                    is_Variant = false;
                                    
                                    break;
                                }
                            }
                            if (is_Variant)
                            {
                                //substr
                                int KolVars = stoi(s.substr(21),nullptr,10);
                                for (size_t MnogoVars = 1; MnogoVars <= KolVars; MnogoVars++)
                                {
                                    pt_BoxVariants[ish] = Current;
                                    for (size_t tuk = 0; tuk < BITSIZE; tuk++)
                                    {
                                        
                                        pt_BoxVariants[ish][tuk] = s[tuk+11];
                                    }
                                    ish++;
                                }
                            } 
                        }
                    }
                    Where = (rand() % (num_Vars-1));
                    Witch = 0;
                    string Temp = pt_BoxVariants[Where];
                    Hod = pt_BoxVariants[Where];
                    delete [] pt_BoxVariants;
                    for (size_t i = 0; i < BITSIZE; i++)
                    {
                        if (Temp[i] == 42)
                        {
                            Witch = i;
                            break;
                        }
                    }
                }
                AiPush(f, Witch);
                ofstream Log;
                Log.open(f.LogFile,ios::app);
                if (Log.is_open())
                {
                    Log << "!" << Current << "!" << Hod << endl;
                }
                else
                {
                    f.Progress = ERROR;
                }
                Log.close();
            }
            else
            {
                f.Progress = ERROR;
            }
            FileAlgoritm.close();
        }
        break;
    default:
        break;
    }
    // cout << endl << "отладка" << endl;
    // cin.get(ok);
    // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    delete [] pt_Variants;
    f.Tour++;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand (static_cast <unsigned> (time(0)));
    general f;
    f.LogFile = "log" + to_string(static_cast<long int> (time(NULL))) + ".ini";
    InitGame(f);
    //std::cout << "\x1B[2J\x1B[H";

    while (f.Progress == IN_GAME)
    {
        ProntField(f);
        if (f.Tour % 2 == f.idHuman) 
        {
            HumanTour(f);
        }
        else
        {
            AITour(f);
        }
        CheckWin(f);
    }
    EndGame(f);
    cout << "Для завершения работы приложения нажимете ENTER" << endl <<endl;
    cin.get(ok);
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return 0;
}