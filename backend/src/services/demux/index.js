import { BaseActionWatcher } from "demux";
import { MassiveActionHandler } from "demux-postgres";
import { NodeosActionReader } from "demux-eos"; // Or any other compatible Action Reader
import massive from "massive";
import { effects } from './effects';
import { updaters } from './updaters';

// See https://dmfay.github.io/massive-js/connecting.html for info on massive configuration
const dbConfig = {
    user: "user",
    password: "pass",
    host: "postgres",
    database: "ebonhavencom"
};

const nodeosConfig = {
    url: process.env.EOSIO_URL || "http://eosiodev:8888",
    startBlock: process.env.EOSIO_STARTING_BLOCK || 10
}

export class Demux {

    static init() {
        massive(dbConfig).then((db) => {
            console.log(nodeosConfig);
            const actionReader = new NodeosActionReader(
                nodeosConfig.url,
                nodeosConfig.startBlock
            );
            //actionReader.initialize();

            const actionHandler = new MassiveActionHandler(
                [{
                    versionName: "v1",
                    updaters,
                    effects
                }],
                db
            );
            
            const actionWatcher = new BaseActionWatcher(actionReader, actionHandler, 250)
            actionWatcher.watch();
        }, (err) => {
            console.error(err);
        });
    }
}