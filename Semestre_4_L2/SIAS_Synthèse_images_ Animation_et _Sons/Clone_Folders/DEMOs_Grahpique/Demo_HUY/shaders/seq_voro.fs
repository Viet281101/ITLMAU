#version 330

in vec2 vsoTexCoord;
out vec4 maSortie;

uniform int nb_mobiles;
uniform vec2 coords[256];
uniform vec4 colors[256];

void main2() {
  const float dmax = 0.5;
  vec4 cinit = vec4(1.0);
  for(int i = 0; i < nb_mobiles; ++i) {
    float d = distance(vsoTexCoord, coords[i]);
    if(d < dmax) {
      cinit *= colors[i];//vec4(1.0 - d / dmax);
      //return;
    }
  }
  maSortie = cinit;//vec4(1.0);
}

void main() {
  vec2 moi = vsoTexCoord;
  float dmin, previous_dmin;
  int idmin, previous_idmin;

  if(distance(moi, coords[0]) < distance(moi, coords[1])) {
    idmin = 0;
    dmin = distance(moi, coords[0]);
    previous_idmin = 1;
    previous_dmin = distance(moi, coords[1]);
  } else {
    idmin = 1;
    dmin = distance(moi, coords[1]);
    previous_idmin = 0;
    previous_dmin = distance(moi, coords[0]);
  }
  for(int i = 2; i < nb_mobiles; ++i) {
    float d = distance(vsoTexCoord, coords[i]);
    if(dmin > d) {
      previous_dmin = dmin;
      previous_idmin = idmin;
      dmin = d;
      idmin = i;
    }
  }
  if(dmin < 0.005)
    maSortie = vec4(0.0);
  else {
    /* if(previous_dmin - dmin < 0.002)  */
    /*   maSortie = vec4(0.0); */
    /* else */
    /*   maSortie = colors[idmin]; */
    maSortie = colors[idmin] * vec4(1.0 - pow(dmin / (previous_dmin), 3.0));
  }
}
