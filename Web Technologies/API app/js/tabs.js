function mostrarSeccion(id) {
  document.querySelectorAll(".seccion").forEach(function (sec) {
    sec.classList.remove("visible");
  });

  document.querySelectorAll(".tab").forEach(function (tab) {
    tab.classList.remove("active");
  });

  document.getElementById(id).classList.add("visible");

  event.target.classList.add("active");
}
