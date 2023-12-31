
import * as dat from 'dat.gui';
// const dat = require('dat.gui');

// let param = {
//     longueur: 10,
// };
// let gui = new dat.gui.GUI();
// gui.add(param, 'longueur').min(10).max(100).step(1);



let param = {
    valeurBooleennePourCaseACocher : true,
    menuDeroulant : "un", // ici un est la valeur par défaut
            // ce qui suppose de l’avoir par la suite (cf ligne 13)
    menuDeroulantAssociatif : 1.0,
    appelDeFonction : function() { console.log("hello world"); },
    couleur: "#ffae23",
};

function another_fun() { console.log("another hello world"); }

let gui = new dat.gui.GUI();
let fa = gui.addFolder('first values');
fa.add(param, 'valeurBooleennePourCaseACocher').onChange(another_fun);
fa.add(param, 'menuDeroulant', [ 'un', 'deux', 'trois' ]);
let fb = gui.addFolder('last values');
fb.add(param, 'menuDeroulantAssociatif', { Un: 1.0, Dix: 10.0, Vingt: 20.0 } );
fb.add(param, 'appelDeFonction').name('une fonction');
fb.addColor(param, 'couleur');
