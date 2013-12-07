class Cube
{
public:
    // This data structure defines a simple house

  int nVerts = 8;    // your vertex array needs to have this many entries

  // These are the x,y,z coordinates of the vertices of the triangles
  float vertices[72] = {
            -5,5,5, 5,5,5, 5,-5,5, -5,-5,5,     // front face
            -5,5,5, -5,5,-5, -5,-5,-5, -5,-5,5, // left face
            5,5,5, 5,5,-5, 5,-5,-5, 5,-5,5,  // right face
            -5,5,-5, 5,5,-5, 5,-5,-5, -5,-5,-5,     // back face
            -5,5,5, 5,5,5, 5,5,-5, -5,5,-5,     // top face
            -5,-5,-5, 5,-5,-5, 5,-5,5, -5,-5,5 // bottom face
            };

  // These are the RGB colors corresponding to the vertices, in the same order
  float colors[36] = {
            0,1,0, 0,1,0,
            1,1,0, 1,1,0,
            0,1,1, 0,1,1,
            0,0,1, 0,0,1,
            1,0,0, 1,0,0,
            1,0,1, 1,0,1
            };

  // The index data stores the connectivity of the triangles;
  // index 0 refers to the first triangle defined above
  int indices[36] = {
            0,1,2, 0,2,3,
            4,5,6, 4,6,7,
            8,9,10, 8,10,11,
            12,13,14, 12,14,15,
            16,17,18, 16,18,19,
            20,21,22, 20,22,23};            // rear attic wall
};
