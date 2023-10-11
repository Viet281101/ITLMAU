

let cnv = document.getElementById("myCanvas");
let ctx = cnv.getContext("2d");


ctx.imageSmoothingEnabled = false;



function getRandom(min, max) {
    return Math.round(Math.random() * (max - min) + min);
}


class myImg {
    constructor(imgSrc, w = 25, h = 25) {
    this.defaultW = w;
    this.defaultH = h;
    this.w = w;
    this.h = h;
    this.imgSrc = imgSrc;

    this.x = (cnv.width / 2) - (this.w / 2);
    this.y = (cnv.height / 2) - (this.h / 2);

    this.img = new Image();
    this.img.src = this.imgSrc;
    }

    reset() {
        this.w = this.defaultW;
        this.h = this.defaultH;
        this.x = (cnv.width / 2) - (this.w / 2);
        this.y = (cnv.height / 2) - (this.h / 2);
        this.img.src = this.img;
    }

    draw(ctx) {
        ctx.drawImage(this.img, this.x, this.y, this.w, this.h);
    }
}


class flakeCircle {
    constructor(x = 0, speed = 1, size = 1) {
        this.x = x;
        this.y = 0;
        this.size = size;
        this.speed = speed;
        this.isDead = false;
    }

    drop(cnv) {
        if (this.isDead) { return; }

        this.y += this.speed;
        if (this.y > cnv.height) {
            this.isDead = true;
        }
    }

    draw(ctx) {
        if (this.isDead) { return; }
        //circle
        ctx.beginPath();
        ctx.arc(this.x, this.y, this.size, 0, 2*Math.PI);
        ctx.fillStyle = "#FFFFFF";
        ctx.fill();
        ctx.closePath();
        //rectangle
        // ctx.beginPath();
        // ctx.fillStyle = "#FFFFFF";
        // ctx.fillRect(this.x, this.y, this.width, this.height);
        // ctx.closePath();
    }
}


class snowAnim {
    constructor(min = 1, max = 10) {
        this.minFlakesByWave = min;
        this.maxFlakesByWave = max;
        // this.next_drop = 10; //time
        this.drop = true;
        this.pause = false;
        this.flakes = []
        this.nb_flakes = 0
    }


    clear_flakes() { this.flakes = []; }

    remove_dead_flakes() {
        //remove dead flakes
        let iDeadFlakes = []
        for (let i = 0; i < this.flakes.length; i++) {
            if (this.flakes[i].isDead) {
                iDeadFlakes.push(i);
            }
        }

        for (let i = iDeadFlakes.length - 1; i >= 0; i--) {
            this.flakes.splice(iDeadFlakes[i], 1);
        }

        this.nb_flakes = this.flakes.length;
    }

    add_flakes(cnv) {
        this.remove_dead_flakes();

        if (this.pause || !this.drop) { return; }
        //add new flakes
        let add = getRandom(this.minFlakesByWave, this.maxFlakesByWave);

        for (let i = 0; i < add; i++) {
            let x = getRandom(0, cnv.width);
            let speed = getRandom(1, 10);
            let size = getRandom(4, 10);
            let flake = new flakeCircle(x, speed, size);
            // flake.draw(ctx);
            this.flakes.push(flake);
        }

        this.remove_dead_flakes();

    }


    draw(ctx, cnv) {
        for (let i = 0; i < this.flakes.length; i++) {
            if (!this.pause) {
                this.flakes[i].drop(cnv);
            }
            this.flakes[i].draw(ctx);
        }

    }

    



}





let imgName = "paysage";
let ext = ".png";
let sprite = "assets/" + imgName + ext;


let snow = new snowAnim();
let img = new myImg(sprite, cnv.width, cnv.height);
let gui = new dat.gui.GUI();

let snowFolder = gui.addFolder("Snow");
snowFolder.open()


snowFolder.add(snow, "minFlakesByWave", 1, 100, 1).onChange(val => {
    if (val > snow.maxFlakesByWave) {
        snow.maxFlakesByWave = val;
    }
})
snowFolder.add(snow, "maxFlakesByWave", 1, 100, 1).onChange(val => {
    if (val < snow.minFlakesByWave) {
        snow.minFlakesByWave = val;
    }
})
snowFolder.add(snow, "pause").name("Flakes freeze");
snowFolder.add(snow, "drop").name("Create new flakes");
snowFolder.add(snow, "clear_flakes");
snowFolder.add(snow, "nb_flakes");






function updateGui() {
    snowFolder.updateDisplay();
}

function add_flakes() {
    snow.add_flakes(cnv);
}

function draw() {
    ctx.clearRect(0, 0, cnv.width, cnv.height);
    img.draw(ctx);
    snow.draw(ctx, cnv);
}



function update() {
    add_flakes();
    draw();
    updateGui();
}

setInterval(update, 50);
