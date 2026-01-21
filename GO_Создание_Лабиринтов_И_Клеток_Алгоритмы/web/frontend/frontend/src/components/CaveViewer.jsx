import React, { useEffect, useRef, useState } from "react";

function CaveViewer({ caveData, isSimulating }) {
  const canvasRef = useRef(null);
  const [cellSize, setCellSize] = useState(10);

  useEffect(() => {
    if (!caveData || !caveData.cells) return;

    const canvas = canvasRef.current;
    const ctx = canvas.getContext("2d");

    ctx.clearRect(0, 0, 500, 500);

    const maxWidth = 500;
    const maxHeight = 500;
    const cellW = Math.floor(maxWidth / caveData.width);
    const cellH = Math.floor(maxHeight / caveData.height);
    const size = Math.min(cellW, cellH);
    setCellSize(size);

    for (let y = 0; y < caveData.height; y++) {
      for (let x = 0; x < caveData.width; x++) {
        const cell = caveData.cells[y]?.[x];

        if (cell === 1) {
          ctx.fillStyle = "#333";
          ctx.fillRect(x * size, y * size, size, size);
        } else {
          ctx.fillStyle = "#fff";
          ctx.fillRect(x * size, y * size, size, size);
        }

        ctx.strokeStyle = "#e0e0e0";
        ctx.strokeRect(x * size, y * size, size, size);
      }
    }
  }, [caveData, isSimulating, cellSize]);

  if (!caveData) {
    return (
      <div
        style={{
          flex: 1,
          display: "flex",
          alignItems: "center",
          justifyContent: "center",
          border: "2px solid #9C27B0",
          margin: "20px",
          borderRadius: "8px",
          backgroundColor: "#f9f9f9",
        }}
      >
        <div style={{ textAlign: "center", color: "#666" }}>
          <h3 style={{ color: "#9C27B0" }}>Визуализатор пещер</h3>
          <p>Загрузите пещеру из файла для отображения</p>
          <p style={{ fontSize: "12px", color: "#666", fontStyle: "italic" }}>
            Максимальный размер: 50×50
          </p>
        </div>
      </div>
    );
  }

  return (
    <div style={{ flex: 1, padding: "20px" }}>
      <div
        style={{
          border: "2px solid #9C27B0",
          borderRadius: "8px",
          padding: "15px",
          backgroundColor: "#fff",
        }}
      >
        <div
          style={{
            display: "flex",
            justifyContent: "space-between",
            alignItems: "center",
            marginBottom: "10px",
          }}
        >
          <h3 style={{ margin: 0, color: "#9C27B0" }}>Визуализация пещеры</h3>
          <div
            style={{
              fontSize: "12px",
              color: "#666",
              backgroundColor: "#f5f5f5",
              padding: "4px 8px",
              borderRadius: "4px",
            }}
          >
            Клетка: {cellSize}px | {caveData.width}×{caveData.height}
          </div>
        </div>

        <div
          style={{
            border: "1px solid #ddd",
            borderRadius: "4px",
            overflow: "hidden",
            backgroundColor: "#fff",
          }}
        >
          <canvas
            ref={canvasRef}
            width={500}
            height={500}
            style={{
              display: "block",
              margin: "0 auto",
              backgroundColor: "white",
            }}
          />
        </div>

        <div
          style={{
            marginTop: "15px",
            fontSize: "12px",
            color: "#666",
            display: "flex",
            justifyContent: "center",
            gap: "30px",
          }}
        >
          <div style={{ display: "flex", alignItems: "center", gap: "5px" }}>
            <div
              style={{
                width: "15px",
                height: "15px",
                backgroundColor: "#333",
                border: "1px solid #666",
              }}
            ></div>
            <span>Живая клетка</span>
          </div>
          <div style={{ display: "flex", alignItems: "center", gap: "5px" }}>
            <div
              style={{
                width: "15px",
                height: "15px",
                backgroundColor: "#fff",
                border: "1px solid #e0e0e0",
              }}
            ></div>
            <span>Мёртвая клетка</span>
          </div>
        </div>
      </div>
    </div>
  );
}

export default CaveViewer;
