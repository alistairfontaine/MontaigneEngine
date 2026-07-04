uniform float offset;
void main() {
    gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0);
}
