using namespace eosio;

class game_controller {
    private:
        name self;
        config_table config;

    public:
        game_controller( name _self ): self(_self),
            config(_self, _self.value){};

        void say_hello( name user ) {
            auto _conf = config.get(1, "Couldn't get table");
            print("Hello ", self);
            print("Conf seed is: ", _conf.seed);
        }
};