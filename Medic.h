#ifndef MTM_EX3_PARTC_MEDIC_H
#define MTM_EX3_PARTC_MEDIC_H
#include "Character.h"
namespace mtm {
    class Medic : public Character {
        Medic(int health, int ammo, int range, int power);

        const int MOVEMENT_RANGE = 3;
        const int RELOAD_AMMO = 5;
        const int ATTACK_COST = 1;

        void move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        void reload();
        Character* clone() const override;


    };

}
#endif //MTM_EX3_PARTC_MEDIC_H
