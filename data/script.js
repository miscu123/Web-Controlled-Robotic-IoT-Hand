async function setGesture(name) {
    try {
        const response = await fetch("/gesture?name=" + encodeURIComponent(name));
        if (!response.ok) throw new Error(response.statusText);
        console.log("Gesture queued:", name);
    } catch (err) {
        console.error("Gesture request failed:", err);
    }

    if (name === 'reset') {
        ['thumb','index','middle','ring','pinky'].forEach(finger => {
            const slider = document.getElementById(finger);
            const display = document.getElementById(finger + '-value');
            if (slider && display) {
                slider.value = 0;
                display.textContent = '0°';
            }
        });
    }
}

async function setFingerAngle(finger, angle) {
    const display = document.getElementById(finger + '-value');
    if (display) display.textContent = angle + '°';

    try {
        const response = await fetch(`/finger?finger=${encodeURIComponent(finger)}&angle=${angle}`);
        if (!response.ok) throw new Error(response.statusText);
        console.log(`Finger ${finger} queued: ${angle}°`);
    } catch (err) {
        console.error("Finger request failed:", err);
    }
}