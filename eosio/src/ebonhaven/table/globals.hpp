#pragma once

struct [[eosio::table]] globals {
    uint64_t key = 1;
    uint32_t seed = 1;
    asset    supply = asset(0, symbol(symbol_code("EBH"),4));
    asset    max_supply;
    name     issuer;
    
    auto primary_key() const { return key; }

    EOSLIB_SERIALIZE(globals,
        (key)
        (seed)
        (supply)
        (max_supply)
        (issuer)
    )
};

typedef multi_index<"globals"_n, globals> config_table;