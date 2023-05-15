import "./index.css";
import React, { useState, useEffect } from "react";
import { format } from "date-fns";

const ShowEvents = ( startDate ) => {
  // create loop that searches for specific date
  // day = format(day, "MM/dd/YYYY");
  // call search function to search for specific date

  const [satelliteItems, setSatellite] = useState([]);
  console.log("param" ,startDate)

  useEffect(() => {
    async function getItems() {

      const response = await fetch('http://localhost:8080/api/satellite');
      const newSatellite = await response.json();
     

      const newSatelliteItems = [];

      // Iterate through the data and create a 2D array of satellite items
      newSatellite.forEach(item => {
        const satelliteItem = [item.name, item.startTime, item.endTime];
        const start = satelliteItem[1].substring(0,10)
        const end = satelliteItem[2].substring(0,10)

        const indexToUpdate = 8;
        const dayUpdate = (parseInt(start.substring(8,10))+1).toString().padStart(2,'0');
        const nextDay = start.substring(0,8) + dayUpdate
        

        
        
        
        if(start == startDate || end == nextDay) {
          newSatelliteItems.push(satelliteItem);
          // console.log("here");
          console.log("today", start)
          console.log("param" ,startDate)  
          console.log("nextDay Day", dayUpdate)
          console.log("Tommorrow", nextDay)
          console.log("endDate", end);
        }
        
      
      });
    
      setSatellite(newSatelliteItems);
    }

    getItems();
  }, [startDate]);

  return (
    <div className="Events">

      {/* <h4> {format(new Date(startDate), "ccc dd MMM yy")} </h4> */}
      <div>
        <h1>Satellite Data</h1>
        <ul>
          <h3>
          Number of Satellites today: {satelliteItems.length}
          </h3>
          {satelliteItems.map((item, index) => (
            <li key={index}>
              Name: {item[0]},
              Start Time: {item[1]}, 
              End Time:{" "} {item[2]}
            </li>
          ))}
        </ul>
      </div>
    </div>
  );
}

export default ShowEvents;
