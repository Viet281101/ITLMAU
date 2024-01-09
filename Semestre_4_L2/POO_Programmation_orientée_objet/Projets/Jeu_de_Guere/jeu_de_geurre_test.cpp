
#include <iostream>
#include <vector>

// Classe pour représenter un pion
class Pawn {
public:
    enum class Type { Castle, Warrior, Peasant, Lord };

    Pawn(Type type, bool isRed) : type(type), isRed(isRed) {
        switch (type) {
            case Type::Castle:
                power = 0;
                maxHP = 20;
                maxMovement = 0;
                production = 2;
                cost = 15;
                break;
            case Type::Warrior:
                power = 5;
                maxHP = 10;
                maxMovement = 3;
                production = 0;
                cost = 10;
                break;
            case Type::Peasant:
                power = 0;
                maxHP = 1;
                maxMovement = 2;
                production = 5;
                cost = 20;
                break;
            case Type::Lord:
                power = 3;
                maxHP = 5;
                maxMovement = 1;
                production = 0;
                cost = 10;
                break;
        }
        HP = maxHP;
    }

    Type getType() const {
        return type;
    }

    bool isRedPlayer() const {
        return isRed;
    }

    int getPower() const {
        return power;
    }

    int getHP() const {
        return HP;
    }

    int getMaxHP() const {
        return maxHP;
    }

    int getMaxMovement() const {
        return maxMovement;
    }

    int getProduction() const {
        return production;
    }

    int getCost() const {
        return cost;
    }

private:
    Type type;
    bool isRed;
    int power;
    int HP;
    int maxHP;
    int maxMovement;
    int production;
    int cost;
};

// Classe pour représenter un joueur
class Player {
public:
    Player(const std::string& playerName, bool isRed) : name(playerName), isRed(isRed), gold(0) {
	    // Ajouter le château initial du joueur
	    Pawn* castle = new Pawn(Pawn::Type::Castle, isRed);
	    pawns.push_back(castle);
    }

    bool isRedPlayer() const {
        return isRed;
    }

    int getGold() const {
        return gold;
    }

    void setGold(int value) {
        gold = value;
    }

    void addGold(int amount) {
        gold += amount;
    }

	bool castleDestroyed() const {
	    for (const auto& pawn : pawns) {
	        if (pawn->getType() == Pawn::Type::Castle && pawn->getHP() <= 0) {
	            return true; // Le château du joueur est détruit
	        }
	    }
	    return false; // Le château du joueur est intact
	}


private:
    std::string name; // Membre pour stocker le nom du joueur
    std::vector<Pawn*> pawns; // Membre pour stocker les pions du joueur
    bool isRed;
    int gold;
};


// Classe pour représenter le plateau de jeu
class GameBoard {
public:

    int getCurrentPlayer() const {
        return currentPlayer;
    }

    void nextPlayer() {
        currentPlayer = (currentPlayer + 1) % players.size();
    }

    GameBoard() : size(20), currentPlayer(0) {
	    board.resize(size, std::vector<Pawn*>(size, nullptr));
	    // Ajouter les joueurs au plateau de jeu
	    players.emplace_back("Joueur 1", true);
	    players.emplace_back("Joueur 2", false);
	}


    ~GameBoard() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                delete board[i][j];
            }
        }
    }

    bool isGameOver() const {
        return players[0].castleDestroyed() || players[1].castleDestroyed();
    }

    void printBoard() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] != nullptr) {
                    Pawn* pawn = board[i][j];
                    char symbol = ' ';
                    switch (pawn->getType()) {
                        case Pawn::Type::Castle:
                            symbol = 'C';
                            break;
                        case Pawn::Type::Warrior:
                            symbol = 'W';
                            break;
                        case Pawn::Type::Peasant:
                            symbol = 'P';
                            break;
                        case Pawn::Type::Lord:
                            symbol = 'L';
                            break;
                    }
                    if (pawn->isRedPlayer()) {
                        symbol = std::tolower(symbol);
                    }
                    std::cout << symbol;
                } else {
                    std::cout << '-';
                }
                std::cout << ' ';
            }
            std::cout << std::endl;
        }
    }

    bool isValidMove(int row, int col, int newRow, int newCol) const {
        if (row < 0 || row >= size || col < 0 || col >= size || newRow < 0 || newRow >= size || newCol < 0 || newCol >= size) {
            return false; // Vérifier que les indices sont valides
        }

        Pawn* pawn = board[row][col];
        if (pawn == nullptr) {
            return false; // Vérifier qu'il y a bien un pion à déplacer
        }

        if (board[newRow][newCol] != nullptr) {
            return false; // Vérifier que la case de destination est vide
        }

        if (abs(newRow - row) + abs(newCol - col) > pawn->getMaxMovement()) {
            return false; // Vérifier que la case de destination est atteignable par le pion
        }

        return true;
    }

    void movePawn(int row, int col, int newRow, int newCol) {
        if (!isValidMove(row, col, newRow, newCol)) {
            return; // Sortir si le déplacement n'est pas valide
        }

        Pawn* pawn = board[row][col];
        board[row][col] = nullptr;
        board[newRow][newCol] = pawn;
    }

    // Le reste des fonctions à implémenter

private:
    int size;
    std::vector<std::vector<Pawn*>> board;
    std::vector<Player> players;
    int currentPlayer;
};



int main() {
    // Initialiser le plateau de jeu et les joueurs
    GameBoard gameBoard;

    while (!gameBoard.isGameOver()) {
        // Afficher l'état du jeu
        gameBoard.printBoard();

        // Demander au joueur courant d'entrer son mouvement
        int row, col, newRow, newCol;
        std::cout << "Joueur " << (gameBoard.getCurrentPlayer() + 1) << ", entrez votre mouvement (ligne colonne nouvelle_ligne nouvelle_colonne) : ";
        std::cin >> row >> col >> newRow >> newCol;

        // Effectuer le mouvement
        gameBoard.movePawn(row, col, newRow, newCol);

        // Passer au joueur suivant
        gameBoard.nextPlayer();
    }

    // Afficher le résultat du jeu
    std::cout << "Le joueur " << (gameBoard.getCurrentPlayer() + 1) << " a perdu !" << std::endl;

    return 0;
}



