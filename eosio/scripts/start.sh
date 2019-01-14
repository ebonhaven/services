echo "=== setup blockchain accounts and smart contract ==="

mkdir -p $DATA_DIR
# start nodeos ( local node of blockchain )
/opt/eosio/bin/nodeos -e -p eosio --config-dir $CONFIG_DIR --delete-all-blocks --access-control-allow-origin=* --contracts-console --verbose-http-errors --data-dir $DATA_DIR 
