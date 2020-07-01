#ifndef MTM_EX3_PARTC_EXCEPTIONS_H
#define MTM_EX3_PARTC_EXCEPTIONS_H
#include "Game.h"
namespace mtm {
    class Exception : public std::exception {

    };

    class GameException : public Exception {

    };

    class IllegalArgument : public GameException {

    };

    class IllegalCell : public GameException {

    };

    class CellEmpty : public GameException {

    };

    class MoveTooFar : public GameException {

    };

    class CellOccupied : public GameException {

    };

    class OutOfRange : public GameException {

    };

    class OutOfAmmo : public GameException {

    };

    class IllegalTarget : public GameException {

    };


}
#endif //MTM_EX3_PARTC_EXCEPTIONS_H
