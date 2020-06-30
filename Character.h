#ifndef MTM_EX3_PARTC_CHARACTER_H
#define MTM_EX3_PARTC_CHARACTER_H
#include <iostream>
#include <vector>
#include <memory>
#include "Auxiliaries.h"
#include "Matrix.h"
#include "Game.h"
#include <cmath>

namespace mtm {
    class Character {
    protected:
        int health, ammo, range, power;
        Team team;
    public:
        Character(int health, int ammo, int range, int power, Team team) : health(health), ammo(ammo), range(range), power(power),Team(team) {}
        virtual ~Character() = default;
        virtual void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates,Matrix<Character*>& game_board) = 0;
        virtual void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates, Matrix<Character*>& game_board) = 0;
        virtual void reload()= 0 ;
        virtual Character *clone() const =0 ;
        void hit(int damage){
            health -= damage;
        }
        Team getTeam(){
            return team;
        }
        int getHealth(){
            return health;
        }
        int roundUp(int x, int y){
            return (int) ceill(static_cast<double>(static_cast<double >(x) / y));


        }

    };
}

#endif //MTM_EX3_PARTC_CHARACTER_H
