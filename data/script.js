function setGesture(name) {
    fetch("/gesture?name=" + name);
}

function setFingerAngle(finger, angle) {
    document.getElementById(finger + '-value').textContent = angle + '°';

    fetch(`/finger?finger=${finger}&angle=${angle}`);
}