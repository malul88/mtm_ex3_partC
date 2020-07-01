#ifndef MTM_EX3_PARTC_SNIPER_H
#define MTM_EX3_PARTC_SNIPER_H

#include "Character.h"

namespace mtm {
    class Sniper : public Character {
        int attack_counter;
        public:
        Sniper(int health, int ammo, int range, int power, Team team, int counter = 0);

        const int MOVEMENT_RANGE = 4;
        const int RELOAD_AMMO = 2;
        const int ATTACK_COST = 1;

        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates,Matrix<Character*>& game_board) override;
        void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates, Matrix<Character*>& game_board) override;
        void reload() override;
        Character* clone() const override;
        char getCharacter() override;
    };
}

#endif //MTM_EX3_PARTC_SNIPER_H
