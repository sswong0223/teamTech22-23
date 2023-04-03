import { config } from 'dotenv';
config();
import express, { Request, Response } from 'express';
import cors from 'cors';
import bodyParser from 'body-parser';
import mongoose from 'mongoose';

const PORT = 5000;
const app = express();
app.use(cors({
    origin: "*"
    })
);
app.use(express.json());

