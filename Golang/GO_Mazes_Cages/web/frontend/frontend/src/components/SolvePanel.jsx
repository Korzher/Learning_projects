import React, { useState, useEffect } from "react";

function SolvePanel({ mazeData, onSolve }) {
  const [start, setStart] = useState({ x: 0, y: 0 });
  const [end, setEnd] = useState({
    x: mazeData ? mazeData.width - 1 : 9,
    y: mazeData ? mazeData.height - 1 : 9,
  });

  useEffect(() => {
    if (mazeData) {
      const maxX = mazeData.width - 1;
      const maxY = mazeData.height - 1;

      setStart((prev) => ({
        x: Math.min(prev.x, maxX),
        y: Math.min(prev.y, maxY),
      }));

      setEnd((prev) => ({
        x: Math.min(prev.x, maxX),
        y: Math.min(prev.y, maxY),
      }));
    }
  }, [mazeData]);

  const clampValue = (value, max) => {
    if (value < 0) return 0;
    if (value > max) return max;
    return value;
  };

  const handleStartChange = (field, value) => {
    const numValue = parseInt(value) || 0;
    if (!mazeData) {
      setStart((prev) => ({ ...prev, [field]: numValue }));
      return;
    }

    const max = field === "x" ? mazeData.width - 1 : mazeData.height - 1;
    setStart((prev) => ({ ...prev, [field]: clampValue(numValue, max) }));
  };

  const handleEndChange = (field, value) => {
    const numValue = parseInt(value) || 0;
    if (!mazeData) {
      setEnd((prev) => ({ ...prev, [field]: numValue }));
      return;
    }

    const max = field === "x" ? mazeData.width - 1 : mazeData.height - 1;
    setEnd((prev) => ({ ...prev, [field]: clampValue(numValue, max) }));
  };

  const solve = async () => {
    if (!mazeData) {
      alert("Сначала загрузите или сгенерируйте лабиринт");
      return;
    }

    if (window.go?.main?.App?.Solve) {
      try {
        const response = await window.go.main.App.Solve(
          JSON.stringify(mazeData),
          start.x,
          start.y,
          end.x,
          end.y,
        );
        const path = JSON.parse(response);
        onSolve(path);
      } catch (err) {
        alert("Ошибка решения: " + err.message);
      }
    }
  };

  const buttonStyle = {
    width: "100%",
    padding: "10px",
    backgroundColor: "#9C27B0",
    color: "white",
    border: "none",
    borderRadius: "4px",
    cursor: "pointer",
    fontSize: "14px",
    fontWeight: "500",
  };

  const buttonDisabledStyle = {
    ...buttonStyle,
    backgroundColor: "#ccc",
    color: "#666",
    cursor: "not-allowed",
  };

  const inputStyle = {
    padding: "6px",
    border: "1px solid #ddd",
    borderRadius: "4px",
    fontSize: "13px",
    textAlign: "center",
    width: "100%",
    boxSizing: "border-box",
  };

  return (
    <div
      style={{
        padding: "15px",
        border: "1px solid #9C27B0",
        marginBottom: "10px",
      }}
    >
      <h4>Решение лабиринта</h4>

      <div style={{ marginBottom: "15px" }}>
        <div style={{ marginBottom: "10px" }}>
          <strong
            style={{ display: "block", marginBottom: "6px", fontSize: "14px" }}
          >
            Начальная точка:
          </strong>
          <div style={{ display: "flex", gap: "8px" }}>
            <div style={{ flex: 1 }}>
              <label
                style={{
                  display: "block",
                  fontSize: "12px",
                  marginBottom: "4px",
                  color: "#666",
                }}
              >
                Координата X:
              </label>
              <input
                type="number"
                value={start.x}
                onChange={(e) => handleStartChange("x", e.target.value)}
                min="0"
                max={mazeData ? mazeData.width - 1 : 49}
                style={inputStyle}
              />
            </div>
            <div style={{ flex: 1 }}>
              <label
                style={{
                  display: "block",
                  fontSize: "12px",
                  marginBottom: "4px",
                  color: "#666",
                }}
              >
                Координата Y:
              </label>
              <input
                type="number"
                value={start.y}
                onChange={(e) => handleStartChange("y", e.target.value)}
                min="0"
                max={mazeData ? mazeData.height - 1 : 49}
                style={inputStyle}
              />
            </div>
          </div>
        </div>

        <div>
          <strong
            style={{ display: "block", marginBottom: "6px", fontSize: "14px" }}
          >
            Конечная точка:
          </strong>
          <div style={{ display: "flex", gap: "8px" }}>
            <div style={{ flex: 1 }}>
              <label
                style={{
                  display: "block",
                  fontSize: "12px",
                  marginBottom: "4px",
                  color: "#666",
                }}
              >
                Координата X:
              </label>
              <input
                type="number"
                value={end.x}
                onChange={(e) => handleEndChange("x", e.target.value)}
                min="0"
                max={mazeData ? mazeData.width - 1 : 49}
                style={inputStyle}
              />
            </div>
            <div style={{ flex: 1 }}>
              <label
                style={{
                  display: "block",
                  fontSize: "12px",
                  marginBottom: "4px",
                  color: "#666",
                }}
              >
                Координата Y:
              </label>
              <input
                type="number"
                value={end.y}
                onChange={(e) => handleEndChange("y", e.target.value)}
                min="0"
                max={mazeData ? mazeData.height - 1 : 49}
                style={inputStyle}
              />
            </div>
          </div>
        </div>
      </div>

      <button
        onClick={solve}
        disabled={!mazeData}
        style={mazeData ? buttonStyle : buttonDisabledStyle}
      >
        Найти путь
      </button>

      {!mazeData && (
        <div
          style={{
            fontSize: "11px",
            color: "#666",
            marginTop: "10px",
            fontStyle: "italic",
          }}
        >
          Сначала загрузите или сгенерируйте лабиринт
        </div>
      )}
    </div>
  );
}

export default SolvePanel;
