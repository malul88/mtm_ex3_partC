#include "Sniper.h"

using namespace mtm;

Sniper::Sniper(int health, int ammo, int range, int power, Team team, int counter) : Character(health, ammo, range, power, team),
                                                                                     attack_counter(counter) {
}

void Sniper::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates, Matrix<Character *> &game_board) {
    if (GridPoint::distance(src_coordinates, dst_coordinates) > MOVEMENT_RANGE) {
        throw Game::MoveTooFar();
    }
    game_board(dst_coordinates.row, dst_coordinates.col) = game_board(src_coordinates.row, src_coordinates.col);
    game_board(src_coordinates.row, src_coordinates.col) = nullptr;
}

Character *Sniper::clone() const {
    return new Sniper(*this);
}

void Sniper::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates, Matrix<Character *> &game_board) {
    int distance = GridPoint::distance(src_coordinates, dst_coordinates);
    if (distance > range || distance < roundUp(range, 2)) {
        throw Game::OutOfRange();
    }
    if (ammo <= 0) {
        throw Game::OutOfAmmo();
    }
    if (game_board(dst_coordinates.row, dst_coordinates.col) == nullptr) {
        throw Game::IllegalTarget();
    }
    if ((attack_counter % 3) == 0 && attack_counter != 0) {
        game_board(dst_coordinates.row, dst_coordinates.col)->hit(power * 2);
        attack_counter++;
        ammo -= ATTACK_COST;
        if (game_board(dst_coordinates.row, dst_coordinates.col)->getHealth() <= 0) {
            delete game_board(dst_coordinates.row, dst_coordinates.col);
            game_board(dst_coordinates.row, dst_coordinates.col) = nullptr;
        }
    } else {
        game_board(dst_coordinates.row, dst_coordinates.col)->hit(power);
        attack_counter++;
        ammo -= ATTACK_COST;
        if (game_board(dst_coordinates.row, dst_coordinates.col)->getHealth() <= 0) {
            delete game_board(dst_coordinates.row, dst_coordinates.col);
            game_board(dst_coordinates.row, dst_coordinates.col) = nullptr;
        }
    }
}

void Sniper::reload() {
    ammo += RELOAD_AMMO;
}

char Sniper::getCharacter() {
    if (team == CPP) {
        return 'N';
    } else {
        return 'n';
    }
}
