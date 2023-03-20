import "./index.css";
import { useState } from "react";
import Calendar from "./Calendar";
import Details from "./Details";

export default function App() {
  const [showDetails, setShowDetails] = useState(false);
  const [data, setData] = useState(null);

  const showDetailsHandle = (dayStr) => {
    setData(dayStr);
    setShowDetails(true);
  };

  return (
    <div className="App">
      <h1>Week View Calendar</h1>
      <br />
      <Calendar showDetailsHandle={showDetailsHandle} />
      <br />
      {showDetails && <Details data={data} />}
    </div>
  );
}

/**
 * Follow this tutorial https://medium.com/@moodydev/create-a-custom-calendar-in-react-3df1bfd0b728
 * and customised by TTNT
 * date-fns doc: https://date-fns.org/v2.21.1/docs
 */
