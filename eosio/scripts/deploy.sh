CONTRACTSPATH="$( pwd -P )/src/ebonhaven"
TABLES="$CONTRACTSPATH/table"
CONTROLLERS="$CONTRACTSPATH/controllers"
cd $CONTRACTSPATH

echo "=== compiling and deploying ==="
(
    eosio-cpp -o ebonhaven.wasm ebonhaven.cpp -I=$INCLUDES -abigen
) &&

cleos set contract ebonhaven ../ebonhaven -p ebonhaven@active &&
cleos set account permission ebonhaven active --add-code

cd $( pwd -P )