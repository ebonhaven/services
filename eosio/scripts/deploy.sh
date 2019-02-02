echo "=== compiling and deploying ==="
cleos wallet unlock -n ebonhavencom --password $(cat ebonhavencom_wallet_password.txt)
cd ../src/ebonhaven

(
    eosio-cpp -o ebonhaven.wasm ebonhaven.cpp -abigen
) &&

cleos set contract ebonhavencom ../ebonhaven -p ebonhavencom &&
cleos set account permission ebonhavencom active --add-code

cd ../../scripts