const createAccount = async (db, payload, blockInfo) => {

    console.info("\n\n==== New Account Updater ====")
    console.info("\n\nUpdater Payload >>> \n", payload)
    console.info("\n\nUpdater Block Info >>> \n", blockInfo)

    const data = {
    }

    console.info("DB Data to Insert >>> ", data);

    const res = await db.accounts.insert(data);

    console.info("DB State Result >>> ", res);
}

const updaters = [
    {
        actionType: "ebonhavencom::newaccount",
        updater: createAccount
    }
]

export { updaters }