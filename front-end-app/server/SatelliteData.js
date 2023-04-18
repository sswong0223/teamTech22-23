import { config } from 'dotenv';
import * as dotenv from 'dotenv'
import express from 'express';
import cors from 'cors';
import bodyParser from 'body-parser';
import mongoose from 'mongoose';
import connectDB from './mongodb/connect.js';
import SatelliteModel from './models/Satellite.js';
import satelliteRouter from './routes/Satellite.routes.js'

dotenv.config();

const app = express();
app.use(cors());
app.use(express.json());


app.get('/', (req,res) => {
    res.send({message: 'Hello World'});
})

app.use('/api/satellite', satelliteRouter);

const startServer = async () => {
    try{
        connectDB(process.env.MONGO_URL);
        app.listen(8080, () => console.log('Server started on port http://localhost:8080'));
    } catch (error){
        console.log(error);
    }
}

startServer();

// app.get('/satellite', async (req, res) => {
//     try {
//         // Fetch all satellites from the database using the Mongoose model
//         const satellites = await SatelliteModel.find();
//         res.json(satellites);
//       } catch (error) {
//         // Handle any errors
//         res.status(500).json({ error: 'Failed to fetch satellites' });
//       }
// });

// app.post('/satellite', async (req, res) => {
//     try {
//         // Create a new satellite in the database using the Mongoose model
//         const satellite = new SatelliteModel({ 
//             name: req.body.name,
//             startTime: req.body.startTime,
//             endTime: req.body.endTime
//         })
//         await satellite.save();
//         res.json(satellite);
//       } catch (error) {
//         // Handle any errors
//         res.status(500).json({ error: 'Failed to create satellite' });
//       }
// });
