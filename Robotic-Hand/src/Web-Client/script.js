// Update slider values
const sliders = ['thumb', 'index', 'middle', 'ring', 'pinky', 'wrist'];

sliders.forEach(slider => {
    const input = document.getElementById(slider);
    const display = document.getElementById(slider + '-value');
    
    input.addEventListener('input', function() {
        display.textContent = this.value + '°';
        
        // Here you would send the value to your IoT device
        console.log(`${slider}: ${this.value}°`);
        
        // Optional: Send to backend/IoT device
        // sendToDevice(slider, this.value);
    });
});

// Reset all sliders to default positions
function resetAll() {
    document.getElementById('thumb').value = 90;
    document.getElementById('index').value = 90;
    document.getElementById('middle').value = 90;
    document.getElementById('ring').value = 90;
    document.getElementById('pinky').value = 90;
    document.getElementById('wrist').value = 0;
    
    sliders.forEach(slider => {
        const input = document.getElementById(slider);
        const display = document.getElementById(slider + '-value');
        display.textContent = input.value + '°';
    });
    
    console.log('All controls reset to default');
}

// Optional: Function to send data to IoT device
// Uncomment and modify based on your IoT setup
/*
function sendToDevice(finger, value) {
    // Example using fetch API
    fetch('/api/control', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({
            finger: finger,
            angle: value
        })
    })
    .then(response => response.json())
    .then(data => console.log('Success:', data))
    .catch((error) => console.error('Error:', error));
}
*/

// Initialize on page load
document.addEventListener('DOMContentLoaded', function() {
    console.log('IoT Robotic Hand Controller Ready');
    console.log('Available gestures: open, fist, point, peace, rock');
});