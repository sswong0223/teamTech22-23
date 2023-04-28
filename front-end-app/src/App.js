import "./index.css";
import "./Events.js"
import { useState } from "react";
import Calendar from "./Calendar";
import Details from "./Details";
import logo from "./images/sweCaciLogo.png";


export default function App() {
  const [showDetails, setShowDetails] = useState(false);
  const [data, setData] = useState(null);

  const showDetailsHandle = (dayStr) => {
    setData(dayStr);
    setShowDetails(true);
  };

  return (
    <div className="App">
     
      <h1>CACI Satellite Scheduler</h1>
       
      <Calendar showDetailsHandle={showDetailsHandle} />
      <br />
      <div className="Events">
      {showDetails && <Details data={data} />}
      <div className= "Events">
     <h3> Satellite information Down Here</h3>
      
  
      <ul style={{textAlign: "left"}}>Name:</ul>
      <ul style={{textAlign: "left"}}>Start Time:</ul>
      <ul style={{textAlign: "left"}}>End Time:</ul>
      <br>
      </br>
      
  </div>
      </div>

    <div className="Footer">
        <img src={logo} width={'100'}/>
</div>
    </div>


  
  );
}

/**
 * Follow this tutorial https://medium.com/@moodydev/create-a-custom-calendar-in-react-3df1bfd0b728
 * and customised by TTNT
 * date-fns doc: https://date-fns.org/v2.21.1/docs
 */
