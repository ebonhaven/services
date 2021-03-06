const logAccountCreated = (_, payload) => {
    console.log("Account Created ==> Payload:\n", payload);
}

const effects = [
    {
        actionType: "ebonhavencom::newaccount",
        run: logAccountCreated
    }
];

export { effects }