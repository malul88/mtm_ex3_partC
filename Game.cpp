#include "Game.h"
#include "Exceptions.h"

using namespace mtm;

Game::Game(const int height, const int width) : game_board(Dimensions(height, width), nullptr) { // todo check init with bad arguments
    if (height <= 0 || width <= 0) {
        throw IllegalArgument();
    }
}

Game::Game(const Game &other) : game_board(nullptr) {
    int row = other.game_board.height();
    int col = other.game_board.width();
    game_board = Matrix<Character *>(Dimensions(row, col), nullptr);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            game_board(i, j) = other.game_board(i, j)->clone();

        }
    }
}

Game &Game::operator=(const Game &other) {
    if (this == &other) {
        return *this;
    }
    int row = other.game_board.height();
    int col = other.game_board.width();
    Matrix<Character *> temp(Dimensions(row, col), nullptr);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            temp(i, j) = other.game_board(i, j)->clone();
        }
    }
    game_board = temp;
    return *this;
}

void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character) {
    int row = this->game_board.height();
    int col = this->game_board.width();
    if (coordinates.row < 0 || coordinates.row >= row || coordinates.col < 0 || coordinates.col >= col) {
        throw IllegalCell();
    }
    if (game_board(coordinates.row, coordinates.col) != nullptr) {
        throw CellOccupied();
    }
    game_board(coordinates.row, coordinates.col) = &*character;
}

void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
    int row = game_board.height();
    int col = game_board.width();
    if (src_coordinates.col < 0 || src_coordinates.col >= col || src_coordinates.row < 0 || src_coordinates.row >= row ||
        dst_coordinates.col < 0 || dst_coordinates.col >= col || dst_coordinates.row < 0 || dst_coordinates.row >= row) {
        throw IllegalCell();
    }
    if (game_board(src_coordinates.row, src_coordinates.col) == nullptr) {
        throw CellEmpty();
    }
    if (game_board(dst_coordinates.row, dst_coordinates.col) != nullptr) {
        throw CellOccupied();
    }
    game_board(src_coordinates.row, src_coordinates.col)->move(src_coordinates, dst_coordinates, game_board);
}

void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
    int row = game_board.height();
    int col = game_board.width();
    if (src_coordinates.col < 0 || src_coordinates.col >= col || src_coordinates.row < 0 || src_coordinates.row >= row ||
        dst_coordinates.col < 0 || dst_coordinates.col >= col || dst_coordinates.row < 0 || dst_coordinates.row >= row) {
        throw IllegalCell();
    }
    if (game_board(src_coordinates.row, src_coordinates.col) == nullptr) {
        throw CellEmpty();
    }
    game_board(src_coordinates.row, src_coordinates.col)->attack(src_coordinates, dst_coordinates, this->game_board);
}

void Game::reload(const GridPoint &coordinates) {
    int row = this->game_board.height();
    int col = this->game_board.width();
    if (coordinates.row < 0 || coordinates.row >= row || coordinates.col < 0 || coordinates.col >= col) {
        throw IllegalCell();
    }
    if (game_board(coordinates.row, coordinates.col) == nullptr) {
        throw CellEmpty();
    }
    game_board(coordinates.row, coordinates.col)->reload();
}

std::ostream &mtm::operator<<(std::ostream &os, const Game &game) {
    int row = game.game_board.height();
    int col = game.game_board.width();
    Matrix<char> new_board(Dimensions(row, col), ' ');
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (game.game_board(i, j) != nullptr) {
                new_board(i, j) = game.game_board(i, j)->getCharacter();
            }
        }
    }
    Matrix<char>::iterator it_begin = new_board.begin();
    Matrix<char>::iterator it_end = new_board.end();
    char *begin = &*it_begin;
    char *end = &*it_end;
    return printGameBoard(os, begin, end, col);
}

bool Game::isOver(const mtm::Team *winningTeam) const {
    int row = game_board.height();
    int col = game_board.width();

    int team_cpp = 0;
    int team_py = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (game_board(i,j) != nullptr){
                if (isUpper(game_board(i, j)->getCharacter())){
                    team_cpp++;
                } else {
                    team_py++;
                }
            }

        }

    }
    if ((team_cpp == 0 && team_py == 0) || (team_cpp > 0  && team_py > 0)){
        return false;
    }
    if (team_cpp > 0 && team_py == 0){
        if(winningTeam != NULL){
            *winningTeam = CPP;
        }
        return true;
    }
    if (team_py > 0 && team_cpp == 0){
        if(winningTeam != NULL){
            *winningTeam = PYTHON;
        }
        return true;
    }
    return false;
}











