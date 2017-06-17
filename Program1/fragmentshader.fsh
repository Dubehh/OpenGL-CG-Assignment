#version 410 core

// Input from vertex shader
in VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
} fs_in;

in vec2 UV;

// Material properties
uniform vec3 matAmbient;
uniform vec3 matDiffuse;
uniform vec3 matSpecular;
uniform float matPower;
uniform sampler2D plop;

// Output
out vec4 color;

void main(void)
{
    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

    // Calculate R locally
    vec3 R = reflect(-L, N);

    // Compute the diffuse and specular components for each fragment
    // vec3 diffuse = max(dot(N, L), 0.0) * matDiffuse;
	vec3 diffuse = max(dot(N, L), 0.0) * texture2D(plop, UV).rgb;
	vec3 specular = pow(max(dot(R,V),0.0),matPower) * matSpecular;

    // Write final color to the framebuffer
    // color = vec4(matAmbient + diffuse, 1.0);
	color = vec4(matAmbient + diffuse + specular, 1.0);
}
            