#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <string>
#include "mybt.h"

bt_t B;
int boardwidth = 0;
int boardheight = 0;
bool white_turn = true;

#ifndef VERBOSE_IDS_PLAYER
#define VERBOSE_IDS_PLAYER
bool verbose = true;
bool showboard_at_each_move = true;
bool show_final_board = true;
#endif

void dls(const bt_t& state, int depth, std::vector<bt_move_t>& path, std::vector<bt_move_t>& bestPath, int& bestScore, bool maxPlayer);
bool ids(const bt_t& state, int maxDepth, bt_move_t& bestMove);
bt_move_t selectMove();

void newgame();
void genmove();
void play(char a, char b, char c, char d);
void showboard();

void help() {
  fprintf(stderr, "  quit\n");
  fprintf(stderr, "  echo ON | OFF\n");
  fprintf(stderr, "  help\n");
  fprintf(stderr, "  name <PLAYER_NAME>\n");
  fprintf(stderr, "  newgame <NBCOL> <NBLINE>\n");
  fprintf(stderr, "  genmove\n");
  fprintf(stderr, "  play <L0C0L1C1>\n");
  fprintf(stderr, "  showboard\n");
}
void name() {
  printf("= rand_player\n\n");
}
void newgame() {
  if((boardheight < 1 || boardheight > 10) && (boardwidth < 1 || boardwidth > 10)) {
    fprintf(stderr, "boardsize is %d %d ???\n", boardheight, boardwidth);
    printf("= \n\n");
    return;
  }
  B.init(boardheight, boardwidth);
  white_turn = true;
  if(verbose) fprintf(stderr, "ready to play on %dx%d board\n", boardheight, boardwidth);
  printf("= \n\n");
}
void showboard() {
  B.print_board(stderr);
  printf("= \n\n");
}
void genmove() {
  int ret = B.endgame();
  if(ret != EMPTY) {
    fprintf(stderr, "game finished\n");
    if(ret == WHITE) fprintf(stderr, "white player wins\n");
    else fprintf(stderr, "black player wins\n");
    printf("= \n\n");
    return;
  }
  bt_move_t m = selectMove();
  B.play(m);
  if(verbose) {
    m.print(stderr, white_turn, B.nbl);
    fprintf(stderr, "\n");
  }
  white_turn = !white_turn;
  printf("= %s\n\n", m.tostr(B.nbl).c_str());
}
void play(char a, char b, char c, char d) {
  bt_move_t m;
  m.line_i = boardheight-(a-'0');
  m.col_i = b-'a';
  m.line_f = boardheight-(c-'0');
  m.col_f = d-'a';
  if(B.can_play(m)) {
    B.play(m);
    if(verbose) {
      m.print(stderr, white_turn, B.nbl);
      fprintf(stderr, "\n");
    }
    white_turn = !white_turn;
  } else {
    fprintf(stderr, "CANT play %d %d %d %d ?\n", m.line_i, m.col_i, m.line_f, m.col_f);
  }
  if(showboard_at_each_move) showboard();
  printf("= \n\n");
}
int main(int _ac, char** _av) {
  bool echo_on = false;
  setbuf(stdout, 0);
  setbuf(stderr, 0);
  if(verbose) fprintf(stderr, "rand_player started\n");
  char a,b,c,d; // for play cmd
  for (std::string line; std::getline(std::cin, line);) {
    if(verbose) fprintf(stderr, "rand_player receive %s\n", line.c_str());
    if(echo_on) if(verbose) fprintf(stderr, "%s\n", line.c_str());
    if(line.compare("quit") == 0) { printf("= \n\n"); break; }
    else if(line.compare("echo ON") == 0) echo_on = true;
    else if(line.compare("echo OFF") == 0) echo_on = false;
    else if(line.compare("help") == 0) help();
    else if(line.compare("name") == 0) name();
    else if(sscanf(line.c_str(), "newgame %d %d\n", &boardheight, &boardwidth) == 2) newgame();
    else if(line.compare("genmove") == 0) genmove();
    else if(sscanf(line.c_str(), "play %c%c%c%c\n", &a,&b,&c,&d) == 4) play(a,b,c,d);
    else if(line.compare("showboard") == 0) showboard();
    else if(line.compare(0,2,"//") == 0) ; // just comments
    else fprintf(stderr, "???\n");
    if(echo_on) printf(">");
  }
  if(verbose) fprintf(stderr, "bye.\n");

  return 0;
}


void dls(const bt_t& state, int depth, std::vector<bt_move_t>& path, std::vector<bt_move_t>& bestPath, int& bestScore, bool maxPlayer) {
  if (depth == 0 || const_cast<bt_t&>(state).is_terminal()) {
    int score = const_cast<bt_t&>(state).eval();
    if (score > bestScore) {
      bestScore = score;
      bestPath = path;
    }
    return;
  }
  std::vector<bt_move_t> moves = const_cast<bt_t&>(state).get_possible_moves();
  for (auto& move : moves) {
    const_cast<bt_t&>(state).play(move);
    path.push_back(move);
    dls(state, depth - 1, path, bestPath, bestScore, !maxPlayer);
    path.pop_back();
    const_cast<bt_t&>(state).undo();
  }
}

bool ids(const bt_t& state, int maxDepth, bt_move_t& bestMove) {
  std::vector<bt_move_t> bestPath;
  int bestScore = INT_MIN;
  for (int depth = 1; depth <= maxDepth; ++depth) {
    std::vector<bt_move_t> path;
    dls(state, depth, path, bestPath, bestScore, true);
    if (bestScore == INT_MAX) {
      bestMove = bestPath[0];
      return true;
    }
  }
  bestMove = bestPath[0];
  return true;
}

bt_move_t selectMove() {
  bt_move_t bestMove;
  ids(B, 10, bestMove);
  return bestMove;
}


