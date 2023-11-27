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

// Set a threshold for color change (move it to the global scope)
const threshold = 50;

// Attach an asynchronous callback to read the data
databaseHum.on('value', (snapshot) => {
  humReading = snapshot.val();
  console.log(humReading);
  document.getElementById("hum").innerHTML = humReading;

  if (humReading !== undefined && tempReading !== undefined) {
    updateBackgroundColor(humReading, tempReading);
  }
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

databaseTemp.on('value', (snapshot) => {
  tempReading = snapshot.val();
  console.log(tempReading);
  document.getElementById("temp").innerHTML = tempReading;

  if (humReading !== undefined && tempReading !== undefined) {
    updateBackgroundColor(humReading, tempReading);
  }
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

function updateBackgroundColor(humReading, tempReading) {
  console.log('Humidity:', humReading);
  console.log('Temperature:', tempReading);

  if (humReading > threshold || tempReading > threshold) {
    console.log('Changing background color to red');
    document.body.style.backgroundColor = '#CE2029';
  } else {
    console.log('Changing background color to green');
    document.body.style.backgroundColor = '#32CD32';
  }
}
