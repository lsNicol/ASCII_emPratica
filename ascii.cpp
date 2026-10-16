#include <bits/stdc++.h>
#include <chrono>
#include <ios>
#include <string>
#include <thread>
#include <vector>
#include <unistd.h>
#include <termios.h>

using namespace std;

const int HEIGHT = 20;
const int WIDTH = 40;
vector<vector<char>> canvas(HEIGHT, vector<char>(WIDTH, '.'));

char getch() {
    char buf = 0;
    struct termios old = {0};
    tcgetattr(0, &old);
    
    struct termios current = old;
    current.c_lflag &= ~ICANON; // Desativa o buffer de linha
    current.c_lflag &= ~ECHO;   // Não mostra a tecla digitada
    current.c_cc[VMIN] = 1;
    current.c_cc[VTIME] = 0;
    
    tcsetattr(0, TCSANOW, &current);
    if (read(0, &buf, 1) < 0) {} // Lê 1 caractere
    tcsetattr(0, TCSADRAIN, &old); // Restaura o terminal
    return buf;
}

void limpar_tela(){
    cout << "\033[2J\033[H";
}

void drawCanvas(int mseY, int mseX){
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            if (i == mseY && j == mseX)
                cout << 'X';
            else
                cout << canvas[i][j];
        }
        cout << "\n";
    }
}

void guidePinceis(){
    cout << "\n---------------------------------------------------------\n";
    
    cout << "1. CONTORNOS E LINHAS (Desenhos de Traço)\n";
    cout << "   Opções: _  -  |  /  \\  (  )  [  ]  '  ,  .\n\n";
    
    cout << "2. PREENCHIMENTO, LUZ E SOMBRA (Estilo Block/Grayscale)\n";
    cout << "   [Espaço] (Luz máxima)\n";
    cout << "   .  ,  (Leve)\n";
    cout << "   -  =  +  *  (Média)\n";
    cout << "   %  &  #  @  (Pesada/Escura)\n";
    cout << "---------------------------------------------------------\n";
    cout << "Digite DIRETAMENTE o caractere que deseja usar como pincel\n";
    cout << "(Ou pressione [ESPAÇO] para pincel vazio / 'Q' para cancelar): ";
}
deque<char> historico = {'#'};
void addHistorico(char op){
    if (!historico.empty() && historico.front() == op)
        return;
    historico.push_front(op);
    if (historico.size() > 5)
        historico.pop_back();
}
char changeBrush(){
    limpar_tela();
    cout << "=================== SELEÇÃO DE PINCEL ===================\n\n";
    cout << "Recentes:\n";
    for (char p : historico)
        cout << "["<< p << "] ";
    char op;
    cout << "Insira o pincel a ser utilizado (':' - guia):\n";
    op = getch();
    while (op == ':'){
        guidePinceis();
        op = getch();
    }
    if (op == 'q' || op == 'Q')
        return historico.front();
    addHistorico(op);
    return op;

}
void Paint() {
    int mseX = WIDTH / 2;
    int mseY = HEIGHT / 2;
    bool running = true;
    char brush = historico.front();
    
    fill(canvas.begin(), canvas.end(), vector<char>(WIDTH, '.'));

    while (running){
        limpar_tela();
        cout << "===================== PAINT NATIVO =====================\n";
        cout << "Movimento: WASD | Desenhar: [ESPACO] | Limpar: C | Voltar ao Menu: Q\n\n";
        drawCanvas(mseY, mseX);
        cout << "\nPincel Atual: [" << brush << "] -> Aperte [R] para trocar\n";

        char acao = getch();
        
        switch (acao){
        case 'R': case 'r':
            brush = changeBrush();
            break;
        case 'w': case 'W': 
            if (mseY > 0) 
                mseY--; 
            break;
        case 'a': case 'A':
            if (mseX > 0)
                mseX--;
            break;
        case 's': case 'S':
            if (mseY + 1 < HEIGHT)
                mseY++; 
            break;
        case 'd': case 'D':
            if (mseX + 1 < WIDTH)
                mseX++; 
            break;
        case ' ': 
            canvas[mseY][mseX] = brush;
            break;
        case 'c': case 'C':
            canvas[mseY][mseX] = '.';
            break;
        case 'q': case 'Q':
            running = false;
            break;
        }
    }
}

//Numero em ASCII
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
    cout << "3. para abrir Paint\n";
    cin >> OP;
    if (OP == "1")
        cronometro();
    else if (OP == "2")
        horas();
    else if (OP == "3")
        Paint();
    return 0;
}