
//////// Import
import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { EffectComposer } from 'three/addons/postprocessing/EffectComposer.js';
import { RenderPass } from 'three/addons/postprocessing/RenderPass.js'
import { UnrealBloomPass } from 'three/addons/postprocessing/UnrealBloomPass.js';


const simplex = new SimplexNoise();
const originalColor = [];
const targetColor = [];


//// Scene & Camera
const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
camera.position.z = 5;

//// Renderer
const renderer = new THREE.WebGLRenderer({canvas: document.getElementById('myCanvas')});
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

//// Lighting
const ambientLight = new THREE.AmbientLight(0xffffff, 0.5);
scene.add(ambientLight);
const directionalLight = new THREE.DirectionalLight(0xffffff, 1);
directionalLight.position.set(0, 1, 1);
scene.add(directionalLight);

//// Spheres
const sphereMaterial = new THREE.MeshStandardMaterial({ color: 0x5fcde4 });
const spheres = [];
for (let i = 0; i < 50; i++) {
	createSphere(0.5);
};

//// Post Processing - Bloom
const composer = new EffectComposer(renderer);
composer.addPass(new RenderPass(scene, camera));

const bloomPass = new UnrealBloomPass(new THREE.Vector2(window.innerWidth, window.innerHeight), 1.5, 0.4, 0.85);
composer.addPass(bloomPass);

//// Orbit Controls
const controls = new OrbitControls(camera, renderer.domElement);

//// dat.GUI
const gui = new dat.GUI();
const settings = {
	speed: 0.5,
	radius: 0.5,
	numSpheres: 50,
	color: '#5fcde4',
	emissiveIntensity: 0.5,
	flicker: false,
	colorChange: false,
	lerpSpeed: 0.05,
	bloomStrength: 1.5,
	bloomRadius: 0.85
};

gui.add(settings, 'speed', 0, 1, 0.01);
gui.add(settings, 'radius', 0.01, 1, 0.01).onChange(function(e) {
	spheres.forEach(sphere => {
		sphere.geometry = new THREE.SphereGeometry(e, 30, 30);
	});
});
gui.add(settings, 'numSpheres', 0, 150, 1).onChange(function(e) {
	////////////*  Add/remove spheres solution 1	*////////////
	// if (e > spheres.length) {
	// 	for (let i = spheres.length; i < e; i++) {
	// 		createSphere(settings.radius);
	// 	}
	// } else {
	// 	for (let i = spheres.length; i > e; i--) {
	// 		scene.remove(spheres[i-1]);
	// 		spheres.pop();
	// 	}
	// }

	////////////*  Add/remove spheres solution 2	*////////////
	spheres.forEach(sphere => {
		scene.remove(sphere);
		sphere.geometry.dispose();
		sphere.material.dispose();
	});
	spheres.length = 0;
	for (let i = 0; i < e; i++) {
		createSphere(settings.radius);
	}
});
gui.addColor(settings, 'color').onChange(function(e) {
	sphereMaterial.color.set(e);
});
gui.add(settings, 'emissiveIntensity', 0, 10, 0.01).onChange(function(e) {
	spheres.forEach(sphere => {
		sphere.material.emissive.set(settings.color).multiplyScalar(e);
	});
});
gui.add(settings, 'bloomStrength', 0, 3, 0.01).onChange(function(e) {
	bloomPass.strength = e;
});
gui.add(settings, 'bloomRadius', 0, 1, 0.01).onChange(function(e) {
	bloomPass.radius = e;
});
gui.add(settings, 'flicker');
gui.add(settings, 'colorChange');
gui.add(settings, 'lerpSpeed', 0, 1, 0.01);


//// Flicker Effect
function flickerSpheres() {
	if (settings.flicker) {
		spheres.forEach(sphere => {
			sphere.material.emissive.set(settings.color).multiplyScalar(Math.random() * settings.emissiveIntensity);
		});
	}
	requestAnimationFrame(flickerSpheres);
};

//// Color Change Effect
function changeSphereColors() {
	if (settings.colorChange) {
		spheres.forEach((sphere, index) => {
			sphere.material.color.lerp(targetColor[index], settings.lerpSpeed);
		});
	} else {
		spheres.forEach((sphere, index) => {
			sphere.material.color.set(originalColor[index]);
		});
	}
};
function updateTargetColors() {
	if (settings.colorChange) {
		for (let i = 0; i < targetColor.length; i++) {
			targetColor[i].set(new THREE.Color(Math.random(), Math.random(), Math.random()));
		};
	}
};


//// Create Sphere
function createSphere(radius) {
	const sphereGeometry = new THREE.SphereGeometry(radius, 30, 30);
	const sphere = new THREE.Mesh(sphereGeometry, sphereMaterial);
	sphere.position.set(Math.random() * 10 - 5, Math.random() * 10 - 5, Math.random() * 10 - 5);
	scene.add(sphere);
	spheres.push(sphere);
	originalColor.push(sphereMaterial.color.clone());
	targetColor.push(new THREE.Color(Math.random(), Math.random(), Math.random()));
};
  


function animate() {
	const time = Date.now() * 0.001;

	//// Move spheres simplex noise style
	spheres.forEach((sphere, index) => {
		sphere.position.x += (simplex.noise3D(index, time, 0)) * settings.speed;
		sphere.position.y += (simplex.noise3D(index, time, 1)) * settings.speed;
		sphere.position.z += (simplex.noise3D(index, time, 2)) * settings.speed;
	});

	flickerSpheres();
	changeSphereColors();

	controls.update();
	renderer.render(scene, camera);
	composer.render();


	requestAnimationFrame(animate);
};

animate();
setInterval(updateTargetColors, 1000);

