import "./index.css";
import React, { useState, useEffect } from "react";
import { format } from "date-fns";

function ShowEvents() {
  // create loop that searches for specific date
  // day = format(day, "MM/dd/YYYY");
  // call search function to search for specific date

  const [satelliteItems, setSatellite] = useState([]);

  useEffect(() => {
    async function getItems() {
      const response = await fetch("http://localhost:8080/api/satellite");
      const newSatellite = await response.json();
      setSatellite(newSatellite);
    }
    getItems();
  }, []);

  return (
    <div className="Events">
      <h4> Satellite Information Down Here</h4>
      <ul style={{ textAlign: "left" }}>testing</ul>

      <div>
        <h1>Satellite Data</h1>
        <ul>
          {satelliteItems.map((item) => (
            <li key={item.id}>
              Name: {item.name}, Start Time: {item.startTime}, End Time:{" "}
              {item.endTime}
            </li>
          ))}
        </ul>
      </div>
    </div>
  );
}

export default ShowEvents;
