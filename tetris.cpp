#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

#include <termios.h>
#include <unistd.h>

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
  if (read(0, &buf, 1) < 0) {
  } // Lê 1 caractere
  tcsetattr(0, TCSADRAIN, &old); // Restaura o terminal
  return buf;
}
void limpar_tela() { cout << "\033[2J\033[H"; }

const int height = 20;
const int width = 20;
vector<vector<char>> board(height, vector<char>(width, ' '));

void initBoard() {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (j % 2 == 1)
        board[i][j] = '.';
    }
  }
}

void drawBoard() {
  limpar_tela();
  cout << "===== TETRIS NATIVO =====\n";
  for (int i = 0; i < height; i++) {
    cout << "<!";
    for (int j = 0; j < width; j++) {
      cout << board[i][j];
    }
    cout << "!>\n";
  }
  cout << "<!";
  for (int i = 0; i < width; i++) cout << '=';
  cout << "!>\n  ";
  for (int i = 0; i < width; i++) cout << (i%2==0? "\\" : "/");
  cout << "\n";
}

int main() {
  initBoard();
  drawBoard();
  return 0;
}
