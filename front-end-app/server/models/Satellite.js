import mongoose from "mongoose";

const Schema = mongoose.Schema;

const SatelliteSchema = new Schema({
    name: String,
    startTime: String,
    endTime: String
}); 

const SatelliteModel = mongoose.model('SatelliteInfo', SatelliteSchema);

export default SatelliteModel;

