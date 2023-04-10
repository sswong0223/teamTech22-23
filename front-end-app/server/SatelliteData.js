import { config } from 'dotenv';
config();

import express, { Request, Response } from 'express';
import cors from 'cors';
import bodyParser from 'body-parser';
import mongoose from 'mongoose';
const SatelliteModel = require('./models/Satellite')

// const PORT = 5000;
const app = express.Router();

// app.use(cors({
//     origin: "*"
//     })
// );
// app.use(express.json());
const mongoUrl = process.env.MONGO_URL ?? 'mongodb://localhost/mydatabase';

mongoose.connect(mongoUrl, {
  useNewUrlParser: true,
  useUnifiedTopology: true
})
.then(() => {
  console.log('Connected to MongoDB');
})
.catch((error) => {
  console.error('Failed to connect to MongoDB', error);
});

app.get('/satellite', async (req, res) => {
    // const satellite = await Satellite.find();
    // res.json(satellite);

    try {
        // Fetch all satellites from the database using the Mongoose model
        const satellites = await SatelliteModel.find();
        res.json(satellites);
      } catch (error) {
        // Handle any errors
        res.status(500).json({ error: 'Failed to fetch satellites' });
      }
});

app.post('/satellite', async (req, res) => {
    // const newSatellite = new Satellite({
    //     name: req.body.name,
    //     startTime: req.body.startTime,
    //     endTime: req.body.endTime
    // });
    // const createdSatellite = await newSatellite.save();
    // res.json(createdSatellite);

    try {
        // Create a new satellite in the database using the Mongoose model
        const satellite = new SatelliteModel({ 
            name: req.body.name,
            startTime: req.body.startTime,
            endTime: req.body.endTime
        })
        await satellite.save();
        res.json(satellite);
      } catch (error) {
        // Handle any errors
        res.status(500).json({ error: 'Failed to create satellite' });
      }
});

// app.delete('/satellite/:satelliteId', async (req, res) => {
//     const satelliteId = req.params.satelliteId;
//     const satellite = await Menu.findByIdAndDelete(satelliteId);
//     res.json(satellite);
// });

// const mongoUrl = process.env.MONGO_URL ?? 'mongodb://localhost/mydatabase';

// mongoose.connect(mongoUrl).then(() => {

// console.log(`listening on port ${PORT}`);
//  app.listen(PORT);   
// });
