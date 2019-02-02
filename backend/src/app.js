import express from 'express';
import bodyParser from 'body-parser';
import mapRoutes from 'express-routes-mapper'
import routes from './config/routes';
import { Demux } from './services/demux';

const app = express();
const port = 3000;

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.use('/', mapRoutes(routes, 'src/controllers/'));

app.listen(port, () => {
    console.log(`Listening on http://127.0.0.1:${port}`);
});

try {
    Demux.init();
} catch (e) {
    console.log('Error!', e);
}




