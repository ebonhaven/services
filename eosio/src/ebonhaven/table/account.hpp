#pragma once

struct [[eosio::table]] account {
    uint64_t id;
    name user;
    asset balance = asset(0, symbol(symbol_code("EBH"),4));

    auto primary_key() const { return id; }

    EOSLIB_SERIALIZE(account,
        (id)
        (user)
        (balance)
    )
};

typedef eosio::multi_index<"accounts"_n, account> accounts_table;