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
    {'9', {"#####", "#   #", "#####", "    #", "    #"}}

};
void limpar_tela(){
    #if (defined(_WIN32) || defined(_WIN64))
        system("cls");
    #else
        system("clear");
    #endif
}
void drawNum(int n){
    string num = to_string(n);
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
int main() {
    ios_base::sync_with_stdio(false);
    cout << unitbuf;
    cin.tie(NULL);
    
    int n; cin >> n;
    while(n < 10){
        drawNum(n);
        this_thread::sleep_for(chrono::milliseconds(500));
        limpar_tela();
        n++;
    }
    return 0;
}