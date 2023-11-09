
import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';

// Setup
const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
camera.position.z = 20;

const renderer = new THREE.WebGLRenderer({ canvas: document.querySelector('#myCanvas') });
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

// Create particles
const particles = [];
for (let i = 0; i < 100; i++) {
  const size = Math.random() * 0.2;
  const particleGeometry = new THREE.SphereGeometry(size, 32, 32);
  const material = new THREE.MeshPhongMaterial({ color: new THREE.Color(Math.random(), Math.random(), Math.random()) });
  const particle = new THREE.Mesh(particleGeometry, material);
  
  particle.position.set(
    (Math.random() - 0.5) * 50,
    (Math.random() - 0.5) * 50,
    (Math.random() - 0.5) * 50
  );

  particle.velocity = new THREE.Vector3(
    (Math.random() - 0.5) * 2,
    (Math.random() - 0.5) * 2,
    (Math.random() - 0.5) * 2
  );
  
  scene.add(particle);
  particles.push(particle);
}

// Add lighting
const ambientLight = new THREE.AmbientLight(0x404040);
scene.add(ambientLight);
const directionalLight = new THREE.DirectionalLight(0xffffff, 1);
directionalLight.position.set(0, 1, 2);
scene.add(directionalLight);

// OrbitControls
const controls = new OrbitControls(camera, renderer.domElement);

// Animation
function animate() {
  requestAnimationFrame(animate);
  
  particles.forEach(particle => {
    particle.position.add(particle.velocity);

    if (particle.position.x > 25 || particle.position.x < -25) {
      particle.velocity.x = -particle.velocity.x;
    }
    if (particle.position.y > 25 || particle.position.y < -25) {
      particle.velocity.y = -particle.velocity.y;
    }
    if (particle.position.z > 25 || particle.position.z < -25) {
      particle.velocity.z = -particle.velocity.z;
    }
  });

  controls.update();
  renderer.render(scene, camera);
}

animate();

// Handle window resize
window.addEventListener('resize', () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});
