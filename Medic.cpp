#include "Medic.h"

using namespace mtm;

Medic::Medic(int health, int ammo, int range, int power, Team team) :
            Character(health, ammo, range, power, team) {
}

void Medic::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates, Matrix<Character *> &game_board) {
    if (GridPoint::distance(src_coordinates, dst_coordinates) > MOVEMENT_RANGE) {
        throw MoveTooFar();
    }
    game_board(dst_coordinates.row, dst_coordinates.col) = game_board(src_coordinates.row, src_coordinates.col);
    game_board(src_coordinates.row, src_coordinates.col) = nullptr;
}

Character *Medic::clone() const {
    return new Medic(*this);
}

void Medic::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates, Matrix<Character*> &game_board) {
    int distance = GridPoint::distance(src_coordinates, dst_coordinates);
    if (distance > range) {
        throw OutOfRange();
    }
    if (game_board(dst_coordinates.row, dst_coordinates.col) == nullptr || src_coordinates == dst_coordinates) {
        throw IllegalTarget();
    }
    if (game_board(dst_coordinates.row, dst_coordinates.col)->getTeam() ==
        game_board(src_coordinates.row, src_coordinates.col)->getTeam()){
        game_board(dst_coordinates.row, dst_coordinates.col)->hit(-power);
    } else {
        if (ammo <= 0) {
            throw OutOfAmmo();
        }
        game_board(dst_coordinates.row, dst_coordinates.col)->hit(power);
        if (game_board(dst_coordinates.row, dst_coordinates.col)->getHealth() <= 0) {
            delete game_board(dst_coordinates.row, dst_coordinates.col);
            game_board(dst_coordinates.row, dst_coordinates.col) = nullptr;
        }
        ammo-=ATTACK_COST;
    }
}

void Medic::reload() {
    ammo += RELOAD_AMMO;
}

char Medic::getCharacter() {
    if (team == CPP) {
        return 'M';
    } else {
        return 'm';
    }
}
