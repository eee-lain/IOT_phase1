document.getElementById('temp-button').addEventListener('click', getTemperature);
document.getElementById('humid-button').addEventListener('click', getHumidity);

function getTemperature() {
  fetchThingSpeakData('field1', 'temp-data', 'Temperature');
}

function getHumidity() {
  fetchThingSpeakData('field2', 'humid-data', 'Humidity');
}

function fetchThingSpeakData(field, elementId, dataType) {
  const channelID = '2326366';
  const apiKey = 'W99IL4JFKFZKTP7L';
  const baseURL = `https://api.thingspeak.com/channels/${channelID}/feeds.json`;

  fetch(`${baseURL}?api_key=${apiKey}&results=1&${field}`)
    .then(response => response.json())
    .then(data => {
      const value = data.feeds[0][field];
      document.getElementById(elementId).textContent = `${dataType}: ${value}`;
    })
    .catch(error => {
      console.error(`Error fetching ${field} data:`, error);
      document.getElementById(elementId).textContent = `Error fetching ${dataType} data`;
    });
}

