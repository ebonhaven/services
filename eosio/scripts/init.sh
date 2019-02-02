echo "=== setup wallet ==="
rm -rf ~/eosio-wallet/ebonhavencom.wallet
cleos wallet create -n ebonhavencom --to-console | tail -1 | sed -e 's/^"//' -e 's/"$//' > ebonhavencom_wallet_password.txt
cleos wallet import -n ebonhavencom --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3
cleos wallet import -n ebonhavencom --private-key 5JpWT4ehouB2FF9aCfdfnZ5AwbQbTtHBAwebRXt94FmjyhXwL4K
cleos wallet import -n ebonhavencom --private-key 5JD9AGTuTeD5BXZwGQ5AtwBqHK21aHmYnTetHgk1B3pjj7krT8N

echo "=== deploy dapp smart contract ==="
cleos create account eosio ebonhavencom EOS6PUh9rs7eddJNzqgqDx1QrspSHLRxLMcRdwHZZRL4tpbtvia5B EOS8BCgapgYA2L4LJfCzekzeSr3rzgSTUXRXwNi8bNRoz31D14en9

./deploy.sh

echo "=== start create accounts in blockchain ==="
cleos create account eosio alice EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
cleos create account eosio bob EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV