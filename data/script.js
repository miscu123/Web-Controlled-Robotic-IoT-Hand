function setGesture(name) {
    fetch("/gesture?name=" + name);

    const fingers = ['thumb', 'index', 'middle', 'ring', 'pinky'];

    if (name === 'reset') {
        fingers.forEach(finger => {
            const slider = document.getElementById(finger);
            const display = document.getElementById(finger + '-value');
            slider.value = 0;          
            display.textContent = '0°'; 
        });
    }
}

function setFingerAngle(finger, angle) {
    document.getElementById(finger + '-value').textContent = angle + '°';

    fetch(`/finger?finger=${finger}&angle=${angle}`);
}