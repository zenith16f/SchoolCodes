async function getApod() {
  const apiKey = "XgSTMKHNzWWoBqKyrgDnNVGuvB83bwRbZDCMBjqB";
  const url = `https://api.nasa.gov/planetary/apod?api_key=${apiKey}`;

  const response = await fetch(url);
  const data = await response.json();

  document.getElementById("nasa-title").innerHTML = data.title;
  document.getElementById("nasa-image").src = data.url;
  document.getElementById("nasa-info").innerHTML = data.explanation;
  document.getElementById("nasa-content").style.display = "block";
}
