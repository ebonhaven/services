#pragma once

struct [[eosio::table]] ecmap {
    uint64_t entity_id;
    uint64_t component_id;
    uint64_t component_data_id;

    auto primary_key() const { return entity_id; }
    uint64_t by_component_id() const { return component_id; }
    uint64_t by_component_data_id() const { return component_data_id; }

    EOSLIB_SERIALIZE(ecmap,
        (entity_id)
        (component_id)
        (component_data_id)
    )
};

typedef multi_index<"ecmaps"_n, ecmap,
        indexed_by< "bycomponent"_n, const_mem_fun<ecmap, uint64_t, &ecmap::by_component_id> >,
        indexed_by< "bydata"_n, const_mem_fun<ecmap, uint64_t, &ecmap::by_component_data_id> >
    > ecmaps_table;