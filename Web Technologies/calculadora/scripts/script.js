//Funcion para insertar numeros o letras
//
insertar = (valor) => {
  document.getElementById("Pantalla").value += valor;
};
// funcion para limpiar
limpiar = () => {
  document.getElementById("Pantalla").value = "";
};

regresar = () => {
  let pantalla = document.getElementById("Pantalla").value;
  document.getElementById("Pantalla").value = pantalla.slice(0, -1);
};
// funcion para calcular el resultado
calcular = () => {
  try {
    let resultado = eval(document.getElementById("Pantalla").value);
    document.getElementById("Pantalla").value = resultado;
  } catch (e) {
    document.getElementById("Pantalla").value = "Error";
    console.log(e);
  }
};

// funcion para calcular raiz cuadrada
raiz = () => {
  try {
    let pantalla = document.getElementById("Pantalla");
    let valor = eval(pantalla.value);
    pantalla.value = Math.sqrt(valor);
  } catch (e) {
    document.getElementById("Pantalla").value = "Error";
  }
};

// funcion para cambiar signo positivo/negativo
cambiarSigno = () => {
  let pantalla = document.getElementById("Pantalla");
  if (pantalla.value !== "" && pantalla.value !== "0") {
    if (pantalla.value.startsWith("-")) {
      pantalla.value = pantalla.value.slice(1);
    } else {
      pantalla.value = "-" + pantalla.value;
    }
  }
};
//funcion para cambiar tema
document.getElementById("toggleTema").addEventListener("click", () => {
  const calculadora = document.querySelector(".calculadora");
  if (calculadora.classList.contains("oscuro")) {
    calculadora.classList.remove("oscuro");
    calculadora.classList.add("claro");
  } else {
    calculadora.classList.remove("claro");
    calculadora.classList.add("oscuro");
  }
});
