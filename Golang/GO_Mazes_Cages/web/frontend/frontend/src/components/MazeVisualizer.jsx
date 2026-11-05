import React from "react";

function MazeVisualizer({ mazeData, solutionPath = [] }) {
  if (!mazeData?.cells) return null;
  const { width, height, cells } = mazeData;
  const wallThickness = 2;
  const cellWidth = 500 / width;
  const cellHeight = 500 / height;

  return (
    <div style={{ marginTop: "20px", position: "relative" }}>
      <h4>
        Лабиринт {width}x{height} (путь: {solutionPath.length} точек)
      </h4>

      <div
        style={{
          width: "500px",
          height: "500px",
          backgroundColor: "#f0f8ff",
          display: "grid",
          gridTemplateColumns: `repeat(${width}, 1fr)`,
          gridTemplateRows: `repeat(${height}, 1fr)`,
          borderTop: `${wallThickness}px solid black`,
          borderLeft: `${wallThickness}px solid black`,
          position: "relative",
        }}
      >
        {cells.map((row, y) =>
          row.map((cell, x) => (
            <div
              key={`${x}-${y}`}
              style={{
                borderRight: cell.Right
                  ? `${wallThickness}px solid black`
                  : "none",
                borderBottom: cell.Bottom
                  ? `${wallThickness}px solid black`
                  : "none",
                boxSizing: "border-box",
                backgroundColor: "rgba(255,255,255,0.3)",
              }}
            />
          ))
        )}

        {solutionPath.length > 0 && (
          <svg
            style={{
              position: "absolute",
              top: 0,
              left: 0,
              width: "500px",
              height: "500px",
              pointerEvents: "none",
              zIndex: 100,
            }}
          >
            <polyline
              points={solutionPath
                .map(
                  ([x, y]) =>
                    `${(x + 0.5) * cellWidth},${(y + 0.5) * cellHeight}`
                )
                .join(" ")}
              stroke="#FF5722"
              strokeWidth="3"
              fill="none"
              strokeLinecap="round"
              strokeLinejoin="round"
            />

            {solutionPath[0] && (
              <circle
                cx={(solutionPath[0][0] + 0.5) * cellWidth}
                cy={(solutionPath[0][1] + 0.5) * cellHeight}
                r="6"
                fill="#4CAF50"
                stroke="white"
                strokeWidth="2"
              />
            )}

            {solutionPath[solutionPath.length - 1] && (
              <circle
                cx={
                  (solutionPath[solutionPath.length - 1][0] + 0.5) * cellWidth
                }
                cy={
                  (solutionPath[solutionPath.length - 1][1] + 0.5) * cellHeight
                }
                r="6"
                fill="#F44336"
                stroke="white"
                strokeWidth="2"
              />
            )}
          </svg>
        )}
      </div>
      {solutionPath.length > 0 && (
        <div style={{ fontSize: "12px", color: "#666", marginTop: "5px" }}>
          Путь: [{solutionPath.map((p) => `(${p[0]},${p[1]})`).join(" → ")}]
        </div>
      )}
    </div>
  );
}

export default MazeVisualizer;
