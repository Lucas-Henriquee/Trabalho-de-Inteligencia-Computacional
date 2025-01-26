const planes = Array.from({ length: 12 }, (_, i) => i + 1)
    .sort(() => Math.random() - 0.5) 
    .map((id, index) => ({
        id,
        initial_delay: index * 1.5 + Math.random() * 2, 
        target_time: Math.floor(Math.random() * 30) + 20
    }));

let timer = 0;
let timerInterval;
let landingCount = 0;
const container = document.querySelector('.main-container');
const runway = document.querySelector('.runway');
const timerDisplay = document.querySelector('.timer');
let runwayClear = true;

function createPlaneElement(plane, altitudeOffset) {
    const div = document.createElement('div');
    div.className = 'plane waiting';
    div.id = 'plane-' + plane.id;
    div.textContent = `✈️${plane.id}`;
    div.style.top = `${30 + altitudeOffset}px`;
    div.style.left = `${runway.offsetLeft}px`;
    container.appendChild(div);
    return div;
}

function moveHorizontallyWithinRunway(planeElem, callback) {
    let posX = runway.offsetLeft;
    let direction = 2;

    const interval = setInterval(() => {
        posX += direction * 2.75;
        if (posX >= runway.offsetLeft + runway.offsetWidth - 60 || posX <= runway.offsetLeft) {
            direction *= -1;
        }
        planeElem.style.left = posX + 'px';

        if (callback && callback()) {
            clearInterval(interval);
        }
    }, 12); 
}

function moveToRunway(planeElem, runwayX, runwayY, callback) {
    let posX = parseInt(planeElem.style.left) || 0;
    let posY = parseInt(planeElem.style.top) || 0;
    const stepX = (runwayX - posX) / 160; 
    const stepY = (runwayY - posY) / 160;

    const interval = setInterval(() => {
        posX += stepX;
        posY += stepY;
        planeElem.style.left = posX + 'px';
        planeElem.style.top = posY + 'px';

        if (Math.abs(posX - runwayX) < 1 && Math.abs(posY - runwayY) < 1) {
            clearInterval(interval);
            callback();
        }
    }, 12); 
}

function moveAlongRunway(planeElem, runwayEndX, callback) {
    let posX = parseInt(planeElem.style.left) || 0;
    const stepX = 5.625; 
    const interval = setInterval(() => {
        posX += stepX;
        planeElem.style.left = posX + 'px';

        if (posX >= runwayEndX) {
            clearInterval(interval);
            planeElem.remove();
            landingCount++;
            
            setTimeout(() => {
                if (landingCount === planes.length) {
                    showMessage();
                }
                callback();
            }, 1600);
        }
    }, 16); 
}

function showMessage() {
    clearInterval(timerInterval);

    const messageDiv = document.createElement('div');
    messageDiv.className = 'message';
    messageDiv.innerHTML = `
        <p>Todos os aviões pousaram!</p>
        <p>Tempo total: ${timer}s</p>
        <button onclick="restartSimulation()">Reiniciar</button>
    `;
    document.body.appendChild(messageDiv);
}

function runSimulation() {
    const runwayStartX = runway.offsetLeft;
    const runwayMiddleX = runway.offsetLeft + runway.offsetWidth / 2 - 50;
    const runwayY = runway.offsetTop + 20;
    const runwayEndX = runway.offsetLeft + runway.offsetWidth - 50;
    let waitingPlanes = 0;

    planes.forEach((plane, index) => {
        setTimeout(() => {
            const altitudeOffset = waitingPlanes * 30;
            const planeElem = createPlaneElement(plane, altitudeOffset);
            waitingPlanes++;

            moveHorizontallyWithinRunway(planeElem, () => {
                if (runwayClear && timer >= plane.target_time) {
                    runwayClear = false;
                    waitingPlanes--;

                    planeElem.classList.remove('waiting');
                    planeElem.classList.add('landing');

                    const randomRunwayX = Math.random() * (runwayMiddleX - runwayStartX) + runwayStartX;

                    moveToRunway(planeElem, randomRunwayX, runwayY, () => {
                        planeElem.classList.remove('landing');
                        planeElem.classList.add('landed');

                        setTimeout(() => {
                            planeElem.classList.remove('landed');
                            planeElem.classList.add('departing');
                            moveAlongRunway(planeElem, runwayEndX, () => {
                                runwayClear = true;
                            });
                        }, 800);
                    });
                    return true;
                }
                return false;
            });
        }, plane.initial_delay * 1000); 
    });

    timer = 0;
    timerInterval = setInterval(() => {
        timer++;
        timerDisplay.textContent = `Tempo: ${timer}s`;
    }, 1000);
}

function restartSimulation() {
    document.querySelectorAll('.plane').forEach(plane => plane.remove());
    clearInterval(timerInterval);
    timerDisplay.textContent = 'Tempo: 0s';
    document.querySelector('.message')?.remove();
    runwayClear = true;
    landingCount = 0;
    runSimulation();
}

runSimulation();