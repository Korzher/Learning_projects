import React, { useState } from "react";

function LoadPanel({ onLoad }) {
  const [filename, setFilename] = useState("maze.txt");

  const load = async () => {
    if (window.go?.main?.App?.LoadMaze) {
      try {
        const response = await window.go.main.App.LoadMaze(filename);
        const data = JSON.parse(response);
        onLoad(data);
      } catch (err) {
        alert("Ошибка загрузки: " + err.message);
      }
    }
  };

  return (
    <div
      style={{
        padding: "15px",
        border: "1px solid #FF9800",
        marginBottom: "10px",
      }}
    >
      <h4>Загрузка</h4>

      <div style={{ marginBottom: "10px" }}>
        <label
          style={{ display: "block", marginBottom: "5px", fontSize: "14px" }}
        >
          Имя файла:
        </label>
        <input
          type="text"
          value={filename}
          onChange={(e) => setFilename(e.target.value)}
          placeholder="maze.txt"
          style={{
            width: "100%",
            padding: "8px 12px",
            border: "1px solid #ddd",
            borderRadius: "4px",
            fontSize: "14px",
            boxSizing: "border-box",
          }}
        />
      </div>

      <button
        onClick={load}
        style={{
          width: "100%",
          padding: "10px",
          backgroundColor: "#FF9800",
          color: "white",
          border: "none",
          borderRadius: "4px",
          cursor: "pointer",
          fontSize: "14px",
          fontWeight: "500",
        }}
      >
        Загрузить лабиринт
      </button>
    </div>
  );
}

export default LoadPanel;
