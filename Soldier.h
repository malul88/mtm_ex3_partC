#ifndef MTM_EX3_PARTC_SOLDIER_H
#define MTM_EX3_PARTC_SOLDIER_H
#include "Character.h"


namespace mtm {
    class Soldier : public Character {
    public:
        Soldier(int health, int ammo, int range, int power, Team team);

        const int MOVEMENT_RANGE = 3;
        const int RELOAD_AMMO = 3;
        const int ATTACK_COST = 1;

        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates,Matrix<Character*>& game_board);
        void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates, Matrix<Character*>& game_board);
        void reload();
        Character* clone() const override;
        char getCharacter() override;

    };

}
#endif //MTM_EX3_PARTC_SOLDIER_H
