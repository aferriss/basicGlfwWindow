#version 330
out vec4 color;
uniform float time;
uniform sampler2D tex0;
void main(){
    vec2 uv = vec2(gl_FragCoord.xy / vec2(640.0,480.0));
    vec4 t = texture(tex0, uv);
    t.rgb = t.grb;
//    color = vec4(gl_FragCoord.x / 640.0, gl_FragCoord.y / 480.0, sin(time*0.1)*0.5 + 0.5, 1.0);
    color = t;
    color.a = 1.0;
}
