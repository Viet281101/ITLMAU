

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>


using namespace std;

/**
* Colorize terminal colors ANSI escape sequences.
*
* @param font font color (-1 to 7), see Colors enum
* @param back background color (-1 to 7), see Colors enum
* @param style font style (1==bold, 4==underline)
**/
const char *colorize(int font, int back = -1, int style = -1) {
    static char code[20];
    
    if (font >= 0)
        font += 30;
    else
        font = 0;
    if (back >= 0)
        back += 40;
    else
        back = 0;

    if (back > 0 && style > 0) {
        sprintf(code, "\033[%d;%d;%dm", font, back, style);
    } else if (back > 0) {
        sprintf(code, "\033[%d;%dm", font, back);
    } else {

        sprintf(code, "\033[%dm", font);
    }

    return code;
};

char intToAsciiChar(int nbr) 
{
    return (char('0' + nbr) + 17);
};

enum Colors { NC=-1, BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
enum Entity { VIDE, HERBE, MOUTON, LOUP, SELS_MINERAUX };

struct Position 
{
    int row;
    int col;
};


class Univers 
{

public:
    Univers(int rows, int cols, int nbrMoutons, int nbrLoups)
    : rows_(rows), cols_(cols), nbrMoutons_(nbrMoutons), nbrLoups_(nbrLoups), tour_(0)
    {    
        grid_.resize(rows_, vector<Entity>(cols_, VIDE));

        for (int i = 0; i < (rand() % (rows_ * cols_)); ++i) 
        {
            Position pos = randomCase();
            if (pos.row != -1 && pos.col != -1) grid_[pos.row][pos.col] = HERBE;
        }
    
        for (int i = 0; i < nbrMoutons_; ++i) 
        {
            Position pos = randomCase();
            if (pos.row != -1 && pos.col != -1) grid_[pos.row][pos.col] = MOUTON;
        }

    
        for (int i = 0; i < nbrLoups_; ++i) 
        {
            Position pos = randomCase();
            if (pos.row != -1 && pos.col != -1) grid_[pos.row][pos.col] = LOUP;
        }
    }

    void simulerUnivers() 
    {
        cout << endl;
        cout << colorize(RED) << "L : Les loups " << colorize(NC) << endl;
        cout << colorize(YELLOW) << "M : Les moutons " << colorize(NC) << endl;
        cout << colorize(GREEN) << "H : Les herbes " << colorize(NC) << endl;
        cout << colorize(BLUE) << "H : Les sels minéreaux " << colorize(NC) << endl;
        
        do {
            afficherUnivers();
            cout << "Tour " << tour_ << " | Loups : " << nbrLoups_ << " | Moutons : " << nbrMoutons_ << endl;
            cout << endl;

            if (nbrLoups_ == 0 && nbrMoutons_ == 0) {
                cout << colorize(MAGENTA) << "L'UNIVERS EST MORT !!" << colorize(NC) << endl;
                cout << endl;
                break;
            }

            simulationChaqueTour();

            ++tour_;

            cout << "1. Continuer jusqu'au tour suivant" << endl;
            cout << "2. Quitter" << endl;
            cout << "Choix : ";
            int choice;
            cin >> choice;

        
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice == 2) break;
        } while (true);
    }

private:
    vector<vector<Entity>> grid_;
    int rows_;
    int cols_;
    int nbrMoutons_;
    int nbrLoups_;
    int tour_;

    void afficherUnivers() {
        cout << endl;
        cout << endl << "//////////////////////////////////////////" << endl;
        cout << endl << "    1   2   3   4   5   6   7   8   9   10" << endl;
        for (int i = 0; i < rows_; ++i) 
        {
            cout << "  +---+---+---+---+---+---+---+---+---+---+" << endl;
            cout << char(intToAsciiChar(i)) << " |";
            for (int j = 0; j < cols_; ++j) 
            {
                switch (grid_[i][j]) 
                {
                    case VIDE:
                        cout << "   " << "|";
                        break;
                    case HERBE:
                        cout << colorize(GREEN) << " H " << colorize(NC) << "|";
                        break;
                    case MOUTON:
                        cout << colorize(YELLOW) << " M " << colorize(NC) << "|";
                        break;
                    case LOUP:
                        cout << colorize(RED) << " L " << colorize(NC) << "|";
                        break;
                    case SELS_MINERAUX:
                        cout << colorize(BLUE) << " S " << colorize(NC) << "|";
                        break;
                    default:
                        break;
                }
            }
            cout << endl;
        }
        cout << "  +---+---+---+---+---+---+---+---+---+---+" << endl;
        cout << endl;
    }

    Position randomCase() {
        vector<Position> emptyCells;
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                if (grid_[i][j] == VIDE) emptyCells.push_back({i, j});
            }
        }
        if (emptyCells.empty()) return {-1, -1};
        int index = rand() % emptyCells.size();
        return emptyCells[index];
    }

    // Position randomCase() 
    // {
    //     int maxAttempts = rows_ * cols_;

    //     for (int attempt = 0; attempt < maxAttempts; ++attempt) 
    //     {
    //         int row = rand() % rows_;
    //         int col = rand() % cols_;
    //         if (grid_[row][col] == VIDE) return {row, col};
    //     }
    //     return {-1, -1};
    // }


    void simulationChaqueTour() {
        vector<Position> moutonPos;
        vector<Position> loupPos;

        for (int i = 0; i < rows_; ++i) 
        {
            for (int j = 0; j < cols_; ++j) 
            {
                if (grid_[i][j] == MOUTON) 
                {
                    moutonPos.push_back({i, j});
                } 
                else if (grid_[i][j] == LOUP) 
                {
                    loupPos.push_back({i, j});
                }
            }
        }

        for (const auto& pos : moutonPos) {
            deplacement(pos, MOUTON);
        }

        for (const auto& pos : loupPos) {
            deplacement(pos, LOUP);
        }

        for (int i = 0; i < rows_; ++i) 
        {
            for (int j = 0; j < cols_; ++j) 
            {
                if (grid_[i][j] == HERBE) 
                {
                    if (grid_[i][j] == SELS_MINERAUX) grid_[i][j] = HERBE; 
                } 
                else if (grid_[i][j] == MOUTON) 
                {
                    mangerHerbe({i, j});
                    if (grid_[i][j] == MOUTON) 
                    {
                        reproduction({i, j}, MOUTON);
                        moutonMeurt({i, j});
                    }
                } 
                else if (grid_[i][j] == LOUP) 
                {
                    mangerMouton({i, j});
                    if (grid_[i][j] == LOUP) 
                    {
                        reproduction({i, j}, LOUP);
                        loupMeurt({i, j});
                    }
                }
            }
        }

        for (const auto& pos : moutonPos) {
            if (grid_[pos.row][pos.col] == VIDE) {
                grid_[pos.row][pos.col] = SELS_MINERAUX;
            }
        }
        for (const auto& pos : loupPos) {
            if (grid_[pos.row][pos.col] == VIDE) {
                grid_[pos.row][pos.col] = SELS_MINERAUX;
            }
        }
    }

    void deplacement(const Position& pos, Entity entity) {
        int newRow = pos.row + rand() % 3 - 1;
        int newCol = pos.col + rand() % 3 - 1;

        newRow = (newRow + rows_) % rows_;
        newCol = (newCol + cols_) % cols_;

        if (grid_[newRow][newCol] == VIDE) {
            grid_[newRow][newCol] = entity;
            grid_[pos.row][pos.col] = VIDE;
        }
    }

	void mangerHerbe(const Position& pos) {
	    int row = pos.row;
	    int col = pos.col;

	    for (int i = row - 1; i <= row + 1; ++i) 
        {
	        for (int j = col - 1; j <= col + 1; ++j) 
            {
	            int newRow = (i + rows_) % rows_;
	            int newCol = (j + cols_) % cols_;

	            if (grid_[newRow][newCol] == HERBE) 
                {
	                grid_[newRow][newCol] = VIDE; 
	                grid_[row][col] = VIDE; 
	                return;
	            }
	        }
	    }
	}

    void mangerMouton(const Position& pos) 
    {
        int row = pos.row;
        int col = pos.col;

        for (int i = row - 1; i <= row + 1; ++i) 
        {
            for (int j = col - 1; j <= col + 1; ++j) 
            {
                int newRow = (i + rows_) % rows_;
                int newCol = (j + cols_) % cols_;

                if (grid_[newRow][newCol] == MOUTON) 
                {
                    grid_[newRow][newCol] = VIDE; 
                    --nbrMoutons_; 
                    return;
                }
            }
        }
    }

    void reproduction(const Position& pos, Entity entity) 
    {
        int row = pos.row;
        int col = pos.col;

        for (int i = row - 1; i <= row + 1; ++i) 
        {
            for (int j = col - 1; j <= col + 1; ++j) 
            {
                int newRow = (i + rows_) % rows_;
                int newCol = (j + cols_) % cols_;

                if (grid_[newRow][newCol] == VIDE) 
                {
                    grid_[newRow][newCol] = entity; 
                    if (entity == MOUTON) 
                    {
                        ++nbrMoutons_; 
                    } 
                    else if (entity == LOUP) 
                    {
                        ++nbrLoups_; 
                    }
                    return;
                }
            }
        }
    }

    void moutonMeurt(const Position& pos) 
    {
        int row = pos.row;
        int col = pos.col;
    
        for (int i = row - 1; i <= row + 1; ++i) 
        {
            for (int j = col - 1; j <= col + 1; ++j) 
            {
                if (i == row && j == col) continue;

                int newRow = (i + rows_) % rows_;
                int newCol = (j + cols_) % cols_;

                if (grid_[newRow][newCol] == HERBE || grid_[newRow][newCol] == MOUTON) return; 
            }
        }

        grid_[row][col] = VIDE; 
        --nbrMoutons_; 
    }

	void loupMeurt(const Position& pos) 
    {
	    int row = pos.row;
	    int col = pos.col;

	    for (int i = row - 1; i <= row + 1; ++i) 
        {
	        for (int j = col - 1; j <= col + 1; ++j) 
            {
	            if (i == row && j == col) continue; 

	            int newRow = (i + rows_) % rows_;
	            int newCol = (j + cols_) % cols_;

	            if (grid_[newRow][newCol] == MOUTON) return; 
	        }
	    }

	    grid_[row][col] = VIDE; 
	    --nbrLoups_; 
	}

};



int main() 
{
    int lignes = 10;
    int colonnes = 10;
    int nbrMouton = 2;
    int nbrLoup = 3;

    srand(time(nullptr));
    Univers univers(lignes, colonnes, nbrMouton, nbrLoup);
    univers.simulerUnivers();

    return 0;
}



