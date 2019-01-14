echo "=== unlock default wallet ==="
cleos wallet unlock --password PW5Jy8pnfEXKQbWb4KNsCmbbA5Vdkt9D1rpYbbQWgBaeqhhbSZznJ

echo "=== start create accounts in blockchain ==="
cleos create account eosio ebonhaven EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
cleos create account eosio alice EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
cleos create account eosio bob EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV