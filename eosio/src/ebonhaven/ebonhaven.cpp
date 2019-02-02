#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/asset.hpp>

using namespace eosio;
using namespace std;

class [[eosio::contract]] ebonhaven : public contract {
    public:
        ebonhaven( name receiver, name code, datastream<const char*> ds):contract(receiver, code, ds),
            _config(code, code.value){};

        [[eosio::action]]
        void newaccount( name user ) {

            require_auth( user );
            accounts_table accounts(_code, _code.value);
            auto itr = accounts.find( user.value );
            eosio_assert(itr == accounts.end(), "Account already exists");
            if (itr == accounts.end() ) {
                accounts.emplace( user , [&](auto& ac) {
                    ac.user = user;
                });
            }
        }

        [[eosio::action]]
        void newcharacter( name user, string character_name, uint8_t gender, uint8_t profession, uint8_t race ) {
            require_auth( user );

            eosio_assert(gender >= 0 && gender <= 1, "Character must have a valid gender");
            eosio_assert(profession >= 0 && profession <= 5, "Character must have a valid profession");
            eosio_assert(race >= 0 && race <= 6, "Character must have a valid race");

            characters_table characters(_code, _code.value);
            base_stats_table basestats(_code, _code.value);
            auto& base = basestats.get(profession, "Profession does not exist");

            // Create account if none exists
            accounts_table accounts(_code, _code.value);
            auto ac_itr = accounts.find( user.value );
            if( ac_itr == accounts.end() ) {
                ac_itr = accounts.emplace( user, [&](auto& ac ) {
                    ac.user = user;
                });
            }

            //auto itr = characters.find(user.value);
            auto str = user.to_string() + character_name + std::to_string(current_time());
            auto hash = create_hash(str);

            characters.emplace(user, [&](auto& row ) {
                row.character_id = hash;
                row.user = user;
                row.character_name = character_name;
                row.gender = gender;
                row.profession = profession;
                row.race = race;
                row.hp = base.base_hp;
                row.max_hp = base.base_hp;
                row.attack = base.base_attack;
                row.defense = base.base_defense;
                row.stats = base.base_stats;
            });

            accounts.modify(ac_itr, user, [&](auto& ac) {
                ac.characters.push_back(hash);
            });
        };

        [[eosio::action]]
        void upsertstats( name    user, 
                          uint8_t profession_id,
                          uint8_t base_hp,
                          uint8_t hp_increase_by_level,
                          vector<uint32_t> base_attack,
                          vector<uint32_t> base_defense,
                          vector<uint32_t> new_stats,
                          vector<uint32_t> attack_increase,
                          vector<uint32_t> defense_increase,
                          vector<uint32_t> stat_increase_by_level) {
            require_auth( user );
            base_stats_table basestats(_code, _code.value);
            auto itr = basestats.find(profession_id);

            stats s_stats = { new_stats[0], new_stats[1], new_stats[2], new_stats[3], new_stats[4] };
            attack s_attack = { base_attack[0], base_attack[1] };
            defense s_defense = { base_defense[0], base_defense[1] };
            stats s_increase = { stat_increase_by_level[0], stat_increase_by_level[1], stat_increase_by_level[2], stat_increase_by_level[3], stat_increase_by_level[4] };
            attack s_attack_increase = { attack_increase[0], attack_increase[1] };
            defense s_defense_increase = { defense_increase[0], defense_increase[1] };

            if ( itr == basestats.end() ) {
                basestats.emplace(user, [&](auto& row) {
                    row.profession_id = profession_id;
                    row.base_hp = base_hp;
                    row.hp_increase_by_level = hp_increase_by_level;
                    row.base_attack = s_attack;
                    row.base_defense = s_defense;
                    row.base_stats = s_stats;
                    row.attack_increase_by_level = s_attack_increase;
                    row.defense_increase_by_level = s_defense_increase;
                    row.stat_increase_by_level = s_increase;
                });
            } else {
                basestats.modify(itr, user, [&](auto& row) {
                    row.base_hp = base_hp;
                    row.hp_increase_by_level = hp_increase_by_level;
                    row.base_attack = s_attack;
                    row.base_defense = s_defense;
                    row.base_stats = s_stats;
                    row.attack_increase_by_level = s_attack_increase;
                    row.defense_increase_by_level = s_defense_increase;
                    row.stat_increase_by_level = s_increase;
                });
            }                  
        }; 

    private:

        enum class gender: uint8_t {
            MALE = 0,
            FEMALE = 1
        };

        enum class race: uint8_t {
            NONE = 0,
            HUMAN = 1,
            EARTHEN = 2,
            AMAZON = 3,
            HIGHBORNE = 4,
            GOBLIN = 5,
            MECHA = 6
        };

        enum class profession: uint8_t {
            NONE = 0,
            ROCKHOUND = 1,
            SURVIVALIST = 2,
            ALCHEMIST = 3,
            CONJUROR = 4,
            METALSMITH = 5
        };

        struct stats {
            // Increase max health
            uint32_t stamina = 0;
            // Increase health regeneration
            uint32_t regen = 0;
            // Improved chance of resource encounter
            uint32_t perception = 0;
            // Improved chance of crafting additional items
            uint32_t skill = 0;
            // Improved chance of finding treasure
            uint32_t luck = 0;
        };

        struct attack {
            uint32_t physical = 0;
            uint32_t spell = 0;
        };

        struct defense {
            uint32_t physical = 0;
            uint32_t spell = 0;
        };

        struct position {
            uint8_t world = 0;
            uint8_t zone = 0;
            uint8_t x = 0;
            uint8_t y = 0;
            uint8_t orientation = 0;
        };

        struct equipment {
            uint64_t head;
            uint64_t neck;
            uint64_t shoulders;
            uint64_t chest;
            uint64_t bracers;
            uint64_t hands;
            uint64_t legs;
            uint64_t feet;
            uint64_t mainhand;
            uint64_t offhand;
            uint64_t ranged;
            uint64_t ring1;
            uint64_t ring2;
            uint64_t trinket1;
            uint64_t trinket2;
        };

        struct [[eosio::table]] globals {
            uint64_t key = 1;
            uint32_t seed = 1;
            asset    supply = asset(0, symbol(symbol_code("EBON"),4));
            asset    max_supply;
            name     issuer;
            
            auto primary_key() const { return key; }
        };

        typedef multi_index<"globals"_n, globals> config_table;
        config_table _config;

        struct [[eosio::table]] account {
            uint64_t id;
            name user;
            asset balance = asset(0, symbol(symbol_code("EBON"),4));
            vector<uint64_t> characters;
            vector<uint64_t> inventory;

            auto primary_key() const { return user.value; }
        };

        typedef eosio::multi_index<"accounts"_n, account> accounts_table;


        struct [[eosio::table]] basestat {
            uint8_t profession_id;
            uint8_t base_hp;
            uint8_t hp_increase_by_level;
            attack base_attack;
            defense base_defense;
            stats base_stats;
            attack attack_increase_by_level;
            defense defense_increase_by_level;
            stats stat_increase_by_level;

            auto primary_key() const { return profession_id; }
        };

        typedef eosio::multi_index<"basestats"_n, basestat> base_stats_table;

        struct [[eosio::table]] character {
            uint64_t character_id;
            name user;
            string character_name;
            uint8_t gender;
            uint8_t profession;
            uint8_t race;
            int32_t level = 1;
            uint32_t experience = 0;
            position position;
            uint8_t in_combat = 0;
            int64_t hp = 0;
            uint64_t max_hp = 0;
            stats stats;
            attack attack;
            defense defense;
            equipment equipped;

            uint64_t primary_key() const { return character_id; }
        };

        typedef eosio::multi_index<"characters"_n, character> characters_table;

        int random(const int range) {
            // Find the existing seed
            auto seed_itr = _config.begin();

            // Initialize the seed with default value if it is not found
            if (seed_itr == _config.end()) {
                seed_itr = _config.emplace( get_self(), [&]( auto& globals ) { });
            }

            // Generate new seed value using the existing seed value
            int prime = 65537;
            auto new_seed_value = (seed_itr->seed + now()) % prime;

            // Store the updated seed value in the table
            _config.modify( seed_itr, get_self(), [&]( auto& s ) {
                s.seed = new_seed_value;
            });

            // Get the random result in desired range
            int random_result = new_seed_value % range;
            return random_result;
        }

        uint64_t create_hash( const string& str ) {
            // Hash the string to a checksum
            hash<string> hasher;
            uint64_t result = hasher(str);
            // Return resulting digest
            return result;
        };
};

EOSIO_DISPATCH(ebonhaven, (newaccount)(newcharacter));