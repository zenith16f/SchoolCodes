async function getPokemon() {
  const input = document
    .getElementById("pokemon-input")
    .value.trim()
    .toLowerCase();

  const errorEl = document.getElementById("pokemon-error");
  const contentEl = document.getElementById("pokemon-content");

  if (!input) {
    errorEl.textContent = "Ingresa el nombre o número de un Pokémon.";
    errorEl.style.display = "block";
    contentEl.style.display = "none";
    return;
  }

  errorEl.style.display = "none";

  try {
    const url = `https://pokeapi.co/api/v2/pokemon/${encodeURIComponent(input)}`;
    const response = await fetch(url);

    if (!response.ok) {
      throw new Error("Pokémon no encontrado");
    }

    const data = await response.json();

    document.getElementById("pokemon-img").src =
      data.sprites.other["official-artwork"].front_default ||
      data.sprites.front_default;

    document.getElementById("pokemon-nombre").textContent = data.name;
    document.getElementById("pokemon-id").textContent =
      `#${String(data.id).padStart(3, "0")}`;

    const tiposContainer = document.getElementById("pokemon-tipos");
    tiposContainer.innerHTML = "";
    data.types.forEach(function (t) {
      const span = document.createElement("span");
      span.className = `tipo-badge tipo-${t.type.name}`;
      span.textContent = t.type.name;
      tiposContainer.appendChild(span);
    });

    document.getElementById("pokemon-altura").textContent =
      `${(data.height / 10).toFixed(1)} m`;
    document.getElementById("pokemon-peso").textContent =
      `${(data.weight / 10).toFixed(1)} kg`;
    document.getElementById("pokemon-exp").textContent =
      data.base_experience || "—";

    const habilidades = data.abilities
      .map(function (a) {
        return a.ability.name;
      })
      .join(", ");
    document.getElementById("pokemon-habilidades").textContent = habilidades;

    const statsContainer = document.getElementById("pokemon-stats-bars");
    statsContainer.innerHTML = "";

    const statNames = {
      hp: "HP",
      attack: "ATK",
      defense: "DEF",
      "special-attack": "SP.ATK",
      "special-defense": "SP.DEF",
      speed: "SPD",
    };

    data.stats.forEach(function (s) {
      const valor = s.base_stat;
      const porcentaje = Math.min((valor / 255) * 100, 100);
      const nombre = statNames[s.stat.name] || s.stat.name;

      const row = document.createElement("div");
      row.className = "stat-row";
      row.innerHTML =
        `<span class="stat-name">${nombre}</span>` +
        `<div class="stat-bar-bg"><div class="stat-bar-fill" style="width: ${porcentaje}%"></div></div>` +
        `<span class="stat-value">${valor}</span>`;

      statsContainer.appendChild(row);
    });

    contentEl.style.display = "block";
  } catch (error) {
    errorEl.textContent =
      "Pokémon no encontrado. Verifica el nombre o número e intenta de nuevo.";
    errorEl.style.display = "block";
    contentEl.style.display = "none";
  }
}

document
  .getElementById("pokemon-input")
  .addEventListener("keydown", function (e) {
    if (e.key === "Enter") getPokemon();
  });
