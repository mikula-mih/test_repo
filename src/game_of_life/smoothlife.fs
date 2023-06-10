#version 330 

const float PI = 3.14159265359;
const float ra = 9.0;
const float ri = ra/3.0;
const float alpha = 0.028;
// const float alpha_m = 0.147;
const float b1 = 0.278;
const float b2 = 0.368;
const float d1 = 0.267;
const float d2 = 0.445;
const float dt = 0.05;

float sigma_1(float x, float a);
float sigma_2(float x, float a, float b);
float sigma_m(float x, float y, float m);
float s(float n, float m);
float grid(float x, float y);

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform vec2 resolution;

out vec4 finalColor;

void main()
{
  float cx = fragTexCoord.x*resolution.x;
  float cy = (1 - fragTexCoord.y)*resolution.y;
  
  float sq_ri = ri*ri, sq_ra = ra*ra;
  
  float m = 0, n = 0;
  float M = PI*sq_ri; 
  float N = PI*sq_ra - M;

  for (float dy = -ra; dy <= ra; dy += 1.0) {
    for (float dx = -ra; dx <= ra; dx += 1.0) {
      
      float x = cx + dx;
      float y = cy + dy;

      float sq_dx = dx*dx, sq_dy = dy*dy;

      if (sq_dx + sq_dy <= sq_ri) {
        m += grid(y, x);
      } else if (sq_dx + sq_dy <= sq_ra) {
        n += grid(y, x);
      }

    }
  }

  n /= N;
  m /= M;
  float q = s(n, m);
  float diff = 2.0*q - 1.0;
  float v = clamp(grid(cx, cy) + dt*diff, 0.0, 1.0);

  finalColor = vec4(v, v, v, 1);
}

float sigma_1(float x, float a)
{
  return 1.0/(1.0 + exp(-(x - a)*4.0/alpha));
}

float sigma_2(float x, float a, float b)
{
  return sigma_1(x, a)*(1.0 - sigma_1(x, b));
}

float sigma_m(float x, float y, float m)
{
  return sigma_1(m, 0.5)*(y - x) + x;
}

float s(float n, float m)
{
  return sigma_2(n, sigma_m(b1, d1, m), sigma_m(b2, d2, m));
}

float grid(float x, float y)
{
  float tx = x/resolution.x;
  float ty = y/resolution.y;
  vec4 t = texture(texture0, vec2(tx, ty));
  return max(max(t.x, t.y), t.z);
}
