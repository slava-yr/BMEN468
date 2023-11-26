// Elements for sensor readings
// const tempElement = document.getElementById("temp");
// const humElement = document.getElementById("hum");
// const presElement = document.getElementById("pres");

// Database Paths
var dataHumPath = 'test/Humidity';
var dataTempPath = 'test/Temperature';

// Get a database reference 
const databaseHum = database.ref(dataHumPath);
const databaseTemp = database.ref(dataTempPath);

// Variables to save database current values
var humReading;
var tempReading;

// Attach an asynchronous callback to read the data
databaseHum.on('value', (snapshot) => {
  humReading = snapshot.val();
  console.log(humReading);
  document.getElementById("hum").innerHTML = humReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

databaseTemp.on('value', (snapshot) => {
  tempReading = snapshot.val();
  console.log(tempReading);
  document.getElementById("temp").innerHTML = tempReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});