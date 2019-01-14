#pragma once

struct [[eosio::table]] entity {
    uint64_t key = 1;
    std::string entity_name;

    auto primary_key() const { return key; }

    EOSLIB_SERIALIZE(entity,
        (key)
        (entity_name)
    )
};

typedef multi_index<"entities"_n, entity> entities_table;