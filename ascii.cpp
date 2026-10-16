#include <bits/stdc++.h>
#include <chrono>
#include <ios>
#include <string>
#include <thread>
#include <vector>
using namespace std;
map <char, vector<string>> dict = {
	{'0', {"#####", "#   #", "#   #", "#   #", "#####"}},
    {'1', {"  ## ", " # # ", "#  # ", "   # ", "#####"}},
    {'2', {"#####", "#   #", "  ## ", " #   ", "#####"}},
    {'3', {"#####", "    #", " ####", "    #", "#####"}},
    {'4', {"  ## ", " # # ", "#####", "   # ", "   # "}},
    {'5', {"#####", "#    ", "#####", "    #", "#####"}},
    {'6', {"#####", "#    ", "#####", "#   #", "#####"}},
    {'7', {"#####", "    #", "   # ", "  #  ", " #   "}},
    {'8', {"#####", "#   #", "#####", "#   #", "#####"}},
    {'9', {"#####", "#   #", "#####", "    #", "    #"}},
    {':', {" ", "o", " ", "o", " "}}

};
void limpar_tela(){
    #if (defined(_WIN32) || defined(_WIN64))
        system("cls");
    #else
        system("clear");
    #endif
}
void drawNum(string num){
    vector<string> lin(5, "");
    for (char x : num){
        int i = 0;
        for (auto s : dict[x]){
            lin[i] += s + " ";
            i++;
        }
    }
    for (auto s : lin){
        cout << s << endl;
    }
}
void cronometro(){
    int n, i = 0;
    cout << "========= Cronometro =========\n";
    cout << "Insira um valor: ";
    cin >> n;

    while(i < n){
        string num = to_string(i);
        drawNum(num);
        this_thread::sleep_for(chrono::milliseconds(500));
        limpar_tela();
        i++;
    }
}
string conv(int h, int m, int s){
    vector<string> aux(3);
    aux[0] = to_string(h);
    aux[1] = to_string(m);
    aux[2] = to_string(s);
    for (string &t : aux){
        if ((int) t.size() == 1)
            t = "0" + t;
    }
    string num = aux[0] + ':' + aux[1] + ':' + aux[2];
    return num;
}
void horas(){
    cout << "========= Horario =========\n";

    int h = 0, m = 0, s = 0;
    while (true){
        string num = conv(h, m, s);
        drawNum(num);
        this_thread::sleep_for(chrono::milliseconds(500));
        limpar_tela();
        s++;
        if (s >= 60){
            m++;
            s = 0;
        }
        if (m >= 60){
            h++;
            m = 0;
        }

        if (h >= 24)
            h = 0;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cout << unitbuf;
    cin.tie(NULL);
    string OP;
    cout << "1. para abrir cronometro\n";
    cout << "2. para abrir horario\n";
    cin >> OP;
    if (OP == "1")
        cronometro();
    else if (OP == "2")
        horas();
    return 0;
}