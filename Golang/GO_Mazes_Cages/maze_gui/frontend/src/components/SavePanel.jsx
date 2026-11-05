import React, { useState } from "react";

function SavePanel({ mazeData }) {
  const [filename, setFilename] = useState("maze.txt");

  const save = async () => {
    if (!mazeData) {
      alert("Нет лабиринта для сохранения");
      return;
    }
    if (window.go?.main?.App?.SaveMaze) {
      try {
        const response = await window.go.main.App.SaveMaze(
          JSON.stringify(mazeData),
          filename,
        );
        alert(response);
      } catch (err) {
        alert("Ошибка сохранения: " + err.message);
      }
    }
  };

  const buttonStyle = {
    padding: "8px 16px",
    backgroundColor: "#2196F3",
    color: "white",
    border: "none",
    borderRadius: "4px",
    cursor: "pointer",
    fontSize: "14px",
  };

  const buttonDisabledStyle = {
    ...buttonStyle,
    backgroundColor: "#ccc",
    color: "#666",
    cursor: "not-allowed",
  };

  return (
    <div
      style={{
        padding: "15px",
        border: "1px solid #2196F3",
        marginBottom: "10px",
      }}
    >
      <h4>Сохранение</h4>

      <div style={{ marginBottom: "10px" }}>
        <label style={{ display: "block", marginBottom: "5px" }}>
          Имя файла:
        </label>
        <input
          type="text"
          value={filename}
          onChange={(e) => setFilename(e.target.value)}
          style={{
            width: "100%",
            padding: "8px",
            border: "1px solid #ddd",
            borderRadius: "4px",
            boxSizing: "border-box",
          }}
        />
      </div>

      <button
        onClick={save}
        style={mazeData ? buttonStyle : buttonDisabledStyle}
        disabled={!mazeData}
      >
        Сохранить лабиринт
      </button>
    </div>
  );
}

export default SavePanel;
