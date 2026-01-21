const backend = {
  Generate: async (width, height) => {
    try {
      const response = await fetch("/api/generate", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ width, height }),
      });
      return await response.text();
    } catch (error) {
      console.error("Generate error:", error);
      return JSON.stringify({ error: error.message });
    }
  },

  SaveMaze: async (jsonStr, filename) => {
    try {
      const response = await fetch("/api/save-maze", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ jsonStr, filename }),
      });
      return await response.text();
    } catch (error) {
      console.error("SaveMaze error:", error);
      return "Ошибка: " + error.message;
    }
  },

  LoadMaze: async (filename) => {
    try {
      const response = await fetch("/api/load-maze", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ filename }),
      });
      return await response.text();
    } catch (error) {
      console.error("LoadMaze error:", error);
      return JSON.stringify({ error: error.message });
    }
  },

  Solve: async (jsonStr, startX, startY, endX, endY) => {
    try {
      const response = await fetch("/api/solve", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ jsonStr, startX, startY, endX, endY }),
      });
      return await response.text();
    } catch (error) {
      console.error("Solve error:", error);
      return JSON.stringify({ error: error.message });
    }
  },

  LoadCave: async (filename) => {
    try {
      const response = await fetch("/api/load-cave", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ filename }),
      });
      return await response.text();
    } catch (error) {
      console.error("LoadCave error:", error);
      return "ERROR: " + error.message;
    }
  },

  CaveStep: async (jsonStr, birthLimit, deathLimit) => {
    try {
      const response = await fetch("/api/cave-step", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ jsonStr, birthLimit, deathLimit }),
      });
      return await response.text();
    } catch (error) {
      console.error("CaveStep error:", error);
      return JSON.stringify({ error: error.message });
    }
  },

  CreateRandomCave: async (width, height, chance) => {
    try {
      const response = await fetch("/api/create-random-cave", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ width, height, chance }),
      });
      return await response.text();
    } catch (error) {
      console.error("CreateRandomCave error:", error);
      return "ERROR: " + error.message;
    }
  },
};

window.go = { main: { App: backend } };
window.Events = { On: () => {} };
