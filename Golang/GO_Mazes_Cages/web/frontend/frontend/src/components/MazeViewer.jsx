import React from "react";
import MazeVisualizer from "./MazeVisualizer";

function MazeViewer({ mazeData, solutionPath }) {
  return (
    <div style={{ flex: 1, padding: "20px" }}>
      <h2>Лабиринт</h2>
      {mazeData ? (
        <MazeVisualizer mazeData={mazeData} solutionPath={solutionPath} />
      ) : (
        <p>Лабиринт не загружен</p>
      )}
    </div>
  );
}

export default MazeViewer;
