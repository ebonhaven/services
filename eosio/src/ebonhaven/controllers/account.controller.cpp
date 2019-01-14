using namespace eosio;

class account_controller {
    private:
        name self;
        config_table config;
        entity_controller<account, accounts_table> accounts_ctl;

    public:
        account_controller( name _self ): self(_self),
            config(_self, _self.value),
            accounts_ctl(_self){};
        

        void create_account( name user ) {
            require_auth( user );

            std::vector<account> accounts;
            account a = account{};
            a.user = user;

            accounts_ctl.create_entity(accounts);
        }

        
};