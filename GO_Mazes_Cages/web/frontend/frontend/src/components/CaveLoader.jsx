import React, { useState } from "react";

function CaveLoader({ onCaveLoaded }) {
  const [filename, setFilename] = useState("cave.txt");
  const [isLoading, setIsLoading] = useState(false);

  const loadCave = async () => {
    if (!filename.trim()) {
      alert("Введите имя файла");
      return;
    }

    if (!window.go?.main?.App?.LoadCave) {
      alert("Функция загрузки пещер недоступна");
      return;
    }

    setIsLoading(true);
    try {
      const response = await window.go.main.App.LoadCave(filename);

      if (response.startsWith("ERROR: ")) {
        alert(response.substring(7));
        return;
      }

      const lines = response.trim().split("\n");
      const [height, width] = lines[0].split(" ").map(Number);

      const cells = [];
      for (let i = 1; i <= height && i < lines.length; i++) {
        const row = lines[i].split(" ").map((num) => parseInt(num));
        cells.push(row);
      }

      const caveData = {
        width: width,
        height: height,
        cells: cells,
        type: "cave",
      };

      onCaveLoaded(caveData);
      setFilename("");
    } catch (err) {
      alert("Ошибка: " + err.message);
    } finally {
      setIsLoading(false);
    }
  };

  return (
    <div
      style={{
        padding: "15px",
        border: "1px solid #9C27B0",
        marginBottom: "10px",
      }}
    >
      <h4>Загрузка пещеры</h4>

      <div style={{ marginBottom: "10px" }}>
        <label
          style={{ display: "block", marginBottom: "5px", fontSize: "14px" }}
        >
          Имя файла пещеры:
        </label>
        <input
          type="text"
          value={filename}
          onChange={(e) => setFilename(e.target.value)}
          placeholder="Например: cave.txt"
          style={{
            width: "80%",
            padding: "8px 12px",
            border: "1px solid #ddd",
            borderRadius: "4px",
            fontSize: "14px",
          }}
        />
      </div>

      <button
        onClick={loadCave}
        disabled={isLoading}
        style={{
          width: "100%",
          padding: "10px",
          backgroundColor: isLoading ? "#ccc" : "#9C27B0",
          color: "white",
          border: "none",
          borderRadius: "4px",
          cursor: isLoading ? "not-allowed" : "pointer",
          fontSize: "14px",
        }}
      >
        {isLoading ? "Загрузка..." : "Загрузить пещеру"}
      </button>
    </div>
  );
}

export default CaveLoader;
