#ifndef MTM_EX3_PARTC_GAME_H
#define MTM_EX3_PARTC_GAME_H
#include "Character.h"
#include "Matrix.h"
#include "Sniper.h"
#include "Soldier.h"
#include "Medic.h"
#include "Exceptions.h"
namespace mtm {
    class Game {
    private:
        Matrix<Character*> game_board;
    public:
        Game(const int height, const int width);

        ~Game() = default;

        Game(const Game &other);

        Game &operator=(const Game &other);

        void addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character);

        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);

        void attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);

        void reload(const GridPoint &coordinates);

        friend std::ostream &operator<<(std::ostream &os, const Game &game);

        bool isOver(const Team *winningTeam = NULL) const;

        enum Team {
            CPP, PYTHON
        };
        enum CharacterType {
            SOLDIER, MEDIC, SNIPER
        };
        typedef int units_t;

        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power){
            if (health <=0 || ammo < 0 || range <= 0|| power < 0){
                throw IllegalArgument();
            }
            if (type == SOLDIER){
                std::shared_ptr<Character> result(new Soldier(health, ammo ,range, power, team));
                return result;
            }
            if (type == SNIPER){
                std::shared_ptr<Character> result(new Sniper(health, ammo ,range, power, team));
                return result;
            }if (type == MEDIC){
                std::shared_ptr<Character> result(new Medic(health, ammo ,range, power, team));
                return result;
            }
        }
        static bool isUpper(char c) {
            return c >= 'A' && c <= 'Z';
        }


    };

}
#endif //MTM_EX3_PARTC_GAME_H
