import React, { useState } from "react";

function GeneratePanel({ onGenerate }) {
  const [width, setWidth] = useState(10);
  const [height, setHeight] = useState(10);

  const generate = async () => {
    if (window.go?.main?.App?.Generate) {
      try {
        const response = await window.go.main.App.Generate(width, height);
        const data = JSON.parse(response);
        onGenerate(data);
      } catch (err) {
        alert("Ошибка генерации: " + err.message);
      }
    }
  };

  return (
    <div
      style={{
        padding: "15px",
        border: "1px solid #4CAF50",
        marginBottom: "10px",
      }}
    >
      <h4>Генерация</h4>

      <div style={{ marginBottom: "8px" }}>
        <div style={{ display: "flex", alignItems: "center" }}>
          <label style={{ width: "80px" }}>Ширина:</label>
          <input
            type="number"
            value={width}
            onChange={(e) => setWidth(Number(e.target.value))}
            style={{ flex: 1, padding: "5px" }}
          />
        </div>
      </div>

      <div style={{ marginBottom: "12px" }}>
        <div style={{ display: "flex", alignItems: "center" }}>
          <label style={{ width: "80px" }}>Высота:</label>
          <input
            type="number"
            value={height}
            onChange={(e) => setHeight(Number(e.target.value))}
            style={{ flex: 1, padding: "5px" }}
          />
        </div>
      </div>

      <button
        onClick={generate}
        style={{
          width: "100%",
          padding: "8px",
          backgroundColor: "#4CAF50",
          color: "white",
          border: "none",
          borderRadius: "4px",
          cursor: "pointer",
          fontSize: "14px",
        }}
      >
        Сгенерировать
      </button>
    </div>
  );
}

export default GeneratePanel;
