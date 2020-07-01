#include "Soldier.h"

using namespace mtm;


Soldier::Soldier(int health, int ammo, int range, int power, Team team) : Character(health, ammo, range, power, team) {
}

void Soldier::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates, Matrix<Character *> &game_board) {
    if (GridPoint::distance(src_coordinates, dst_coordinates) > MOVEMENT_RANGE) {
        throw MoveTooFar();
    }
    game_board(dst_coordinates.row, dst_coordinates.col) = game_board(src_coordinates.row, src_coordinates.col);
    game_board(src_coordinates.row, src_coordinates.col) = nullptr;
}

Character *Soldier::clone() const {
    return new Soldier(*this);
}

void Soldier::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates, Matrix<Character *> &game_board) {
    if (GridPoint::distance(src_coordinates, dst_coordinates) > range) {
        throw OutOfRange();
    }
    if (ammo <= 0) {
        throw OutOfAmmo();
    }
    if (src_coordinates.row != dst_coordinates.row && src_coordinates.col != dst_coordinates.col) {
        throw IllegalTarget();
    }
    int row = game_board.height();
    int col = game_board.width();
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            GridPoint tmp_dest(i, j);
            int co_range = roundUp(range, 3);
            if (i == src_coordinates.row && j == src_coordinates.col) {
                continue;
            }
            if (i == dst_coordinates.row && j == dst_coordinates.col && game_board(i, j) != nullptr) {
                game_board(i, j)->hit(power);
                if (game_board(i, j)->getHealth() <= 0){
                    delete game_board(i, j);
                    game_board(i, j) = nullptr;
                }
            } else if (GridPoint::distance(src_coordinates, tmp_dest) <= co_range) {
                if (team != game_board(i, j)->getTeam() && game_board(i, j) != nullptr) {
                    game_board(i, j)->hit(roundUp(power, 2));
                    if (game_board(i, j)->getHealth() <= 0){
                        delete game_board(i, j);
                        game_board(i, j) = nullptr;
                    }
                }
            }
        }
    }
    ammo -= ATTACK_COST;
}

void Soldier::reload() {
    ammo += RELOAD_AMMO;
}

char Soldier::getCharacter() {
    if (team == CPP) {
        return 'S';
    } else {
        return 's';
    }

}
