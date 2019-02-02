import { Migration } from "demux-postgres"

const createAccountsTable = new Migration("createAccountsTable", "ebonhaven", "./services/database/migrations/create_base_tables.sql");

const migrationSequences = [{
    migrations: [ createAccountsTable ],
    sequenceName: 'init'
}];

export { migrationSequences };