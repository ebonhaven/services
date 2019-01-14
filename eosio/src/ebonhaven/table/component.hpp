#pragma once

struct [[eosio::table]] component {
    uint64_t key = 1;
    std::string component_name;
    std::string component_description;
    std::string table_name;

    auto primary_key() const { return key; }

    EOSLIB_SERIALIZE(component,
        (key)
        (component_name)
        (component_description)
        (table_name)
    )
};

typedef multi_index<"components"_n, component> components_table;