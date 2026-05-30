async function getClima() {
  const apiKey = "dd76dc0c2e06f8e555078a4beb9e094f";
  const ciudad = document.getElementById("ciudad").value.trim();

  const errorEl = document.getElementById("clima-error");
  const contentEl = document.getElementById("clima-content");

  if (!ciudad) {
    errorEl.textContent = "Ingresa el nombre de una ciudad.";
    errorEl.style.display = "block";
    contentEl.style.display = "none";
    return;
  }

  errorEl.style.display = "none";

  try {
    const url = `https://api.openweathermap.org/data/2.5/weather?q=${encodeURIComponent(ciudad)}&appid=${apiKey}&units=metric&lang=es`;

    const response = await fetch(url);

    if (!response.ok) {
      throw new Error("Ciudad no encontrada");
    }

    const data = await response.json();

    document.getElementById("clima-icon").src =
      `https://openweathermap.org/img/wn/${data.weather[0].icon}@2x.png`;
    document.getElementById("clima-ciudad").textContent =
      `${data.name}, ${data.sys.country}`;
    document.getElementById("clima-desc").textContent =
      data.weather[0].description;
    document.getElementById("clima-temp").textContent =
      `${Math.round(data.main.temp)}°C`;
    document.getElementById("clima-sensacion").textContent =
      `${Math.round(data.main.feels_like)}°C`;
    document.getElementById("clima-humedad").textContent =
      `${data.main.humidity}%`;
    document.getElementById("clima-viento").textContent =
      `${data.wind.speed} m/s`;
    document.getElementById("clima-minmax").textContent =
      `${Math.round(data.main.temp_min)}° / ${Math.round(data.main.temp_max)}°`;

    contentEl.style.display = "block";
  } catch (error) {
    errorEl.textContent =
      "No se encontró la ciudad. Verifica el nombre e intenta de nuevo.";
    errorEl.style.display = "block";
    contentEl.style.display = "none";
  }
}

document.getElementById("ciudad").addEventListener("keydown", function (e) {
  if (e.key === "Enter") getClima();
});
