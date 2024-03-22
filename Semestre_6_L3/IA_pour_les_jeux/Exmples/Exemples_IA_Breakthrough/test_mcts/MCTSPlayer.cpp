#include "mybt.h"
#include <limits>
#include <cmath>
#include <chrono>
#include <vector>
#include <iostream>
#include <algorithm>

const float UCT_K = sqrt(2);

MCTSNode* UCTSelectNode(MCTSNode* node) {
  MCTSNode* bestNode = nullptr;
  double bestValue = -std::numeric_limits<double>::max();

  for (MCTSNode* child : node->children) {
    if (child->visits == 0) continue;
    double uctValue = 
      child->wins / (double)(child->visits + 1e-4) +
      UCT_K * sqrt(log(node->visits + 1) / (double)(child->visits + 1e-4));
    if (uctValue > bestValue) {
      bestValue = uctValue;
      bestNode = child;
    }
  }
  return bestNode;
}

bool simulateGame(bt_t& board) {
  bt_t tempBoard = board;
  while (tempBoard.endgame() == EMPTY) {
    bt_move_t move = tempBoard.get_rand_move();
    tempBoard.play(move);
  }
  return tempBoard.score(board.turn) > 0;
}

void expandNode(MCTSNode* node, bt_t& board) {
  if (node->children.empty() && board.nb_moves > 0) {
    board.update_moves();
    for (int i = 0; i < board.nb_moves; ++i) {
      bt_t newBoard = board;
      newBoard.play(board.moves[i]);
      MCTSNode* newNode = new MCTSNode(newBoard);
      newNode->parent = node;
      node->children.push_back(newNode);
    }
  }
}

bt_move_t mcts(bt_t& rootBoard, double timeLimit) {
  MCTSNode root(rootBoard);
  auto startTime = std::chrono::high_resolution_clock::now();

  while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count() < timeLimit) {
    MCTSNode* node = &root;
    bt_t board = rootBoard;

    while (!node->children.empty()) {
      node = UCTSelectNode(node);
      board.play(node->board.moves[0]);
    }

    expandNode(node, board);

    bool result = simulateGame(board);

    while (node != nullptr) {
      node->visits++;
      if (result) node->wins++;
      node = node->parent;
    }
  }

  MCTSNode* bestNode = UCTSelectNode(&root);
  return bestNode->board.moves[0];
}

int main() {
  bt_t board;
  double timeLimit = 1.0;
  bt_move_t bestMove = mcts(board, timeLimit);
  std::cout << "Best move: ";
  std::cout << std::endl;
  return 0;
}
