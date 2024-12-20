#ifndef MYBT_H
#define MYBT_H
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <random>
#include <vector>
#define WHITE 0
#define BLACK 1
#define EMPTY 2
#define INT_MIN -9999
#define INT_MAX 9999
char* cboard = (char*)"o@.";

// print black in red (as bg is black... black is printed in red)
// comment the following #define USE_COLOR to print without color
#define USE_COLOR

struct bt_piece_t {
  int line; int col;
};
struct bt_move_t {
  int line_i; int col_i;
  int line_f; int col_f;

  // all moves are printed without ambiguity
  // white in its color
  // black in red color
  void print(FILE* _fp, bool _white, int _nbl) {
    if(_white) {
      fprintf(_fp, "%d%c%d%c", _nbl-line_i, 'a'+col_i, _nbl-line_f, 'a'+col_f);
    } else {
#ifdef USE_COLOR
      fprintf(_fp, "\x1B[31m%d%c%d%c\x1B[0m", _nbl-line_i, 'a'+col_i, _nbl-line_f, 'a'+col_f);
#else
      fprintf(_fp, "%d%c%d%c", _nbl-line_i, 'a'+col_i, _nbl-line_f, 'a'+col_f);
#endif /* USE_COLOR */
    }
  }
  std::string tostr(int _nbl) {
    char ret[16];
    snprintf(ret, sizeof(ret), "%d%c%d%c", _nbl-line_i, 'a'+col_i, _nbl-line_f, 'a'+col_f);
    return std::string(ret);
  }
};

// alloc default 10x10
// standard game in 8x8
#define MAX_LINES 10
#define MAX_COLS 10

// rules reminder :
// pieces moves from 1 square in diag and in front
// pieces captures only in diag
// i.e. to go forward, square must be empty

struct bt_state_t {
  int board[MAX_LINES][MAX_COLS];
    int turn;
    bt_piece_t white_pieces[2*MAX_LINES];
    int nb_white_pieces;
    bt_piece_t black_pieces[2*MAX_LINES];
    int nb_black_pieces;
};

std::vector<bt_state_t> history;

struct bt_t {
  int nbl;
  int nbc;
  int board[MAX_LINES][MAX_COLS];
  int turn;

  bt_piece_t white_pieces[2*MAX_LINES];
  int nb_white_pieces;
  bt_piece_t black_pieces[2*MAX_LINES];
  int nb_black_pieces;
  bt_move_t moves[3*2*MAX_LINES];
  int nb_moves;
  // last turn of moves update
  int turn_of_last_moves_update;

  void init(int _nbl, int _nbc);
  void init_pieces();
  void print_board(FILE* _fp);
  void print_turn_and_moves(FILE* _fp);
  void update_moves();
  void update_moves(int _color);
  
  bool white_can_move_right(int _line, int _col);
  bool white_can_move_forward(int _line, int _col);
  bool white_can_move_left(int _line, int _col);
  bool black_can_move_right(int _line, int _col);
  bool black_can_move_forward(int _line, int _col);
  bool black_can_move_left(int _line, int _col);

  bt_move_t get_rand_move();
  bool can_play(bt_move_t _m);
  void play(bt_move_t _m);
  int endgame();
  double score(int _color);
  void playout(bool _log);
  bool is_terminal();
  void apply_move(bt_move_t _m);
      
  // déclarées mais non définies
  double eval();
  void undo();
  bt_move_t minimax(double _sec);
  bt_move_t alphabeta(double _sec);
  int minimax_depth(int turn, int depth, bool maximizingPlayer);
  int alphabeta_depth(int turn, int depth, int alpha, int beta, bool maximizingPlayer);
  bt_move_t mcts(double _sec);
  bt_move_t mcts_ppa(double _sec);
  bt_move_t nmcs(double _sec);
  bt_move_t nrpa(double _sec);

  void saveCurrentState();
  void restoreLastState();

  void add_move(int _li, int _ci, int _lf, int _cf) {
    moves[nb_moves].line_i = _li; moves[nb_moves].col_i = _ci;
    moves[nb_moves].line_f = _lf; moves[nb_moves].col_f = _cf;
    nb_moves++;
  }

  std::vector<bt_move_t> get_possible_moves() {
    std::vector<bt_move_t> possible_moves;
    update_moves();
    for(int i = 0; i < nb_moves; i++) {
        possible_moves.push_back(moves[i]);
    }
    return possible_moves;
  }
};
  
void bt_t::init(int _nbl, int _nbc) {
  if(_nbl > MAX_LINES || _nbc > MAX_COLS) {
    fprintf(stderr, "ERROR : MAX_LINES or MAX_COLS exceeded\n");
    exit(0);
  }
  nbl = _nbl; nbc = _nbc;
  turn = 0;
  turn_of_last_moves_update = -1;
  for(int i = 0; i < nbl; i++)
    for(int j = 0; j < nbc; j++) {
      if(i <= 1 ) {
        board[i][j] = BLACK;
      } else if(i < _nbl-2) {
        board[i][j] = EMPTY;
      } else {
        board[i][j] = WHITE;
      }
    }
  init_pieces();
  update_moves();
}
void bt_t::init_pieces() {
  nb_white_pieces = 0;
  nb_black_pieces = 0;
  for(int i = 0; i < nbl; i++)
    for(int j = 0; j < nbc; j++) {
      if(board[i][j] == WHITE) {
        white_pieces[nb_white_pieces].line = i;
        white_pieces[nb_white_pieces].col = j;
        nb_white_pieces++;
      } else if(board[i][j] == BLACK) {
        black_pieces[nb_black_pieces].line = i;
        black_pieces[nb_black_pieces].col = j;
        nb_black_pieces++;
      }
    }
}

void bt_t::print_board(FILE* _fp = stderr) {
#ifdef USE_COLOR
  fprintf(_fp, "   \x1B[34m");
  for(int j = 0; j < nbc; j++) {
    fprintf(_fp, "%c ", 'a'+j);
  }
  fprintf(_fp, "\x1B[0m\n");
  for(int i = 0; i < nbl; i++) {
    fprintf(_fp, "\x1B[34m%2d\x1B[0m ", (nbl-i));
    for(int j = 0; j < nbc; j++) {
      if(board[i][j] == BLACK) 
        fprintf(_fp, "\x1B[31m%c\x1B[0m ", cboard[board[i][j]]);
      else
        fprintf(_fp, "%c ", cboard[board[i][j]]);
    }
    fprintf(_fp, "\n");
  }
#else
  fprintf(_fp, "   ");
  for(int j = 0; j < nbc; j++) {
    fprintf(_fp, "%c ", 'a'+j);
  }
  fprintf(_fp, "\n");
  for(int i = 0; i < nbl; i++) {
    fprintf(_fp, "%2d ", (nbl-i));
    for(int j = 0; j < nbc; j++) {
      if(board[i][j] == BLACK) 
        fprintf(_fp, "%c ", cboard[board[i][j]]);
      else
        fprintf(_fp, "%c ", cboard[board[i][j]]);
    }
    fprintf(_fp, "\n");
  }
#endif /* USE_COLOR */
}
void bt_t::print_turn_and_moves(FILE* _fp = stderr) {
  fprintf(_fp,"turn:%d\nmoves:", turn);
  for(int i = 0; i < nb_moves; i++) {
    moves[i].print(_fp, turn%2 == 1, nbl);
    fprintf(_fp, " ");
  }
  fprintf(_fp, "\n");
}
void bt_t::update_moves() {
  if(turn%2 == 0) update_moves(WHITE);
  else update_moves(BLACK);
}
void bt_t::update_moves(int _color) {
  if(turn_of_last_moves_update == turn) return; // MAJ ever done
  turn_of_last_moves_update = turn;
  nb_moves = 0;
  if(_color==WHITE) {
    for(int i = 0; i < nb_white_pieces; i++) {
      int li = white_pieces[i].line;
      int ci = white_pieces[i].col;
      if(white_can_move_right(li, ci)) add_move(li, ci, li-1, ci+1);
      if(white_can_move_forward(li, ci)) add_move(li, ci, li-1, ci);
      if(white_can_move_left(li, ci)) add_move(li, ci, li-1, ci-1);
    }
  } else if(_color == BLACK) {
    for(int i = 0; i < nb_black_pieces; i++) {
      int li = black_pieces[i].line;
      int ci = black_pieces[i].col;
      if(black_can_move_right(li, ci)) add_move(li, ci, li+1, ci+1);
      if(black_can_move_forward(li, ci)) add_move(li, ci, li+1, ci);
      if(black_can_move_left(li, ci)) add_move(li, ci, li+1, ci-1);
    }
  }
}
bool bt_t::white_can_move_right(int _line, int _col) {
  if(_line == 0) return false;
  if(_col == nbc-1) return false;
  if(board[_line-1][_col+1] != WHITE) return true;
  return false;
}
bool bt_t::white_can_move_forward(int _line, int _col) {
  if(_line == 0) return false;
  if(board[_line-1][_col] == EMPTY) return true;
  return false;
}
bool bt_t::white_can_move_left(int _line, int _col) {
  if(_line == 0) return false;
  if(_col == 0) return false;
  if(board[_line-1][_col-1] != WHITE) return true;
  return false;
}
bool bt_t::black_can_move_right(int _line, int _col) {
  if(_line == nbl-1) return false;
  if(_col == nbc-1) return false;
  if(board[_line+1][_col+1] != BLACK) return true;
  return false;
}
bool bt_t::black_can_move_forward(int _line, int _col) {
  if(_line == nbl-1) return false;
  if(board[_line+1][_col] == EMPTY) return true;
  return false;
}
bool bt_t::black_can_move_left(int _line, int _col) {
  if(_line == nbl-1) return false;
  if(_col == 0) return false;
  if(board[_line+1][_col-1] != BLACK) return true;
  return false;
}
bt_move_t bt_t::get_rand_move() {
  update_moves();
  int r = ((int)rand())%nb_moves;
  return moves[r];
}
bool bt_t::can_play(bt_move_t _m) {
  int dx = abs(_m.col_f - _m.col_i);
  if(dx > 1) return false;
  int dy = abs(_m.line_f - _m.line_i);
  if(dy > 1) return false;
  if(_m.line_i < 0 || _m.line_i >= nbl) return false;
  if(_m.line_f < 0 || _m.line_f >= nbl) return false;
  if(_m.col_i < 0 || _m.col_i >= nbc) return false;
  if(_m.col_f < 0 || _m.col_f >= nbc) return false;
  int color_i = board[_m.line_i][_m.col_i];
  int color_f = board[_m.line_f][_m.col_f];
  if(color_i == EMPTY) return false;
  if(color_i == color_f) return false;
  if(turn%2==0 && color_i == BLACK) return false;
  if(turn%2==1 && color_i == WHITE) return false;
  if(_m.col_i == _m.col_f && color_f != EMPTY) return false;
  return true;
}

void bt_t::play(bt_move_t _m) {
  saveCurrentState();
  int color_i = board[_m.line_i][_m.col_i];
  int color_f = board[_m.line_f][_m.col_f];
  board[_m.line_f][_m.col_f] = color_i;
  board[_m.line_i][_m.col_i] = EMPTY;
  if(color_i == WHITE) {
    for(int i = 0; i < nb_white_pieces; i++) {
      if(white_pieces[i].line == _m.line_i && white_pieces[i].col == _m.col_i) {
        white_pieces[i].line = _m.line_f;
        white_pieces[i].col = _m.col_f;
        break;
      }
    }
    if(color_f == BLACK) {
      for(int i = 0; i < nb_black_pieces; i++) {
        if(black_pieces[i].line == _m.line_f && black_pieces[i].col == _m.col_f) {
          black_pieces[i] = black_pieces[nb_black_pieces-1];
          nb_black_pieces--;
          break;
        }
      }
    }
  } else if(color_i == BLACK) {
    for(int i = 0; i < nb_black_pieces; i++) {
      if(black_pieces[i].line == _m.line_i &&
         black_pieces[i].col == _m.col_i) {
        black_pieces[i].line = _m.line_f;
        black_pieces[i].col = _m.col_f;
        break;
      }
    }
    if(color_f == WHITE) {
      for(int i = 0; i < nb_white_pieces; i++) {
        if(white_pieces[i].line == _m.line_f &&
           white_pieces[i].col == _m.col_f) {
          white_pieces[i] = white_pieces[nb_white_pieces-1];
          nb_white_pieces--;
          break;
        }
      }
    }
  }
  turn++;
}
int bt_t::endgame() {
  for(int i = 0; i < nbc; i++) {
    if(board[0][i] == WHITE) return WHITE;
  }
  for(int i = 0; i < nbc; i++) {
    if(board[nbl-1][i] == BLACK) return BLACK;
  }  
  if(nb_black_pieces==0) return WHITE;
  if(nb_white_pieces==0) return BLACK;
  return EMPTY;
}
double bt_t::score(int _color) {
  int state = endgame();
  if(state == EMPTY) return 0.0;
  if(_color == state) return 1.0;
  return -1.0;
}

void bt_t::playout(bool _log) {
  while(endgame() == EMPTY) {
    bt_move_t m = get_rand_move();
    play(m);
    if(_log) {
      print_board(stderr);
      print_turn_and_moves(stderr);
    }
  }
  if(_log) {
    print_board(stderr);
    print_turn_and_moves(stderr);
  }
}

/// @brief une fonction heuristique pour la variante classique du jeu Breakthrough
double bt_t::eval() {
  int score = 0;
  for(int i = 0; i < nbl; i++) {
    for(int j = 0; j < nbc; j++) {
      if(board[i][j] == WHITE) {
        score += (nbl - i) * 2;
        if(i > 0 && (board[i-1][j] == EMPTY || (j > 0 && board[i-1][j-1] == EMPTY) || (j < nbc-1 && board[i-1][j+1] == EMPTY)))
          score += 5;
      } else if(board[i][j] == BLACK) {
        score -= (i + 1) * 2;
        if(i < nbl-1 && (board[i+1][j] == EMPTY || (j > 0 && board[i+1][j-1] == EMPTY) || (j < nbc-1 && board[i+1][j+1] == EMPTY)))
          score -= 5;
      }
    }
  }
  return score;
}

void bt_t::undo() {
  restoreLastState();
}

void bt_t::saveCurrentState() {
  bt_state_t current_state;
  std::copy(&board[0][0], &board[0][0] + MAX_LINES*MAX_COLS, &current_state.board[0][0]);
  current_state.turn = turn;
  std::copy(&white_pieces[0], &white_pieces[0] + 2*MAX_LINES, &current_state.white_pieces[0]);
  current_state.nb_white_pieces = nb_white_pieces;
  std::copy(&black_pieces[0], &black_pieces[0] + 2*MAX_LINES, &current_state.black_pieces[0]);
  current_state.nb_black_pieces = nb_black_pieces;

  history.push_back(current_state);
}

void bt_t::restoreLastState() {
  if (history.empty()) return;

  bt_state_t last_state = history.back();
  history.pop_back();

  std::copy(&last_state.board[0][0], &last_state.board[0][0] + MAX_LINES*MAX_COLS, &board[0][0]);

  turn = last_state.turn;
  std::copy(&last_state.white_pieces[0], &last_state.white_pieces[0] + 2*MAX_LINES, &white_pieces[0]);
  nb_white_pieces = last_state.nb_white_pieces;
  std::copy(&last_state.black_pieces[0], &last_state.black_pieces[0] + 2*MAX_LINES, &black_pieces[0]);
  nb_black_pieces = last_state.nb_black_pieces;

  update_moves();
}

bool bt_t::is_terminal() {
  return endgame() != EMPTY;
}

void bt_t::apply_move(bt_move_t move) {
  int piece = board[move.line_i][move.col_i];
  board[move.line_f][move.col_f] = piece;
  board[move.line_i][move.col_i] = EMPTY;

  if(piece == WHITE) {
    for(int i = 0; i < nb_white_pieces; ++i) {
      if(white_pieces[i].line == move.line_i && white_pieces[i].col == move.col_i) {
        white_pieces[i].line = move.line_f;
        white_pieces[i].col = move.col_f;
        break;
      }
    }
  } else {
    for(int i = 0; i < nb_black_pieces; ++i) {
      if(black_pieces[i].line == move.line_i && black_pieces[i].col == move.col_i) {
        black_pieces[i].line = move.line_f;
        black_pieces[i].col = move.col_f;
        break;
      }
    }
  }
  turn++;
  update_moves();
}

bt_move_t bt_t::minimax(double _sec) {
  int bestScore = INT_MIN;
  bt_move_t bestMove;
  update_moves();
  int score;
  for (int i = 0; i < nb_moves; i++) {
    bt_move_t move = moves[i];
    play(move);
    score = minimax_depth(turn, 3, false);
    if (score > bestScore) {
      bestScore = score;
      bestMove = move;
    }
    undo();
  }
  return bestMove;
}
int bt_t::minimax_depth(int turn, int depth, bool maximizingPlayer) {
  if (depth == 0 || endgame() != EMPTY) {
    return eval();
  }
  if (maximizingPlayer) {
    int maxEval = INT_MIN;
    update_moves();
    for (int i = 0; i < nb_moves; i++) {
      play(moves[i]);
      int eval = minimax_depth(turn + 1, depth - 1, false);
      maxEval = std::max(maxEval, eval);
      undo();
    }
    return maxEval;
  } else {
    int minEval = INT_MAX;
    update_moves();
    for (int i = 0; i < nb_moves; i++) {
      play(moves[i]);
      int eval = minimax_depth(turn + 1, depth - 1, true);
      minEval = std::min(minEval, eval);
      undo();
    }
    return minEval;
  }
}

bt_move_t bt_t::alphabeta(double _sec) {
  int alpha = INT_MIN;
  int beta = INT_MAX;
  int bestScore = INT_MIN;
  bt_move_t bestMove;
  update_moves();
  int score;
  for (int i = 0; i < nb_moves; i++) {
    bt_move_t move = moves[i];
    play(move);
    score = alphabeta_depth(turn, 3, alpha, beta, false);
    if (score > bestScore) {
      bestScore = score;
      bestMove = move;
    }
    undo();
  }
  return bestMove;
}
int bt_t::alphabeta_depth(int turn, int depth, int alpha, int beta, bool maximizingPlayer) {
  if (depth == 0 || endgame() != EMPTY) {
    return eval();
  }
  if (maximizingPlayer) {
    int maxEval = INT_MIN;
    update_moves();
    for (int i = 0; i < nb_moves; i++) {
      play(moves[i]);
      int eval = alphabeta_depth(turn + 1, depth - 1, alpha, beta, false);
      maxEval = std::max(maxEval, eval);
      alpha = std::max(alpha, eval);
      undo();
      if (beta <= alpha)
        break;
    }
    return maxEval;
  } else {
    int minEval = INT_MAX;
    update_moves();
    for (int i = 0; i < nb_moves; i++) {
      play(moves[i]);
      int eval = alphabeta_depth(turn + 1, depth - 1, alpha, beta, true);
      minEval = std::min(minEval, eval);
      beta = std::min(beta, eval);
      undo();
      if (beta <= alpha)
        break;
    }
    return minEval;
  }
}



#endif /* MYBT_H */
