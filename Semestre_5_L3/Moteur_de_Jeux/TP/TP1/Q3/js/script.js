
const canvas = document.getElementById('myCanvas');
const ctx = canvas.getContext('2d');

const scale = 2;
canvas.width = 640 * scale;
canvas.height = 480 * scale;

ctx.fillStyle = 'rgb(255, 255, 255)';
ctx.fillRect(0, 0, canvas.width, canvas.height);
ctx.imageSmoothingEnabled = false;

const tilemap = new Image();
tilemap.src = './assets/tilemap1280x960.png';

const playerImage = new Image();
playerImage.src = './assets/warrior/idle.png';

const candleSpriteA = new Image();
candleSpriteA.src = './assets/candleA.png';

const candleSpriteB = new Image();
candleSpriteB.src = './assets/candleB.png';

const torch = new Image();
torch.src = './assets/torch.png';


Promise.all([
    tilemap, 
    candleSpriteA, 
    candleSpriteB, 
    torch, 
    playerImage].map(image => new Promise(resolve => {
    image.onload = resolve;
}))).then(() => {
    const objectsToDraw = [];

    const initCandleAPositions = [
        { x: 768, y: 130 },
        { x: 800, y: 620 }
    ];

    const initCandleBPositions = [
        { x: 448, y: 606 },
        { x: 970, y: 130 }
    ];

    const initTorchPositions = [
        { x: 176, y: 60 },
        { x: 368, y: 60 },
        { x: 944, y: 60 },
        { x: 1136, y: 60 },
        { x: 625, y: 542 },
    ];

    const candleAPositions = [...initCandleAPositions];
    const candleBPositions = [...initCandleBPositions];
    const torchPositions = [...initTorchPositions];

    let frameIndex = 0;
    const frameWidth = 16;
    const frameHeight = 16;
    const frameRate = 200;

    ctx.drawImage(tilemap, 0, 0);

    function drawCandles() {

        const sourceX = frameIndex * frameWidth;

        for (const position of candleAPositions) {
            objectsToDraw.push({
                image: candleSpriteA,
                sourceX,
                sourceY: 0,
                sourceWidth: frameWidth,
                sourceHeight: frameHeight,
                destinationX: position.x,
                destinationY: position.y,
                destinationWidth: (frameWidth * scale),
                destinationHeight: (frameHeight * scale)
            });
        }

        for (const position of candleBPositions) {
            objectsToDraw.push({
                image: candleSpriteB,
                sourceX,
                sourceY: 0,
                sourceWidth: frameWidth,
                sourceHeight: frameHeight,
                destinationX: position.x,
                destinationY: position.y,
                destinationWidth: (frameWidth * scale),
                destinationHeight: (frameHeight * scale)
            });
        }

        for (const position of torchPositions) {
            objectsToDraw.push({
                image: torch,
                sourceX,
                sourceY: 0,
                sourceWidth: frameWidth,
                sourceHeight: frameHeight,
                destinationX: position.x,
                destinationY: position.y,
                destinationWidth: (frameWidth * scale),
                destinationHeight: (frameHeight * scale)
            });
        }

        for (const object of objectsToDraw) {
            ctx.drawImage(
                object.image,
                object.sourceX,
                object.sourceY,
                object.sourceWidth,
                object.sourceHeight,
                object.destinationX,
                object.destinationY,
                object.destinationWidth,
                object.destinationHeight
            );
        }

        objectsToDraw.length = 0;

        frameIndex = (frameIndex + 1) % 4;
        setTimeout(drawCandles, frameRate);
    }

    function drawWarrior() {
        drawCandles();
        ctx.drawImage(
            playerImage, 
            0,
            0,
            playerImage.width / 6,
            playerImage.height,
            (canvas.width / 2 - playerImage.width / 6), 
            (canvas.height / 2 - playerImage.height / 6),
            (playerImage.width / 6) * scale,
            (playerImage.height) * scale
        );
    }

    drawWarrior();
});


