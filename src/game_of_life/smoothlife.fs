#version 330 







const int ra = 9; // ring outer
const int ri = ra/3; // ring inner
const float alpha = 0.028; // alpha_n
// const float alpha_m = 0.147f;
const float b1 = 0.278;
const float b2 = 0.368;
const float d1 = 0.267;
const float d2 = 0.445;
const float dt = 0.05;










// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

uniform vec2 resolution;





int emod(int a, int b)
{
  return (a%b + b)%b;
}

float sigma_1(float x, float a)
{
  return 1.0/(1.0 + exp(-(x - a)*4/alpha));
}

float sigma_2(float x, float a, float b)
{
  return sigma_1(x, a)*(1 - sigma_1(x, b));
}

float sigma_m(float x, float y, float m)
{
  return sigma_1(m, 0.5)*(y - x) + x;
}

float s(float n, float m)
{
  return sigma_2(n, sigma_m(b1, d1, m), sigma_m(b2, d2, m));
}

float grid(int x, int y)
{
  float tx = float(x)/resolution.x;
  float ty = float(y)/resolution.y;
  vec4 t = texture(texture0, vec2(tx, ty));
  return max(max(t.x, t.y), t.z);
}






void main()
{

  int cx = int(floor(fragTexCoord.x*resolution.x));
  int cy = int(floor(fragTexCoord.y*resolution.y));
  float m = 0, M = 0; 
  float n = 0, N = 0;

  float sq_ri = ri*ri, sq_ra = ra*ra;

  for (int dy = -(ra - 1); dy <= (ra - 1); ++dy) {
    for (int dx = -(ra - 1); dx <= (ra - 1); ++dx) {
      
      int x = emod(cx + dx, int(resolution.x));
      int y = emod(cy + dy, int(resolution.y));

      float sq_dx = dx*dx, sq_dy = dy*dy;

      if (sq_dx + sq_dy <= sq_ri) {
        m += grid(y, x);
        M++;
      } else if (sq_dx + sq_dy <= sq_ra) {
        n += grid(y, x);
        N++;
      }

    }
  }

  n /= N;
  m /= M;
  float q = s(n, m);
  float diff = 2*q - 1;
  float v = grid(cx, cy) + dt*diff;


  // finalColor = texture(texture0, fragTexCoord)*fragColor(0, 1, 0, 1);
  // finalColor = vec4(fragTexCoord.x, fragTexCoord.y, 0, 1);
  finalColor = vec4(v, v, v, 1);
}
