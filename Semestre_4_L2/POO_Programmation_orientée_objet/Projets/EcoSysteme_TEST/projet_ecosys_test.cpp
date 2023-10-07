

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

enum Entity {
    EMPTY, GRASS, SHEEP, WOLF, MINERAL_SALT
};

struct Position {
    int row;
    int col;
};

char intToAsciiChar(int number) {
    return (char('0' + number) + 17);
};

class Universe {
public:
    Universe(int rows, int cols, int numSheep, int numWolves)
        : rows_(rows), cols_(cols), numSheep_(numSheep), numWolves_(numWolves), tour_(0)
    {
        // Initialize the universe with empty cells
        grid_.resize(rows_, std::vector<Entity>(cols_, EMPTY));

        // // Place grass on each cell
        // for (int i = 0; i < rows_; ++i) {
        //     for (int j = 0; j < cols_; ++j) {
        //         grid_[i][j] = GRASS;
        //     }
        // }

        // Place sheep randomly
        for (int i = 0; i < numSheep_; ++i) {
            Position pos = getRandomEmptyCell();
            if (pos.row != -1 && pos.col != -1) {
                grid_[pos.row][pos.col] = SHEEP;
            }
        }

        // Place wolves randomly
        for (int i = 0; i < numWolves_; ++i) {
            Position pos = getRandomEmptyCell();
            if (pos.row != -1 && pos.col != -1) {
                grid_[pos.row][pos.col] = WOLF;
            }
        }
    }

    void runSimulation() {
        do {
            printUniverse();
            std::cout << "Tour " << tour_ << " | Loups : " << numWolves_ << " | Moutons : " << numSheep_ << std::endl;
            std::cout << std::endl;

            if (numWolves_ == 0 && numSheep_ == 0) {
                std::cout << "L'univers est mort !" << std::endl;
                break;
            }

            simulateOneStep();

            ++tour_;

            std::cout << "1. Continuer jusqu'au tour suivant" << std::endl;
            std::cout << "2. Quitter" << std::endl;
            std::cout << "Choix : ";
            int choice;
            std::cin >> choice;

            // Vider le tampon d'entrée
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (choice == 2) {
                break;
            }
        } while (true);
    }

private:
    std::vector<std::vector<Entity>> grid_;
    int rows_;
    int cols_;
    int numSheep_;
    int numWolves_;
    int tour_;

    void printUniverse() {
        std::cout << std::endl;
        std::cout << std::endl << "//////////////////////////////////////////" << std::endl;
        std::cout << std::endl << "    1   2   3   4   5   6   7   8   9   10" << std::endl;
        for (int i = 0; i < rows_; ++i) {
            std::cout << "  +---+---+---+---+---+---+---+---+---+---+" << std::endl;
            std::cout << char(intToAsciiChar(i)) << " |";
            for (int j = 0; j < cols_; ++j) {
                switch (grid_[i][j]) {
                    case EMPTY:
                        std::cout << "   |";
                        break;
                    case GRASS:
                        std::cout << " H |";
                        break;
                    case SHEEP:
                        std::cout << " M |";
                        break;
                    case WOLF:
                        std::cout << " L |";
                        break;
                    case MINERAL_SALT:
                        std::cout << " S |";
                        break;
                    default:
                        break;
                }
            }
            std::cout << std::endl;
        }
        std::cout << "  +---+---+---+---+---+---+---+---+---+---+" << std::endl;
        std::cout << std::endl;
    }

    // Position getRandomEmptyCell() {
    //     std::vector<Position> emptyCells;
    //     for (int i = 0; i < rows_; ++i) {
    //         for (int j = 0; j < cols_; ++j) {
    //             if (grid_[i][j] == EMPTY) emptyCells.push_back({i, j});
    //         }
    //     }
    //     if (emptyCells.empty()) return {-1, -1};
    //     int index = std::rand() % emptyCells.size();
    //     return emptyCells[index];
    // }

    Position getRandomEmptyCell() {
        int maxAttempts = rows_ * cols_;  // Nombre maximal de tentatives

        for (int attempt = 0; attempt < maxAttempts; ++attempt) {
            int row = std::rand() % rows_;
            int col = std::rand() % cols_;

            if (grid_[row][col] == EMPTY) {
                return {row, col};  // Retourner les coordonnées de la cellule vide
            }
        }

        return {-1, -1};  // Retourner une valeur indiquant qu'aucune cellule vide n'a été trouvée
    }

    void simulateOneStep() {
        std::vector<Position> sheepPositions;
        std::vector<Position> wolfPositions;

        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                if (grid_[i][j] == SHEEP) {
                    sheepPositions.push_back({i, j});
                } else if (grid_[i][j] == WOLF) {
                    wolfPositions.push_back({i, j});
                }
            }
        }

        // Move sheep
        for (const auto& pos : sheepPositions) {
            moveEntity(pos, SHEEP);
        }

        // Move wolves
        for (const auto& pos : wolfPositions) {
            moveEntity(pos, WOLF);
        }

        // Update grass and check for reproduction and death
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                if (grid_[i][j] == GRASS) {
                    if (grid_[i][j] == MINERAL_SALT) {
                        grid_[i][j] = GRASS;  // Grass regrows after minerals are deposited
                    }
                } else if (grid_[i][j] == SHEEP) {
                    eatGrass({i, j});
                    if (grid_[i][j] == SHEEP) {
                        reproduce({i, j}, SHEEP);
                        checkSheepDeath({i, j});
                    }
                } else if (grid_[i][j] == WOLF) {
                    eatSheep({i, j});
                    if (grid_[i][j] == WOLF) {
                        reproduce({i, j}, WOLF);
                        checkWolfDeath({i, j});
                    }
                }
            }
        }

        // Place mineral salts after death
        for (const auto& pos : sheepPositions) {
            if (grid_[pos.row][pos.col] == EMPTY) {
                grid_[pos.row][pos.col] = MINERAL_SALT;
            }
        }
        for (const auto& pos : wolfPositions) {
            if (grid_[pos.row][pos.col] == EMPTY) {
                grid_[pos.row][pos.col] = MINERAL_SALT;
            }
        }
    }

    void moveEntity(const Position& pos, Entity entity) {
        int newRow = pos.row + std::rand() % 3 - 1;
        int newCol = pos.col + std::rand() % 3 - 1;

        newRow = (newRow + rows_) % rows_;
        newCol = (newCol + cols_) % cols_;

        if (grid_[newRow][newCol] == EMPTY) {
            grid_[newRow][newCol] = entity;
            grid_[pos.row][pos.col] = EMPTY;
        }
    }

	void eatGrass(const Position& pos) {
	    int row = pos.row;
	    int col = pos.col;

	    // Check if there is grass in the neighboring cells
	    for (int i = row - 1; i <= row + 1; ++i) {
	        for (int j = col - 1; j <= col + 1; ++j) {
	            int newRow = (i + rows_) % rows_;
	            int newCol = (j + cols_) % cols_;

	            if (grid_[newRow][newCol] == GRASS) {
	                grid_[newRow][newCol] = EMPTY;  // Remove the grass
	                grid_[row][col] = EMPTY;  // Remove the grass from the current cell of the sheep
	                return;
	            }
	        }
	    }
	}



    void eatSheep(const Position& pos) {
        int row = pos.row;
        int col = pos.col;

        // Check if there is a sheep in the neighboring cells
        for (int i = row - 1; i <= row + 1; ++i) {
            for (int j = col - 1; j <= col + 1; ++j) {
                int newRow = (i + rows_) % rows_;
                int newCol = (j + cols_) % cols_;

                if (grid_[newRow][newCol] == SHEEP) {
                    grid_[newRow][newCol] = EMPTY;  // Remove the sheep
                    --numSheep_;  // Decrease the sheep count
                    return;
                }
            }
        }
    }

    void reproduce(const Position& pos, Entity entity) {
        int row = pos.row;
        int col = pos.col;

        // Check if there is an empty neighboring cell
        for (int i = row - 1; i <= row + 1; ++i) {
            for (int j = col - 1; j <= col + 1; ++j) {
                int newRow = (i + rows_) % rows_;
                int newCol = (j + cols_) % cols_;

                if (grid_[newRow][newCol] == EMPTY) {
                    grid_[newRow][newCol] = entity;  // Place a new entity (sheep or wolf)
                    if (entity == SHEEP) {
                        ++numSheep_;  // Increase the sheep count
                    } else if (entity == WOLF) {
                        ++numWolves_;  // Increase the wolf count
                    }
                    return;
                }
            }
        }
    }

    void checkSheepDeath(const Position& pos) {
        int row = pos.row;
        int col = pos.col;

        // Check if the sheep has no neighboring grass or sheep
        for (int i = row - 1; i <= row + 1; ++i) {
            for (int j = col - 1; j <= col + 1; ++j) {
                if (i == row && j == col) {
                    continue;  // Skip the current cell
                }

                int newRow = (i + rows_) % rows_;
                int newCol = (j + cols_) % cols_;

                if (grid_[newRow][newCol] == GRASS || grid_[newRow][newCol] == SHEEP) {
                    return;  // The sheep is still alive
                }
            }
        }

        grid_[row][col] = EMPTY;  // Remove the dead sheep
        --numSheep_;  // Decrease the sheep count
    }

	void checkWolfDeath(const Position& pos) {
	    int row = pos.row;
	    int col = pos.col;

	    // Check if the wolf has no neighboring sheep
	    for (int i = row - 1; i <= row + 1; ++i) {
	        for (int j = col - 1; j <= col + 1; ++j) {
	            if (i == row && j == col) {
	                continue;  // Skip the current cell
	            }

	            int newRow = (i + rows_) % rows_;
	            int newCol = (j + cols_) % cols_;

	            if (grid_[newRow][newCol] == SHEEP) {
	                return;  // The wolf is still alive
	            }
	        }
	    }

	    grid_[row][col] = EMPTY;  // Remove the dead wolf
	    --numWolves_;  // Decrease the wolf count
	}

};

int main() {
    // Seed the random number generator
    std::srand(std::time(nullptr));

    // Create an instance of the Universe class
    Universe universe(10, 10, 5, 3);

    // Run the simulation
    universe.runSimulation();

    return 0;
}

