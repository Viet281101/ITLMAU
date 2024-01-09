
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
playerImage.src = './assets/warrior/idle_right.png';

const candleSpriteA = new Image();
candleSpriteA.src = './assets/candleA.png';

const candleSpriteB = new Image();
candleSpriteB.src = './assets/candleB.png';

const torch = new Image();
torch.src = './assets/torch.png';


class CharactersSprite {
    constructor ({
        position,
        velocity,
        image
    }) {
        this.position = position;
        this.velocity = velocity;
        this.image = image;
        this.frames = 6;
        this.width = (this.image.width / this.frames);
        this.height = this.image.height;
    };

    draw () {
        ctx.drawImage(
            this.image,
            0,
            0,
            this.width,
            this.height,
            this.position.x,
            this.position.y,
            this.width * scale,
            this.height * scale
        );
    }
};


const keys = {
    w: { pressed: false }, z: { pressed: false },

    q: { pressed: false }, a: { pressed: false },

    s: { pressed: false },
    d: { pressed: false },

    ArrowUp: {
        pressed: false,
    },
    ArrowDown: {
        pressed: false,
    },
    ArrowLeft: {
        pressed: false,
    },
    ArrowRight: {
        pressed: false,
    },
}

function clearCanvas() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.fillStyle = 'rgb(255, 255, 255)';
    ctx.fillRect(0, 0, canvas.width, canvas.height);
};


const warrior = new CharactersSprite({
    position: { 
        x: 256, 
        y: 520
    },
    image: playerImage,
});


//// Draw the tilemap with the candles and the torches animated
Promise.all([
    tilemap, 
    candleSpriteA, 
    candleSpriteB, 
    torch].map(image => new Promise(resolve => {
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

    function drawCandles() {
        ctx.drawImage(tilemap, 0, 0);
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

    drawCandles();

    function animateWarrior() {
        clearCanvas();
        drawCandles();
    
        warrior.draw();
    
        if (keys.w.pressed || keys.z.pressed || keys.ArrowUp.pressed) {
            warrior.position.y -= 2;
        } else if (keys.s.pressed || keys.ArrowDown.pressed) {
            warrior.position.y += 2;
        } else if (keys.q.pressed || keys.a.pressed || keys.ArrowLeft.pressed) {
            warrior.position.x -= 2;
        } else if (keys.d.pressed || keys.ArrowRight.pressed) {
            warrior.position.x += 2;
        }
    
        window.requestAnimationFrame(animateWarrior);
    }
    animateWarrior();
});


window.addEventListener('keydown', (event) => {
    // console.log(event.key);
    switch (event.key) {
        /* UP */
        case 'z':
            keys.z.pressed = true;
            break;
        case 'w':
            keys.w.pressed = true;
            break;
        case 'ArrowUp':
            keys.ArrowUp.pressed = true;
            break;
        
        /* LEFT */
        case 'q':
            keys.q.pressed = true;
            break;
        case 'a':
            keys.a.pressed = true;
            break;
        case 'ArrowLeft':
            keys.ArrowLeft.pressed = true;
            break;
        
        /* DOWN */
        case 's':
            keys.s.pressed = true;
            break;
        case 'ArrowDown':
            keys.ArrowDown.pressed = true;
            break;
        
        /* RIGHT */
        case 'd':
            keys.d.pressed = true;
            break;
        case 'ArrowRight':
            keys.ArrowRight.pressed = true;
            break;
    }
});

window.addEventListener('keyup', (event) => {
    // console.log(event.key);
    switch (event.key) {
        /* UP */
        case 'z':
            keys.z.pressed = false;
            break;
        case 'w':
            keys.w.pressed = false;
            break;
        case 'ArrowUp':
            keys.ArrowUp.pressed = false;
            break;
        
        /* LEFT */
        case 'q':
            keys.q.pressed = false;
            break;
        case 'a':
            keys.a.pressed = false;
            break;
        case 'ArrowLeft':
            keys.ArrowLeft.pressed = false;
            break;
        
        /* DOWN */
        case 's':
            keys.s.pressed = false;
            break;
        case 'ArrowDown':
            keys.ArrowDown.pressed = false;
            break;
        
        /* RIGHT */
        case 'd':
            keys.d.pressed = false;
            break;
        case 'ArrowRight':
            keys.ArrowRight.pressed = false;
            break;
    }
});

