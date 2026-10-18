#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

#include <unistd.h>
#include <termios.h>

// Códigos de Cores ANSI
const string RESET   = "\033[0m";
const string SHINY = "\033[93m"; // Tom de amarelo mais vivo para itens
const string VERDE   = "\033[32m";
const string AZUL    = "\033[34m";
const string CINZA   = "\033[90m";
const string AMARELO = "\033[33m";
const string VERMELHO= "\033[31m";

// Elementos do Jogo
const char ESTRELA = '*';
const char CHAO    = '.';
const char PAREDE  = '#'; // Ou utilize bloco sólido '█'
const char AGUA    = '~';
const char ARVORE  = 'T';
const char JOGADOR = 'X';

const int width = 100, height = 100;
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

struct Pos{
	int X;
	int Y;
};
vector<vector<char>> canvas(height, vector<char>(width, '.'));
void gerarMapa() {
    srand(time(0));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                canvas[i][j] = PAREDE;
            } else {
                int r = rand() % 100;
                if (r < 5) canvas[i][j] = ARVORE;
                else if (r < 8) canvas[i][j] = AGUA;
                else if (r < 10) canvas[i][j] = PAREDE;
                else canvas[i][j] = CHAO;
            }
        }
    }
}
void gerarEstrelas(){
    int e = 0;
    while (e < 3){
        int randX = rand() % width;
        int randY = rand() % height;
        if (canvas[randY][randX] == CHAO){
            canvas[randY][randX] = ESTRELA;
            e++;
        }
    }
}
void drawCanvas(Pos posicao){
	pair<Pos, Pos> range;
	int range_valX = 20, range_valY = 10;
	auto [X, Y] = posicao;
	int &x1 = range.first.X, &x2 = range.second.X;
	int &y1 = range.first.Y, &y2 = range.second.Y;

	x1 = X-range_valX; x2 = X+range_valX;
	if (X-range_valX < 0){
		x1 = 0; x2 = 2*range_valX;
	}
	else if (X+range_valX > width-1){
		x1 = width-(2*range_valX); x2 = width-1; 
	}

	y1 = Y-range_valY; y2 = Y+range_valY;
	if (Y-range_valY < 0){
		y1 = 0; y2 = 2*range_valY;
	}
	else if (Y+range_valY > height-1){
		y1 = height-(2*range_valY); y2 = height-1; 
	}
	for (int i = y1; i <= y2; i++){
		for (int j = x1; j <= x2; j++){
			if (i == Y && j == X)
				cout << VERMELHO << 'X' << RESET;
            else {
                char tile = canvas[i][j];
                switch(tile) {
                    case PAREDE: cout << CINZA << PAREDE << RESET; break;
                    case ARVORE: cout << VERDE << ARVORE << RESET; break;
                    case AGUA:   cout << AZUL << AGUA << RESET; break;
                    case ESTRELA:cout << SHINY << ESTRELA << RESET; break;
                    default: cout << CHAO; break;
                }
            }
		}
		cout << "\n";
	}
}
int main() {
    gerarMapa();
    gerarEstrelas();
    Pos spawn = {width / 2, height / 2};
    Pos posicao = spawn;
    int score = 0;
    
    drawCanvas(posicao);
    cout << "\nScore: " << score << "\n";
    bool running = true;
    
    while (running){
        limpar_tela();
        cout << "Movimento: WASD | Attack: [ESPACO] | Guia: G | Voltar ao Menu: Q\n\n";
        
        drawCanvas(posicao);
        cout << "\nScore: " << score << "\n";

        int &posX = posicao.X;
        int &posY = posicao.Y;
        
        char acao = getch();
        switch (acao){
        case 'w': case 'W': 
            if (posY > 0 && (canvas[posY-1][posX] == CHAO || canvas[posY-1][posX] == ESTRELA)) 
                posY--; 
            break;
        case 'a': case 'A':
            if (posX > 0 && (canvas[posY][posX-1] == CHAO || canvas[posY][posX-1] == ESTRELA))
                posX--;
            break;
        case 's': case 'S':
            if (posY < height-1 && (canvas[posY+1][posX] == CHAO || canvas[posY+1][posX] == ESTRELA))
                posY++; 
            break;
        case 'd': case 'D':
            if (posX < width-1 && (canvas[posY][posX+1] == CHAO || canvas[posY][posX+1] == ESTRELA))
                posX++; 
            break;
        case ' ': 
            break;
        case 'c': case 'C':
            break;
        case 'q': case 'Q':
            running = false;
            break;
        }
    }

    return 0;
}
