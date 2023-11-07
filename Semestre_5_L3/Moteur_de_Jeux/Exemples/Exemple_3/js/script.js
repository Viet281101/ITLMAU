
let cnv = document.querySelector('#myCanvas');
let renderer = new THREE.WebGLRenderer({canvas: cnv,
antialiasing: true});

let width = window.innerWidth;
let height = window.innerHeight;

renderer.setSize(width, height);

let scene = new THREE.Scene();
let camera = new THREE.PerspectiveCamera(75, width/height, 1, 1000);
scene.add(camera);

let spheres = [];

function addSphere(radius, nbStack, xc, yc, zc){
    let geometry = new THREE.SphereGeometry(radius, 100, nbStack);
    let material = new THREE.MeshBasicMaterial({color: 0xffffff,
    wireframe: true});
    let newSphere = new THREE.Mesh(geometry, material);
    newSphere.position.set(xc, yc, zc);
    spheres.push(newSphere);
    scene.add(newSphere);
};

for (let i = 0; i < 5; i++) {
    addSphere(1.0+0.2*i, 2+i, -1.5+1.5*i, 0.0, -1*i);
};

camera.position.set(0, 0, 2);
camera.lookAt(0, 0, 0);

function onWindowResize(){
    width = window.innerWidth;
    height = window.innerHeight;
    camera.aspect = width/height;
    camera.updateProjectionMatrix();
    renderer.setSize(width, height);
};

let previousTimeStamp = undefined;
let updateTime = 20, elapsed = updateTime+1;

function update(timestamp) {
    if(previousTimeStamp != undefined) {
        elapsed = timestamp-previousTimeStamp;
    }
    if(elapsed > updateTime) {
        previousTimeStamp = timestamp;
        for (let i = 0; i < 5; i++) {
        spheres[i].rotation.x += 0.01+0.001*i;
        spheres[i].rotation.y += 0.01+0.001*i;
        }
    }
    renderer.render(scene, camera);
    requestAnimationFrame(update);
};

window.addEventListener('resize', onWindowResize, false);
requestAnimationFrame(update);

