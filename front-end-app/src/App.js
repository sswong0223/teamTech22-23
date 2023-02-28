// combine caci and swe logo into one image
// import logo from './images/sweCaciLogo.png';
import Navbar from './components/Navbar';
// to install calendar use npm install react-big-calendar react-datepicker date-fns
import format from "date-fns/format";
import getDay from "date-fns/getDay";
import parse from "date-fns/parse";
import startOfWeek from "date-fns/startOfWeek";
import React, { useState } from "react";
import { Calendar, dateFnsLocalizer } from "react-big-calendar";
import "react-big-calendar/lib/css/react-big-calendar.css";
import DatePicker from "react-datepicker";
import "react-datepicker/dist/react-datepicker.css";
import './App.css';

const locales = {
  "en-US": require("date-fns/locale/en-US")
};

const localizer = dateFnsLocalizer ({
  format,
  parse,
  startOfWeek,
  getDay, 
  locales
});
// array of objects, can hard code for now, then implement back end somehow
const events = [
  {
    title: "Satellite One",
    allDay: true,
    start: new Date(2023, 3, 2),
    end: new Date(2023, 3, 2)
  },
  {
    title: "Satellite Two",
    start: new Date(2023, 3, 27),
    end: new Date(2023, 3, 29)
  },
  {
    title: "Satellite Three",
    start: new Date(2023, 4, 1),
    end: new Date(2023, 4, 6)
  }
];

function App() {
  
  return (
    <div className = "App">
      <Navbar/>
        <Calendar 
          localizer={localizer} 
          events={events} 
          startAccessor="start" 
          endAccessor="end" 
          style={{height: 500, marign: "50px"}} 
        />
    </div>
  );
}

export default App;
