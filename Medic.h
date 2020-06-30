#ifndef MTM_EX3_PARTC_MEDIC_H
#define MTM_EX3_PARTC_MEDIC_H
#include "Character.h"
namespace mtm {
    class Medic : public Character {
        Medic(int health, int ammo, int range, int power, Team team);

        const int MOVEMENT_RANGE = 5;
        const int RELOAD_AMMO = 5;
        const int ATTACK_COST = 1;

        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates,Matrix<Character*>& game_board);
        void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates, Matrix<Character*>& game_board);
        void reload();
        Character* clone() const override;
        char getCharacter() override;


    };

}
#endif //MTM_EX3_PARTC_MEDIC_H
