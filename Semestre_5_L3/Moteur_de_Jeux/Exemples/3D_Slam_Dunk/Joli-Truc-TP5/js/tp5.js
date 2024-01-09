
/* TP5  - JOLI TRUC en 3D

-----> thème choisi <-----
Sport =  basket-ball
Equipe = Cavaliers de Cleveland
Action = Dunk, un joueur marque un panier
+ applaudissement à la fin 

https://www.youtube.com/watch?v=8626gYcbHr8&t=4s&ab_channel=Relaxation
soud ballon de basket qui rebondit

HADJ RABAH
ZINE EDDINE 
L3 INFORMATIQUE */

let renderer, scene, camera,sphereRadius,cam;
sphereRadius = 0.5; // pour la balle de basket
cam = 450;

/* chargement de l'audio pour la fin de l'animation
lorsque le joueur marque le panier un son
d'applaudissement s'active 9 secondes */
var audio_musique = document.createElement("AUDIO")
document.body.appendChild(audio_musique);
audio_musique.src = "./Assets/Applause.mp3"

function init() {

  let cnv = document.querySelector('#myCanvas');
  renderer = new THREE.WebGLRenderer({canvas: cnv, antialiasing: true});
  renderer.setSize(window.innerWidth, window.innerHeight);

  // Scene
  scene = new THREE.Scene();
  // Mise en place d'un fond noir
  scene.background = new THREE.Color('black');
  //scene.background = new THREE.Color('white'); fond blanc

  // Camera 
  camera = new THREE.PerspectiveCamera(cam,window.innerWidth / window.innerHeight, 1, 1000 );
  // Positionnement de la camera
  camera.position.x=4;
  camera.position.y=9;
  camera.position.z=15;
  camera.lookAt(0, 0, 0);
  //ajout de la Camera
  scene.add(camera);

  // Plan du terrain de basket
  let loader = new THREE.TextureLoader();
  let texture_terrain = loader.load('./assets/images/terrainclv.png');
  /* l'image doit etre retourner sinon lors de l'affichage
  il y aura un effet miroir de l'image inverse
  */
  let geometry_plane = new THREE.PlaneBufferGeometry(28, 14);
  let material_plane = new THREE.MeshPhongMaterial({map: texture_terrain , side: THREE.DoubleSide});
  let plane = new THREE.Mesh(geometry_plane, material_plane);
  // Positionement du terrain de basket
  plane.rotation.x = Math.PI/2;
  plane.position.x = 0;
  plane.position.y = 0;
  plane.position.z = 0;

  // Plan de la premiere fresque avec le logo de Clevelands BAsket
  let loader_t1 = new THREE.TextureLoader();
  let texture_fresque1 = loader_t1.load('./assets/images/f1.png');
  let geometry_plane1 = new THREE.PlaneBufferGeometry(25, 17);
  let material_plane1 = new THREE.MeshPhongMaterial({map: texture_fresque1, side: THREE.DoubleSide});
  let plane1 = new THREE.Mesh(geometry_plane1, material_plane1);
  // Posititonment de la premiere fresque 
  plane1.rotation.x = 12;
  plane1.position.x = 0;
  plane1.position.y = 5;
  plane1.position.z = -12;

  // Plan de la deuxieme fresque avec le logo de Clevelands BAsket
  let loader_t2 = new THREE.TextureLoader();
  let texture_fresque2 = loader_t2.load('./assets/images/f2.png');
  let geometry_plane2 = new THREE.PlaneBufferGeometry(20, 12);
  let material_plane2 = new THREE.MeshPhongMaterial({map: texture_fresque2, side: THREE.DoubleSide});
  let plane2 = new THREE.Mesh(geometry_plane2, material_plane2);
  // Posititonement de la premiere fresque x=12 y=5 z=-13
  plane2.rotation.x = 12;
  plane2.position.x = 0;
  plane2.position.y = 5;
  plane2.position.z = -13;

  // Cube blanc qui est sous le terrain de basket
  let loader_t3 = new THREE.TextureLoader();
  let texture_cub = loader_t3.load('./assets/images/templat.png');
  let geometry1 = new THREE.BoxGeometry( 28, 13, 10 );
  let material1 = new THREE.MeshBasicMaterial( {map: texture_cub});
  let cube3 = new THREE.Mesh( geometry1, material1 );
  //Positionement du cube blanc
  cube3.position.y = -6.59;
  scene.add( cube3 );

  // Cube logo rouge bordeaux
  // let loader_d = new THREE.TextureLoader();
  let loader_t4 = new THREE.TextureLoader();
  let texture_cube1 = loader_t4.load('./assets/images/l1.png');
  let material_cube1 = new THREE.MeshPhongMaterial({map: texture_cube1, side: THREE.DoubleSide});
  let geometry_cube1 = new THREE.BoxGeometry( 3, 3, 3 );
  let cube = new THREE.Mesh( geometry_cube1, material_cube1);
  // Positionnement du cube logo qui est derrière la fresque
  // qui aura un effet de traverser la fresque jusqu'au début de l'ecran
  cube.position.y = 4;
  cube.position.z = -20;
  cube.position.x = -7;

  // Cube blanc avec texture pour décoration
  let loader_t5 = new THREE.TextureLoader();
  let texture_cube2 = loader_t5.load('./assets/images/l2.png');
  let material_cube2 = new THREE.MeshPhongMaterial({map: texture_cube2, side: THREE.DoubleSide});
  let geometry_cube2 = new THREE.BoxGeometry( 3, 3, 3 );
  let cube2 = new THREE.Mesh( geometry_cube2, material_cube2);
  // Positionement du cube en dessous du terrain effet support
  cube2.position.y = 8;
  cube2.position.z = 8;
  cube2.position.x = -6;
  
  // Torus blanc qui prends le role du panier de basket
  let loader_t6 = new THREE.TextureLoader();
  let texture_torus = loader_t6.load("./assets/images/panier.png");
  let material_torus = new THREE.MeshPhongMaterial({map: texture_torus, side: THREE.DoubleSide});
  let geometry_torus = new THREE.TorusGeometry( 1, 0.3, 16, 300 );
  let torus = new THREE.Mesh( geometry_torus, material_torus );
  // Positionement du Torus à la fin du terrain à droite
  torus.position.y = 6;
  torus.position.x = 13;
  torus.position.z = 0;
  torus.rotation.x = 1.5;

  // Sphere Balle de Basket
  let loader_t7 = new THREE.TextureLoader();
  let texture_ball = loader_t7.load("./assets/images/bll1.png");   
  let geometry_sphere = new THREE.SphereGeometry( 0.4, 32, 32 );
  let material_sphere = new THREE.MeshPhongMaterial({map: texture_ball});
  let sphere_ball = new THREE.Mesh(geometry_sphere , material_sphere);
  // Positionement de la balle au départ
  // Pour le revond voir code de l'animation
  sphere_ball.position.x = 0;
  sphere_ball.position.y = 1;
  sphere_ball.rotation.z = 0.01;
  // Ajout de la sphere a la scene
  scene.add(sphere_ball);
  
  // Joueur cubique 
  let loader_t8 = new THREE.TextureLoader();
  let texture_joueur= loader_t8.load('./assets/images/joueur1.png');
  let material_joueur = new THREE.MeshPhongMaterial({map: texture_joueur, side: THREE.DoubleSide});
  let geometry_joueur = new THREE.BoxGeometry( 1.2, 3.3, 1.2 );
  let joueur = new THREE.Mesh( geometry_joueur ,material_joueur);
  // Poisitionement du joueur cubique
  joueur.position.y = 2;
  joueur.position.z = -1;
  joueur.position.x = 0;
  joueur.rotation.z = 0.01;
  // Ajout du joueur (cube) a la scene
  scene.add(joueur);
  
  //Différentes Lummières pour la scene
  let light = new THREE.HemisphereLight(0xffffff, 0x000000, 1.0);
  let point_light = new THREE.PointLight(0xffffff,0.9);

  // Ajout du reste des éléments dans la scène créer précédement
  scene.add(plane,torus, plane1,plane2,cube,cube2,light,point_light);

  // Fonction qui va animer les formes de la scene
  function animation() {
    // Va nous serir pour la simulation du rebond de la balle 
    // en sa direction x, pour la courbe
    let y_ball_r = Math.abs(Math.sin(Math.PI*sphere_ball.position.x));
    
    // Rotation du torus du cube et du joueur
    cube.rotation.z += 0.01;
    torus.rotation.z += 0.02;
    joueur.rotation.y += 0.01;

    if(cube.position.z < 10.7){
      plane1.position.y -= 0.01;
      cube.position.z +=0.2;
      cube.rotation.x += 0.1;
      cube2.rotation.y -= 0.01;
      camera.position.x-= 0.01;
    }
    plane1.position.y += 0.02;
    cube2.rotation.y += 0.01;
    sphere_ball.position.y = sphereRadius + 4.0 *y_ball_r;

    if(sphere_ball.position.x < 12.0){
      joueur.position.x +=0.02
      sphere_ball.rotation.z -= 0.07;
      sphere_ball.position.x += 0.02;
    }
    if (sphere_ball.position.x > 11.25999999999984){
      audio_musique.play(); // Lancement de son appaudissement
      sphere_ball.position.y += 5;
      joueur.position.y = 5;   
      joueur.rotation.y -=0.01; 
      torus.rotation.z -= 0.02;
      cube.rotation.z -= 0.01;
      cube2.rotation.y -= 0.01;
      // Mouvement de caméra de la fin
      camera.position.y -= 0.012;
      camera.position.x += 0.033;
      camera.position.z -= 0.04;    
    }
    renderer.render( scene, camera );
    requestAnimationFrame( animation);
  }
  animation(); // lancement de l'animation
}

// Fonction pour la fenetre, l'ecran
function onWindowResize(){
  camera.aspect = window.innerWidth/window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
}
window.addEventListener('resize', onWindowResize, false);
init();
/*
J'ai tout coder dans la fonction init
on aurait pu faire une fonction init puis draw et anime
*/