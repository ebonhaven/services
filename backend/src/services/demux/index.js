import { BaseActionWatcher } from "demux";
import { MassiveActionHandler } from "demux-postgres";
import { NodeosActionReader } from "demux-eos"; // Or any other compatible Action Reader
import massive from "massive";
import { migrationSequences } from './migrationSequences';
import { effects } from './effects';
import { updaters } from './updaters';

// See https://dmfay.github.io/massive-js/connecting.html for info on massive configuration
const dbConfig = {
    user: "user",
    password: "pass",
    host: "postgres",
    database: "ebonhavencom",
    schema: "ebonhaven"
};

const nodeosConfig = {
    url: process.env.EOSIO_URL || "http://eosiodev:8888",
    startBlock: process.env.EOSIO_STARTING_BLOCK || 10
}

export class Demux {

    static init() {

        massive(dbConfig).then((db) => {
            const actionHandler = new MassiveActionHandler(
                [{
                    updaters,
                    effects,
                    versionName: "v1",
                }],
                db,
                dbConfig.schema,
                migrationSequences
            );
    
            actionHandler.setupDatabase();
    
            const actionReader = new NodeosActionReader(
                nodeosConfig.url,
                nodeosConfig.startBlock
            );
    
            const actionWatcher = new BaseActionWatcher(actionReader, actionHandler, 250);
    
            actionWatcher.watch();
        }, (e) => {
            console.log('Error', e);
        });
    }
}