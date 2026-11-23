#include <bits/stdc++.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

bool kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}

int gridX = 32;
int speed = 1;

void printGrid(vector<vector<char>> grid, deque<pair<int, int>> player){
  for (auto [X, Y] : player){
    grid[X][Y] = 'O';
  }
  for (int i = 0; i < gridX; i++){
    for (int j = 0; j < gridX; j++){
      cout << grid[i][j] << " ";
    }
    cout << "\n";
  }
}

void caminhar(deque<pair<int, int>>& player, char motion){
  auto [X, Y] = player.front();
  player.pop_back();
  if (motion == 'd'){
    Y++;
    if (Y == gridX)
      Y = 0;
  }
  else if (motion == 'a'){
    Y--;
    if (Y == -1)
      Y = gridX-1;
  }
  else if (motion == 'w'){
    X--;
    if (X == -1)
      X = gridX-1;
  }
  else if (motion == 's'){
    X++;
    if (X == gridX)
      X = 0;
  }
  player.push_front({X, Y});
}

void limparTela() {
  std::cout << "\033[2J\033[1;1H";
}


int main(){
  vector<vector<char>> grid(gridX, vector<char>(gridX, '.'));
  deque<pair<int, int>> player = {{16, 16}, {16, 15}};
  char motion = 'd';
  while (true){
    printGrid(grid, player);
    if(kbhit()){
      motion = getchar();
    }
    caminhar(player, motion);
    usleep(150000);
    limparTela();
  }
}
