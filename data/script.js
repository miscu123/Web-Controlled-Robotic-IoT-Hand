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

function setGesture(name) {
    fetch("/gesture?name=" + name);
}
