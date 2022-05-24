#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main(){
    setlocale(LC_ALL, "ru");
    srand(time(0));

    string str = "1";
    int step;
    bool ind = false;
    int buff = 0;

    //--------------------1 point------------------------------- 
    cout << "enter our degree(bytes): ";
    cin >> step;
    for (int i = 0; i < step; i++) {
        //шагаем по всей строке 
        for (int j = str.size() - 1; j >= 0; j--) {
            //cout << str[j] << endl;
            //если от 0 до 4 - просто умножаем 
            if (str[j] <= 52) {
                str[j] = (char)(((str[j] - 48) * 2) + 48);
                if (ind) {
                    str[j]++;
                    ind = false;
                }
                //cout << "str:" << str[j] << endl;
            }
            //если нет - начинается игра на выживание :_) если 5 - отнимаем единицу
            else {
                str[j] = (char)(((str[j] - 48) * 2) % 10 + 48);
                if (ind && buff - j == 1) {
                    str[j]++;
                    ind = false;
                }
                ind = true;
                buff = j;
                //cout << str[j] << endl;
            }
            if (ind && j == 0) {
                str.insert(str.begin(), 48);
                str[j]++;
                ind = false;
            }
        }

    }
    cout << "max lim = " << str << endl;

    //----------------------2 point-----------------------
    string code = str;
    int counter = 0;
    //отдельный случай для первого элемента (генерим по самому старшему разряду, если имеется ошибка - откат и все заново)
    for (int i = 0; i < str.size(); i++) {
        if (i == 0) {
            int buf = code[0];
            code[i] = (((code[i] - 48) * (rand() % 1000)) % 10) + 48;
            if (code[0] > buf) {
                code[0] = buf;
            }
        }
        else {
            code[i] = (((code[i] - 48) * (rand() % 1000)) % 10) + 48;
        }

    }
    //обеспечивает различную разрядность (7 раз чтоб обеспечить диапазон, пока все циферки не заменим на 0)
    if (str.size() > 7) {
        for (int i = 0; i < str.size() / 7; i++) {
            for (int j = rand() % 7; j < 7; j++) {
                code[counter] = 48;
                counter++;
            }
        }
    }
    else {
        for (int i = 0; i < str.size(); i++) {
            if (rand() % 2 == 0) {
                code[counter] = 48;
                counter++;
            }
        }
    }
    //удаляем нули - уменьшаем разрядность
    while (code[0] == 48)
    {
        if (code.size() == 1) {
            break;
        }
        code.erase(code.begin());
    }
    cout << endl << "code = " << code;

    //-------------------3 point-------------------
    ind = false;
    string decod = "0";
    clock_t start;
    start = clock();
    long double t = 0;
    int min = 0;
    int hour = 0;

    //перебор ключей + счетчик времени
    while (true) {
        //cout << decod << endl;
        t = (clock() - start) / (double)CLOCKS_PER_SEC;

        if (t > 60) {
            min++;
            t = 0;
        }
        if (min == 60) {
            hour++;
            min = 0;
        }

        if (decod == code) {
            cout << "\n\nЖЕВАТЬ КАРТОН БЕЗ ХЛЕБА, НЕУЖЕЛИ ОНО ЗАКОНЧИЛОСЬ???????????" << endl;
            break;
        }
        for (int j = decod.size() - 1; j >= 0; j--) {
            //уменьшаем разрядность
            if (j == 0 && decod[j] == 57) {
                decod[j] = 48;
                decod.insert(decod.begin(), 49);
                break;
            }
            //возвращаем единицу, которую забрали
            else {
                decod[j] = ((decod[j] + 1) % 48 % 10) + 48;
                if (decod[j] != 48) {
                    break;
                }
            }
        }
    }
    cout << "\ndecode = " << decod << endl << "with time = "
        << hour << " hours "
        << min << " minutes "
        << fixed << setprecision(10) << t << " seconds " << endl;

    system("pause");
}
