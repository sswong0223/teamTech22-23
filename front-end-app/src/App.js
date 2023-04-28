import "./index.css";
import { useState } from "react";
import Calendar from "./Calendar";
import Details from "./Details";
import logo from "./images/sweCaciLogo.png";
import showEvents from "./Event";

export default function App() {
  const [showDetails, setShowDetails] = useState(false);
  const [data, setData] = useState(null);
  const showDetailsHandle = (dayStr) => {
    setData(dayStr);
    setShowDetails(true);
  };

  return (
    <div className="App">
      <h1>CACI Satellite Schedule</h1>
      <br />
      <Calendar showDetailsHandle={showDetailsHandle} />
      <br />
      <div className="Events">
        {showDetails && <Details data={data} />}
        {showEvents()}
      </div>
      <div className="Footer">
        <img src={logo} width={'100'}/>
      </div>
    </div>
  );
}