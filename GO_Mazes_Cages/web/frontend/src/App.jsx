import React, { useState } from "react";
import MazeViewer from "./components/MazeViewer";
import GeneratePanel from "./components/GeneratePanel";
import SavePanel from "./components/SavePanel";
import LoadPanel from "./components/LoadPanel";
import SolvePanel from "./components/SolvePanel";
import CaveLoader from "./components/CaveLoader";
import CaveControls from "./components/CaveControls";
import CaveViewer from "./components/CaveViewer";

function App() {
  const [mazeData, setMazeData] = useState(null);
  const [solutionPath, setSolutionPath] = useState([]);
  const [mode, setMode] = useState("maze");
  const [caveData, setCaveData] = useState(null);
  const [isSimulating, setIsSimulating] = useState(false);

  return (
    <div style={{ display: "flex", minHeight: "500px" }}>
      <div
        style={{
          flex: 0,
          padding: "20px",
          borderRight: "1px solid #ccc",
          minWidth: "350px",
          maxWidth: "350px",
        }}
      >
        <h1>Управление</h1>
        <div
          style={{
            marginBottom: "20px",
            display: "flex",
            gap: "5px",
          }}
        >
          <button
            onClick={() => {
              setMode("maze");
              setIsSimulating(false);
            }}
            style={{
              padding: "10px",
              backgroundColor: mode === "maze" ? "#9C27B0" : "#f5f5f5",
              color: mode === "maze" ? "white" : "#333",
              border: "1px solid #ccc",
              borderRadius: "4px",
              cursor: "pointer",
              fontSize: "14px",
              flex: 1,
            }}
          >
            Лабиринты
          </button>
          <button
            onClick={() => setMode("cave")}
            style={{
              padding: "10px",
              backgroundColor: mode === "cave" ? "#9C27B0" : "#f5f5f5",
              color: mode === "cave" ? "white" : "#333",
              border: "1px solid #ccc",
              borderRadius: "4px",
              cursor: "pointer",
              fontSize: "14px",
              flex: 1,
            }}
          >
            Пещеры
          </button>
        </div>

        {mode === "maze" ? (
          <>
            <GeneratePanel 
              onGenerate={(data) => {
              setMazeData(data);
              setSolutionPath([]);
            }} 
            />
            <SavePanel mazeData={mazeData} />
            <LoadPanel onLoad={setMazeData} />
            <SolvePanel mazeData={mazeData} onSolve={setSolutionPath} />
          </>
        ) : (
          <>
            <CaveLoader onCaveLoaded={setCaveData} />
            <CaveControls caveData={caveData} onCaveDataChange={setCaveData} />
          </>
        )}
      </div>
      {mode === "maze" ? (
        <MazeViewer mazeData={mazeData} solutionPath={solutionPath} />
      ) : (
        <CaveViewer caveData={caveData} isSimulating={isSimulating} />
      )}
    </div>
  );
}

export default App;
