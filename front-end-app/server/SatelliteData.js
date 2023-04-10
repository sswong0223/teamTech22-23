import { config } from 'dotenv';
config();

import express, { Request, Response } from 'express';
import cors from 'cors';
import bodyParser from 'body-parser';
import mongoose from 'mongoose';
import Satellite from "./models/Satellite"

const PORT = 5000;
const app = express();

app.use(cors({
    origin: "*"
    })
);
app.use(express.json());

app.get('/satellite', async (req, res) => {
    const satellite = await Satellite.find();
    res.json(satellite);
});

app.post('/satellite', async (req, res) => {
    const newSatellite = new Satellite({
        name: req.body.name,
        startTime: req.body.startTime,
        endTime: req.body.endTime
    });
    const createdSatellite = await newSatellite.save();
    res.json(createdSatellite);
});

app.delete('/satellite/:satelliteId', async (req, res) => {
    const satelliteId = req.params.satelliteId;
    const satellite = await Menu.findByIdAndDelete(satelliteId);
    res.json(satellite);
});

const mongoUrl = process.env.MONGO_URL ?? 'mongodb://localhost/mydatabase';

mongoose.connect(mongoUrl).then(() => {

console.log(`listening on port ${PORT}`);
 app.listen(PORT);   
});
