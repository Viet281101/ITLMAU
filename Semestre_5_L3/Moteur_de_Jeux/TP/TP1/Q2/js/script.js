
const canvas = document.getElementById('myCanvas');
const ctx = canvas.getContext('2d');

canvas.width = 1280;
canvas.height = 960;

ctx.fillStyle = 'rgb(255, 255, 255)';
ctx.fillRect(0, 0, canvas.width, canvas.height);
ctx.imageSmoothingEnabled = false;

const tilemap = new Image();
tilemap.src = './assets/tilemap1280x960.png';

const candleSpriteA = new Image();
candleSpriteA.src = './assets/candleA.png';

const candleSpriteB = new Image();
candleSpriteB.src = './assets/candleB.png';

const torch = new Image();
torch.src = './assets/torch.png';

Promise.all([tilemap, candleSpriteA, candleSpriteB, torch].map(image => new Promise(resolve => {
    image.onload = resolve;
}))).then(() => {

    const candleAPositions = [
        { x: 768, y: 130 },
        { x: 800, y: 620 }
    ];

    const candleBPositions = [
        { x: 448, y: 606 },
        { x: 970, y: 130 }
    ];

    const torchPositions = [
        { x: 176, y: 60 },
        { x: 368, y: 60 },
        { x: 944, y: 60 },
        { x: 1136, y: 60 },
        { x: 625, y: 542 },
    ];

    let frameIndex = 0;
    const frameWidth = 16;
    const frameHeight = 16;
    const scale = 2;
    const frameRate = 200;

    function drawCandles() {
        ctx.drawImage(tilemap, 0, 0);

        const sourceX = frameIndex * frameWidth;

        for (const position of candleAPositions) {
            ctx.drawImage(candleSpriteA, sourceX, 0, frameWidth, frameHeight, position.x, position.y, (frameWidth * scale), (frameHeight * scale));
        }

        for (const position of candleBPositions) {
            ctx.drawImage(candleSpriteB, sourceX, 0, frameWidth, frameHeight, position.x, position.y, (frameWidth * scale), (frameHeight * scale));
        }

        for (const position of torchPositions) {
            ctx.drawImage(torch, sourceX, 0, frameWidth, frameHeight, position.x, position.y, (frameWidth * scale), (frameHeight * scale));
        }

        frameIndex = (frameIndex + 1) % 4;
        // requestAnimationFrame(drawCandles);
        setTimeout(drawCandles, frameRate);
    }

    drawCandles();
});


/** Track mouse position **/
// https://stackoverflow.com/questions/7790725/javascript-track-mouse-position
(function() {
    document.addEventListener('mousedown', handleMouseMove);
    function handleMouseMove(event) {
        var eventDoc, doc, body;

        event = event || window.event; // IE-ism

        // If pageX/Y aren't available and clientX/Y are,
        // calculate pageX/Y - logic taken from jQuery.
        // (This is to support old IE)
        if (event.pageX == null && event.clientX != null) {
            eventDoc = (event.target && event.target.ownerDocument) || document;
            doc = eventDoc.documentElement;
            body = eventDoc.body;

            event.pageX = event.clientX +
              (doc && doc.scrollLeft || body && body.scrollLeft || 0) -
              (doc && doc.clientLeft || body && body.clientLeft || 0);
            event.pageY = event.clientY +
              (doc && doc.scrollTop  || body && body.scrollTop  || 0) -
              (doc && doc.clientTop  || body && body.clientTop  || 0 );
        }

        // Use event.pageX / event.pageY here
        console.log(event.pageX, event.pageY);
    }
})();
