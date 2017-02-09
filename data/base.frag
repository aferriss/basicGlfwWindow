#version 330
out vec4 color;
void main(){
    color = vec4(gl_FragCoord.x / 640.0, gl_FragCoord.y / 480.0, 1.0, 1.0);
}
