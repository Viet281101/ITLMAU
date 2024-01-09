
const canvas = document.getElementById('myCanvas');
const ctx = canvas.getContext('2d');
canvas.width = 1280;
canvas.height = 960;
ctx.imageSmoothingEnabled = false;

const background = new Image();
background.src = './assets/tilemap1280x960.png';

const skeletonRight = new Image();
skeletonRight.src = './assets/walk_right.png';

const skeletonLeft = new Image();
skeletonLeft.src = './assets/walk_left.png';

let xPos = 320;
let yPos = 600;
const endPos = 870;
const speed = 4;

let isFlipped = false;

let frame = 0;
let frameRate = 140;
let frameWidth = 128;
let frameHeight = 96;

background.onload = () => {
	drawSkeleton();
};

function drawSkeleton() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    ctx.drawImage(background, 0, 0);

    if (!isFlipped) {
		ctx.drawImage(skeletonRight, frame * frameWidth, 0, frameWidth, frameHeight, xPos, yPos, frameWidth * 2, frameHeight * 2);
		xPos += speed;

		if (xPos >= endPos) {
			isFlipped = true;
			frame = 0;
		} else {
			frame = (frame + 1) % 6;
		}
    } else {
		ctx.save();
		ctx.scale(-1, 1);
		ctx.drawImage(skeletonLeft, frame * frameWidth, 0, frameWidth, frameHeight, -xPos -128, yPos, frameWidth * 2, frameHeight * 2);
		ctx.restore();
		xPos -= speed;

		if (xPos <= 320) {
			isFlipped = false;
			frame = 0;
		} else {
			frame = (frame + 1) % 6;
		}
    }

    // requestAnimationFrame(drawSkeleton);
	setTimeout(drawSkeleton, frameRate);
}