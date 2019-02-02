const createAccount = async (db, payload, blockInfo) => {

    console.info("\n\n==== New Account Updater ====")
    console.info("\n\nUpdater Payload >>> \n", payload)
    console.info("\n\nUpdater Block Info >>> \n", blockInfo)

    const data = {
        user: payload.data.user,
        balance: "0.0000 EBON",
        inventory: [],
        characters: []
    }

    console.info("DB Data to Insert >>> ", data);

    const res = await db.accounts.insert(data);

    console.info("DB State Result >>> ", res);
}

const updaters = [
    {
        actionType: "ebonhavencom::newaccount",
        apply: createAccount
    }
]

export { updaters }