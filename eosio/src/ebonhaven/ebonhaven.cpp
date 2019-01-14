#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/crypto.h>
#include <eosiolib/print.hpp>
#include <eosiolib/fixedpoint.hpp>
#include <functional>
#include <string.h>
#include <math.h>

using namespace std;
using namespace eosio;

#include "table/globals.hpp"
#include "table/entity.hpp"
#include "table/ecmap.hpp"
#include "table/component.hpp"
#include "table/account.hpp"
#include "controllers/entity.controller.cpp"
#include "controllers/game.controller.cpp"
#include "controllers/account.controller.cpp"

class [[eosio::contract]] ebonhaven : public contract {
    private:
        game_controller game_controller;
        account_controller account_controller;

    public:
        ebonhaven( name receiver, name code, datastream<const char*> ds):contract(receiver, code, ds),
            game_controller( _self ),
            account_controller( _self ){};

        [[eosio::action]]
        void hello( name user ) {
            game_controller.say_hello( user );
        }

        [[eosio::action]]
        void newaccount( name user ) {
            account_controller.create_account( user );
        }
};

EOSIO_DISPATCH( ebonhaven, 
    (hello)
    (newaccount)
);