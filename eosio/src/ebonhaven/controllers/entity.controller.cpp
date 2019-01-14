template<class Entity, class Table>
class entity_controller {
    protected:
        Table table;
        name self;
        std::string version;

    public:
        entity_controller(name _self) : table(_self, _self.value),
            self(_self) {}

        void create_entity(const std::vector<Entity> &data) {
            
            for (auto iter = data.begin(); iter != data.end(); ++iter) {
                auto pos = table.find(iter->primary_key());
                if (pos != table.cend()) {
                    table.modify(pos, self, [&](auto &entity) {
                        entity = *iter;
                    });
                } else {
                    table.emplace(self, [&](auto &entity) {
                        entity = *iter;
                    });
                }
            }

        }

        bool is_empty() {
            return table.cbegin() == table.cend();
        }

        Table& get_table() {
            return table;
        }
        
};