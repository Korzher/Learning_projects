import React, { useState, useEffect, useRef, useCallback } from "react";

function CaveControls({ caveData: initialCaveData, onCaveDataChange }) {
  const [caveData, setCaveData] = useState(initialCaveData);
  const [settings, setSettings] = useState({
    birthLimit: 4,
    deathLimit: 3,
    chance: 0.4,
  });
  const [simulationSpeed, setSimulationSpeed] = useState(100);
  const [isSimulating, setIsSimulating] = useState(false);

  const caveDataRef = useRef(initialCaveData);
  const settingsRef = useRef(settings);
  const isSimulatingRef = useRef(false);
  const simulationTimerRef = useRef(null);

  useEffect(() => {
    caveDataRef.current = caveData;
  }, [caveData]);

  useEffect(() => {
    settingsRef.current = settings;
  }, [settings]);

  useEffect(() => {
    isSimulatingRef.current = isSimulating;
  }, [isSimulating]);

  useEffect(() => {
    setCaveData(initialCaveData);
  }, [initialCaveData]);

  useEffect(() => {
    if (onCaveDataChange && caveData) {
      onCaveDataChange(caveData);
    }
  }, [caveData, onCaveDataChange]);

  const step = useCallback(async () => {
    const currentCaveData = caveDataRef.current;
    const currentSettings = settingsRef.current;

    if (!currentCaveData || !window.go?.main?.App?.CaveStep) {
      return;
    }

    try {
      const response = await window.go.main.App.CaveStep(
        JSON.stringify(currentCaveData),
        currentSettings.birthLimit,
        currentSettings.deathLimit,
      );
      const newCave = JSON.parse(response);
      setCaveData(newCave);
    } catch (err) {
      console.error("Ошибка шага:", err);
      stopSimulation();
    }
  }, []);

  const simulationStep = useCallback(async () => {
    if (!isSimulatingRef.current) {
      return;
    }

    await step();

    if (isSimulatingRef.current && simulationTimerRef.current) {
      simulationTimerRef.current = setTimeout(simulationStep, simulationSpeed);
    }
  }, [step, simulationSpeed]);

  const startSimulation = useCallback(() => {
    if (!caveDataRef.current) {
      alert("Сначала загрузите пещеру");
      return;
    }

    if (isSimulatingRef.current) {
      return;
    }

    setIsSimulating(true);
    isSimulatingRef.current = true;

    simulationTimerRef.current = setTimeout(simulationStep, simulationSpeed);
  }, [simulationStep, simulationSpeed]);

  const stopSimulation = useCallback(() => {
    setIsSimulating(false);
    isSimulatingRef.current = false;

    if (simulationTimerRef.current) {
      clearTimeout(simulationTimerRef.current);
      simulationTimerRef.current = null;
    }
  }, []);

  const toggleSimulation = () => {
    if (isSimulating) {
      stopSimulation();
    } else {
      startSimulation();
    }
  };

  useEffect(() => {
    return () => {
      if (simulationTimerRef.current) {
        clearTimeout(simulationTimerRef.current);
      }
    };
  }, []);

  useEffect(() => {
    if (!caveData && isSimulating) {
      stopSimulation();
    }
  }, [caveData, isSimulating, stopSimulation]);

  if (!caveData) {
    return (
      <div
        style={{
          padding: "15px",
          border: "1px solid #9C27B0",
          marginBottom: "10px",
          backgroundColor: "#f9f9f9",
        }}
      >
        <h4>Управление пещерой</h4>
        <p style={{ color: "#666", fontSize: "14px" }}>
          Сначала загрузите пещеру
        </p>
      </div>
    );
  }

  return (
    <div
      style={{
        padding: "15px",
        border: "1px solid #9C27B0",
        marginBottom: "10px",
      }}
    >
      <h4>Управление пещерой</h4>
      <div style={{ marginBottom: "15px" }}>
        <strong>Пределы клеток:</strong>

        <div style={{ marginTop: "8px" }}>
          <label
            style={{ display: "block", fontSize: "13px", marginBottom: "5px" }}
          >
            Лимит рождения (0-7):
          </label>
          <input
            type="range"
            min="0"
            max="7"
            value={settings.birthLimit}
            onChange={(e) =>
              setSettings({
                ...settings,
                birthLimit: parseInt(e.target.value),
              })
            }
            style={{ width: "100%" }}
            disabled={isSimulating}
          />
          <div
            style={{
              display: "flex",
              justifyContent: "space-between",
              fontSize: "11px",
              color: "#666",
            }}
          >
            <span>0</span>
            <span>Текущее: {settings.birthLimit}</span>
            <span>7</span>
          </div>
        </div>

        <div style={{ marginTop: "12px" }}>
          <label
            style={{ display: "block", fontSize: "13px", marginBottom: "5px" }}
          >
            Лимит смерти (0-7):
          </label>
          <input
            type="range"
            min="0"
            max="7"
            value={settings.deathLimit}
            onChange={(e) =>
              setSettings({
                ...settings,
                deathLimit: parseInt(e.target.value),
              })
            }
            style={{ width: "100%" }}
            disabled={isSimulating}
          />
          <div
            style={{
              display: "flex",
              justifyContent: "space-between",
              fontSize: "11px",
              color: "#666",
            }}
          >
            <span>0</span>
            <span>Текущее: {settings.deathLimit}</span>
            <span>7</span>
          </div>
        </div>
      </div>

      <div style={{ display: "flex", gap: "5px", marginBottom: "10px" }}>
        <button
          onClick={step}
          disabled={isSimulating}
          style={{
            flex: 1,
            padding: "10px",
            backgroundColor: isSimulating ? "#ccc" : "#9C27B0",
            color: "white",
            border: "none",
            borderRadius: "4px",
            cursor: isSimulating ? "not-allowed" : "pointer",
            fontSize: "14px",
          }}
        >
          Следующий шаг
        </button>
      </div>

      <div
        style={{
          marginTop: "15px",
          paddingTop: "15px",
          borderTop: "1px solid #ccc",
        }}
      >
        <strong
          style={{ fontSize: "14px", marginBottom: "8px", display: "block" }}
        >
          Автоматическая симуляция:
        </strong>

        <div style={{ display: "flex", gap: "5px", marginBottom: "5px" }}>
          <button
            onClick={toggleSimulation}
            style={{
              flex: 1,
              padding: "10px",
              backgroundColor: isSimulating ? "#F44336" : "#9C27B0",
              color: "white",
              border: "none",
              borderRadius: "4px",
              cursor: "pointer",
              fontSize: "14px",
            }}
          >
            {isSimulating ? "Остановить симуляцию" : "Запустить симуляцию"}
          </button>

          <div style={{ display: "flex", alignItems: "center", gap: "5px" }}>
            <input
              type="number"
              min="50"
              max="5000"
              step="50"
              value={simulationSpeed}
              onChange={(e) => setSimulationSpeed(parseInt(e.target.value))}
              style={{
                width: "80px",
                padding: "6px",
                border: "1px solid #ccc",
                borderRadius: "4px",
                textAlign: "center",
                fontSize: "12px",
              }}
              disabled={isSimulating}
            />
            <span style={{ fontSize: "12px", color: "#666" }}>мс</span>
          </div>
        </div>

        <div
          style={{
            fontSize: "11px",
            color: "#666",
            fontStyle: "italic",
            marginTop: "5px",
          }}
        >
          {isSimulating
            ? `Симуляция активна (1 шаг в ${simulationSpeed}мс)`
            : "Симуляция остановлена"}
        </div>
      </div>
    </div>
  );
}

export default CaveControls;
