let secreto = Math.floor(Math.random() * 10 + 1);
let intentosRestantes = 5;

function dibujarIntentos() {
  let tries = document.getElementById("intentos");
  tries.innerHTML = "";

  for (let index = 0; index < intentosRestantes; index++) {
    const cuadro = document.createElement("div");
    cuadro.className = "cuadro";
    tries.appendChild(cuadro);
  }
}

dibujarIntentos();

const jugar = () => {
  let inputElement = document.getElementById("numero");
  let numero = parseInt(inputElement.value);
  let resultado = document.getElementById("resultado");

  if (isNaN(numero) || numero < 1 || numero > 10) {
    resultado.textContent = "Ingresa un número válido del 1 al 10.";
    return;
  }

  if (numero === secreto) {
    resultado.textContent = "¡Correcto...!!! El número era " + secreto;

    document
      .querySelectorAll(".cuadro")
      .forEach((c) => (c.className = "cuadro acierto"));
    terminarJuego(inputElement);
  } else {
    intentosRestantes--;

    if (intentosRestantes > 0) {
      resultado.textContent = `No, te quedan ${intentosRestantes} intentos.`;
      dibujarIntentos();
    }
    while (intentosRestantes == 0) {
      resultado.textContent = `¡Te quedaste sin vidas! El número secreto era ${secreto}.`;
      dibujarIntentos();
      terminarJuego(inputElement);
      break;
    }
  }
};

function terminarJuego(inputElement) {
  inputElement.disabled = true;
  document.querySelector("button").disabled = true;
}
