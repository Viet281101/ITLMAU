
const canvas = document.getElementById('myCanvas');
const ctx = canvas.getContext('2d');

canvas.width = 1280;
canvas.height = 960;

ctx.fillStyle = 'rgb(255, 255, 255)';
ctx.fillRect(0, 0, canvas.width, canvas.height);

const image = new Image();
image.src = './assets/tilemap2560x1920.png';

image.onload = () => {
    ctx.drawImage(image, 0, 0);
};
